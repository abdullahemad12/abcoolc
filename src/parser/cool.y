/*
*  cool.y
*              Parser definition for the COOL language.
*
*/
%{
  #include <iostream>
  #include "cool-tree.h"
  #include "stringtab.h"
  #include "utilities.h"
  
  extern char *curr_filename;
  
  
  /* Locations */
  #define YYLTYPE int              /* the type of locations */
  #define cool_yylloc curr_lineno  /* use the curr_lineno from the lexer
  for the location of tokens */
    
    extern int node_lineno;          /* set before constructing a tree node
    to whatever you want the line number
    for the tree node to be */
      
      
      #define YYLLOC_DEFAULT(Current, Rhs, N)         \
      Current = Rhs[1];                             \
      node_lineno = Current;
    
    
    #define SET_NODELOC(Current)  \
    node_lineno = Current;
    
    /* IMPORTANT NOTE ON LINE NUMBERS
    *********************************
    * The above definitions and macros cause every terminal in your grammar to 
    * have the line number supplied by the lexer. The only task you have to
    * implement for line numbers to work correctly, is to use SET_NODELOC()
    * before constructing any constructs from non-terminals in your grammar.
    * Example: Consider you are matching on the following very restrictive 
    * (fictional) construct that matches a plus between two integer constants. 
    * (SUCH A RULE SHOULD NOT BE  PART OF YOUR PARSER):
    
    plus_consts	: INT_CONST '+' INT_CONST 
    
    * where INT_CONST is a terminal for an integer constant. Now, a correct
    * action for this rule that attaches the correct line number to plus_const
    * would look like the following:
    
    plus_consts	: INT_CONST '+' INT_CONST 
    {
      // Set the line number of the current non-terminal:
      // ***********************************************
      // You can access the line numbers of the i'th item with @i, just
      // like you acess the value of the i'th exporession with $i.
      //
      // Here, we choose the line number of the last INT_CONST (@3) as the
      // line number of the resulting expression (@$). You are free to pick
      // any reasonable line as the line number of non-terminals. If you 
      // omit the statement @$=..., bison has default rules for deciding which 
      // line number to use. Check the manual for details if you are interested.
      @$ = @3;
      
      
      // Observe that we call SET_NODELOC(@3); this will set the global variable
      // node_lineno to @3. Since the constructor call "plus" uses the value of 
      // this global, the plus node will now have the correct line number.
      SET_NODELOC(@3);
      
      // construct the result node:
      $$ = plus(int_const($1), int_const($3));
    }
    
    */
    
    
    
    void yyerror(char *s);        /*  defined below; called for each parse error */
    extern int yylex();           /*  the entry point to the lexer  */
    
    /************************************************************************/
    /*                DONT CHANGE ANYTHING IN THIS SECTION                  */
    
    Program ast_root;	      /* the result of the parse  */
    Classes parse_results;        /* for use in semantic analysis */
    int omerrs = 0;               /* number of errors in lexing and parsing */
    %}
    
    /* A union of all the types that can be the result of parsing actions. */
    %union {
      Boolean boolean;
      Symbol symbol;
      Program program;
      Class_ class_;
      Classes classes;
      Feature feature;
      Features features;
      Formal formal;
      Formals formals;
      Case case_;
      Cases cases;
      Expression expression;
      Expressions expressions;
      char *error_msg;
    }
    
    /* 
    Declare the terminals; a few have types for associated lexemes.
    The token ERROR is never used in the parser; thus, it is a parse
    error when the lexer returns it.
    
    The integer following token declaration is the numeric constant used
    to represent that token internally.  Typically, Bison generates these
    on its own, but we give explicit numbers to prevent version parity
    problems (bison 1.25 and earlier start at 258, later versions -- at
    257)
    */
    %token CLASS 258 ELSE 259 FI 260 IF 261 IN 262 
    %token INHERITS 263 LET 264 LOOP 265 POOL 266 THEN 267 WHILE 268
    %token CASE 269 ESAC 270 OF 271 DARROW 272 NEW 273 ISVOID 274
    %token <symbol>  STR_CONST 275 INT_CONST 276 
    %token <boolean> BOOL_CONST 277
    %token <symbol>  TYPEID 278 OBJECTID 279 
    %token ASSIGN 280 NOT 281 LE 282 ERROR 283
    
    /*  DON'T CHANGE ANYTHING ABOVE THIS LINE, OR THE PARSER WONT WORK       */
    /**************************************************************************/
    
    /*
     * consult the README for explanation of the role of each non-terminal
     * (See section 3.6 in the bison documentation for details). 
     */

    
    /* Declare types for the grammar's non-terminals. */
    %type <program> program
    %type <classes> class_list
    %type <class_> class
    
    /* You will want to change the following line. */
    %type <features> feature_list
    %type <feature> feature
    
    
    %type <formals> formal_list
    %type <formals> formalsc
    %type <formal> formal
    
    
    %type <expression> expr
    
    %type <expressions> expr_list
    %type <expressions> expr_listc
    
    %type <expressions> expr_stmts
    
    %type <cases> case_stmts
    
    %type <expression> let_init
    %type <expression> let_initc
    
    /* Precedence declarations go here. */
    %right '.'
    %right '@'
    %right '~'
    %right ISVOID
    %right '*' '/'
    %right '+' '-'
    %right LE '<' '='
    %right NOT
    %right ASSIGN
    
    %%
    /* 
    Save the root of the abstract syntax tree in a global variable.
    */
    program	: class_list	{ SET_NODELOC(@1); @$ = @1; ast_root = program($1); }
    ;
    
    class_list
    : class			/* single class */
    { SET_NODELOC(@1); 
    $$ = single_Classes($1);
    parse_results = $$; }
    | class_list class	/* several classes */
    { SET_NODELOC(@1);
     $$ = append_Classes($1,single_Classes($2)); 
    parse_results = $$; }
    ;
    
    /* If no parent is specified, the class inherits from the Object class. */
    class	: CLASS TYPEID '{' feature_list '}' ';'
    { SET_NODELOC(@1);
     $$ = class_($2,idtable.add_string("Object"),$4,
    stringtable.add_string(curr_filename)); }
    | CLASS TYPEID INHERITS TYPEID '{' feature_list '}' ';'
    { SET_NODELOC(@1); 
    $$ = class_($2,$4,$6,stringtable.add_string(curr_filename)); }
    ;
    
    /* Feature list may be empty, but no empty features in list. */
    feature_list : feature_list feature
    {
        SET_NODELOC(@1);
        $$ = append_Features($1, single_Features($2));
    }  
    | { $$ = nil_Features(); }
   
    
    /* Feature definition */
    feature : OBJECTID '(' formal_list ')' ':' TYPEID '{' expr '}' ';'  
    {
        SET_NODELOC(@1);
        $$ = method($1, $3, $6, $8);
    }
    | OBJECTID ':' TYPEID ';' 
    {
        SET_NODELOC(@1);
        $$ = attr($1, $3, no_expr());
    } 
    | OBJECTID ':' TYPEID ASSIGN expr ';' 
    {
        SET_NODELOC(@1);
        $$ = attr($1, $3, $5);
    }
    
    
    /* formal list */
    formal_list : formal formalsc 
    {
       SET_NODELOC(@1);
       $$ = append_Formals(single_Formals($1), $2);
    }
    | 
    {
       $$ = nil_Formals(); 
    }
    
    formalsc : formalsc ',' formal
    {
        SET_NODELOC(@1);
        $$ = append_Formals($1, single_Formals($3));
    }
    |
    {
       $$ = nil_Formals(); 
    }
    
    /*formal*/
    formal : OBJECTID ':' TYPEID 
    {
        SET_NODELOC(@1);
        $$ = formal($1, $3);
    }
    
    
    /*
     * Expression (expr) Non-Terminal
     */
    expr : OBJECTID ASSIGN expr 
    {
        SET_NODELOC(@1);
        $$ = assign($1, $3);
    }
    /*
     * dispatch expr
     * Generates the list of expressions (function argument) and uses it directly 
     */
    | expr '.' OBJECTID '(' expr_list ')'
    {
        SET_NODELOC(@1);
        $$ = dispatch($1, $3, $5);
    }
    | OBJECTID '(' expr_list ')'
    {
        SET_NODELOC(@1);

        $$ = dispatch(object(idtable.add_string("self")), $1, $3); /*need to add self keyword when shorthand is used*/
    }
    /* static dispatch expr */
    | expr '@' TYPEID '.' OBJECTID '(' expr_list ')'
    {
       SET_NODELOC(@1);
       $$ = static_dispatch($1, $3, $5, $7); 
    }
    /*If expression*/ 
    | IF expr THEN expr ELSE expr FI
    {
        SET_NODELOC(@1);
        $$ = cond($2, $4, $6);
    }
    /*while loop expression*/
    | WHILE expr LOOP expr POOL 
    {
        SET_NODELOC(@1);
        $$ = loop($2, $4);   
    }
    /*block of multiple expressions*/
    | '{' expr_stmts '}'
    {
        SET_NODELOC(@1);
        $$ = block($2);
    }
    /*Case statement expression*/
    | CASE expr OF case_stmts ESAC
    {
        SET_NODELOC(@1);
        $$ = typcase($2, $4);
    }
    /*new expression*/
    | NEW TYPEID
    {
        SET_NODELOC(@1);
        $$ = new_($2);
    }
    | ISVOID expr
    {
       SET_NODELOC(@1); 
       $$ = isvoid($2);
    }
    /*arithmetics*/
    | expr '+' expr
    {
        SET_NODELOC(@1); 
        $$ = plus($1, $3);
    }
    | expr '-' expr
    {
        SET_NODELOC(@1);
        $$ = sub($1, $3);
    }
    | expr '*' expr
    {
       SET_NODELOC(@1); 
       $$ = mul($1, $3);
    }
    | expr '/' expr
    {
       SET_NODELOC(@1); 
       $$ = divide($1, $3);
    }
    | '~' expr
    {
        SET_NODELOC(@1);  
        $$ = neg($2);
    }
    /*comparisons*/
    | expr '<' expr
    {
        SET_NODELOC(@1);
        $$ = lt($1, $3);
    }
    | expr LE expr
    {
        SET_NODELOC(@1);      
        $$ = leq($1, $3);
    }
    | expr '=' expr
    {
       SET_NODELOC(@1);
       $$ = eq($1, $3);  
    }
    | NOT expr
    {
       SET_NODELOC(@1);
       $$ = comp($2); 
    }
    /*In brackets*/
    | '(' expr ')'
    {
        SET_NODELOC(@2);
        $$ = $2; 
    }
    /*Atoms*/
    | OBJECTID
    {
        SET_NODELOC(@1);
        $$ = object($1);   
    }
    | INT_CONST
    {
        SET_NODELOC(@1);
        int_const($1);
    }
    | STR_CONST
    {
        SET_NODELOC(@1);
        string_const($1);
    }
    | BOOL_CONST
    {
        SET_NODELOC(@1);
        bool_const($1);
    }
    | LET let_init
    {
        SET_NODELOC(@1);
        $$ = $2;
    }
    /*list of comma separated expressions*/
    expr_list : expr expr_listc
    {
       SET_NODELOC(@1);
       $$ = append_Expressions(single_Expressions($1), $2);
    }
    |
    {
        $$ = nil_Expressions();
    }
    
    expr_listc : expr_listc ',' expr
    {
       SET_NODELOC(@3);
       $$ = append_Expressions($1, single_Expressions($3));
    }
    | 
    {
        $$ = nil_Expressions();
    }
    
    /*expression  seperated by a ';'*/
    expr_stmts : expr_stmts expr ';'
    {
        SET_NODELOC(@2);
        $$ = append_Expressions($1, single_Expressions($2));
    }
    | expr ';' 
    {
       SET_NODELOC(@1);
       $$ = single_Expressions($1);
    }
    
     
     
    /*case statements (cases)*/
    case_stmts  : case_stmts OBJECTID ':' TYPEID DARROW expr ';'
    {
        SET_NODELOC(@2);
        // create a branch, use it to create a list of single case
        // and append the list to the list matched by case_stmts, i.e $1
        $$ = append_Cases($1, single_Cases(branch($2, $4, $6)));
    }
    | OBJECTID ':' TYPEID DARROW expr ';'
    {
        SET_NODELOC(@1);
        $$ = single_Cases(branch($1, $3, $5));   
    }
    
    /*let expression*/
    
    /**
      * let_initc there are two possible cases that let_initc will match:
      * 1. It will match another <OBJECTID>:<TYPEID>[<- expr]. In this case
      *    it creates a new let expression and this let expression will be the body
      *    of the parent let expression.
      * 2. It will match <IN><expr>. In this case it just returns the expr that will be
      *    the body of the last let expression created. 
      * In the two cases the final expression created by let_initc will act as the body of the let 
      * expression matched by let_init.
      */ 
    
    /*The the declared variable is not initialized*/
    let_init : OBJECTID ':' TYPEID let_initc
    {
        SET_NODELOC(@1);
        $$ = let($1, $3, no_expr(), $4); 
    }
    /*The declared type is initialized with expr*/  
    | OBJECTID ':' TYPEID ASSIGN expr let_initc
    {
         SET_NODELOC(@1);
         $$ = let($1, $3, $5, $6);
    }
    
    let_initc : ',' OBJECTID ':' TYPEID let_initc
    {
        SET_NODELOC(@2);
        $$ = let($2, $4, no_expr(), $5);
    }
    | ',' OBJECTID ':' TYPEID ASSIGN expr let_initc
    {
        SET_NODELOC(@2);
        $$ = let($2, $4, $6, $7);
    }
    | IN expr
    {
        SET_NODELOC(@1);
        $$ = $2; // the return type is still expr
    }
    
    
    /* end of grammar */
    %%
    
    /* This function is called automatically when Bison detects a parse error. */
    void yyerror(char *s)
    {
      extern int curr_lineno;
      
      cerr << "\"" << curr_filename << "\", line " << curr_lineno << ": " \
      << s << " at or near ";
      print_cool_token(yychar);
      cerr << endl;
      omerrs++;
      
      if(omerrs>50) {fprintf(stdout, "More than 50 errors\n"); exit(1);}
    }
    
    
