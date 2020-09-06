/* A Bison parser, made by GNU Bison 3.6.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.6.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1


/* Substitute the variable and function names.  */
#define yyparse         cool_yyparse
#define yylex           cool_yylex
#define yyerror         cool_yyerror
#define yydebug         cool_yydebug
#define yynerrs         cool_yynerrs
#define yylval          cool_yylval
#define yychar          cool_yychar
#define yylloc          cool_yylloc

/* First part of user prologue.  */
#line 6 "cool.y"

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
    

#line 162 "cool.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_COOL_YY_COOL_TAB_H_INCLUDED
# define YY_COOL_YY_COOL_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int cool_yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 284,                 /* "invalid token"  */
    CLASS = 258,                   /* CLASS  */
    ELSE = 259,                    /* ELSE  */
    FI = 260,                      /* FI  */
    IF = 261,                      /* IF  */
    IN = 262,                      /* IN  */
    INHERITS = 263,                /* INHERITS  */
    LET = 264,                     /* LET  */
    LOOP = 265,                    /* LOOP  */
    POOL = 266,                    /* POOL  */
    THEN = 267,                    /* THEN  */
    WHILE = 268,                   /* WHILE  */
    CASE = 269,                    /* CASE  */
    ESAC = 270,                    /* ESAC  */
    OF = 271,                      /* OF  */
    DARROW = 272,                  /* DARROW  */
    NEW = 273,                     /* NEW  */
    ISVOID = 274,                  /* ISVOID  */
    STR_CONST = 275,               /* STR_CONST  */
    INT_CONST = 276,               /* INT_CONST  */
    BOOL_CONST = 277,              /* BOOL_CONST  */
    TYPEID = 278,                  /* TYPEID  */
    OBJECTID = 279,                /* OBJECTID  */
    ASSIGN = 280,                  /* ASSIGN  */
    NOT = 281,                     /* NOT  */
    LE = 282,                      /* LE  */
    ERROR = 283                    /* ERROR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 284
#define CLASS 258
#define ELSE 259
#define FI 260
#define IF 261
#define IN 262
#define INHERITS 263
#define LET 264
#define LOOP 265
#define POOL 266
#define THEN 267
#define WHILE 268
#define CASE 269
#define ESAC 270
#define OF 271
#define DARROW 272
#define NEW 273
#define ISVOID 274
#define STR_CONST 275
#define INT_CONST 276
#define BOOL_CONST 277
#define TYPEID 278
#define OBJECTID 279
#define ASSIGN 280
#define NOT 281
#define LE 282
#define ERROR 283

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 89 "cool.y"

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
    

#line 288 "cool.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE cool_yylval;
extern YYLTYPE cool_yylloc;
int cool_yyparse (void);

#endif /* !YY_COOL_YY_COOL_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_CLASS = 3,                      /* CLASS  */
  YYSYMBOL_ELSE = 4,                       /* ELSE  */
  YYSYMBOL_FI = 5,                         /* FI  */
  YYSYMBOL_IF = 6,                         /* IF  */
  YYSYMBOL_IN = 7,                         /* IN  */
  YYSYMBOL_INHERITS = 8,                   /* INHERITS  */
  YYSYMBOL_LET = 9,                        /* LET  */
  YYSYMBOL_LOOP = 10,                      /* LOOP  */
  YYSYMBOL_POOL = 11,                      /* POOL  */
  YYSYMBOL_THEN = 12,                      /* THEN  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_CASE = 14,                      /* CASE  */
  YYSYMBOL_ESAC = 15,                      /* ESAC  */
  YYSYMBOL_OF = 16,                        /* OF  */
  YYSYMBOL_DARROW = 17,                    /* DARROW  */
  YYSYMBOL_NEW = 18,                       /* NEW  */
  YYSYMBOL_ISVOID = 19,                    /* ISVOID  */
  YYSYMBOL_STR_CONST = 20,                 /* STR_CONST  */
  YYSYMBOL_INT_CONST = 21,                 /* INT_CONST  */
  YYSYMBOL_BOOL_CONST = 22,                /* BOOL_CONST  */
  YYSYMBOL_TYPEID = 23,                    /* TYPEID  */
  YYSYMBOL_OBJECTID = 24,                  /* OBJECTID  */
  YYSYMBOL_ASSIGN = 25,                    /* ASSIGN  */
  YYSYMBOL_NOT = 26,                       /* NOT  */
  YYSYMBOL_LE = 27,                        /* LE  */
  YYSYMBOL_ERROR = 28,                     /* ERROR  */
  YYSYMBOL_29_ = 29,                       /* '<'  */
  YYSYMBOL_30_ = 30,                       /* '='  */
  YYSYMBOL_31_ = 31,                       /* '+'  */
  YYSYMBOL_32_ = 32,                       /* '-'  */
  YYSYMBOL_33_ = 33,                       /* '*'  */
  YYSYMBOL_34_ = 34,                       /* '/'  */
  YYSYMBOL_35_ = 35,                       /* '~'  */
  YYSYMBOL_36_ = 36,                       /* '@'  */
  YYSYMBOL_37_ = 37,                       /* '.'  */
  YYSYMBOL_38_ = 38,                       /* ';'  */
  YYSYMBOL_39_ = 39,                       /* '{'  */
  YYSYMBOL_40_ = 40,                       /* '}'  */
  YYSYMBOL_41_ = 41,                       /* '('  */
  YYSYMBOL_42_ = 42,                       /* ')'  */
  YYSYMBOL_43_ = 43,                       /* ':'  */
  YYSYMBOL_44_ = 44,                       /* ','  */
  YYSYMBOL_YYACCEPT = 45,                  /* $accept  */
  YYSYMBOL_program = 46,                   /* program  */
  YYSYMBOL_class_list = 47,                /* class_list  */
  YYSYMBOL_class = 48,                     /* class  */
  YYSYMBOL_feature_list = 49,              /* feature_list  */
  YYSYMBOL_feature = 50,                   /* feature  */
  YYSYMBOL_formal_list = 51,               /* formal_list  */
  YYSYMBOL_formalsc = 52,                  /* formalsc  */
  YYSYMBOL_formal = 53,                    /* formal  */
  YYSYMBOL_expr = 54,                      /* expr  */
  YYSYMBOL_expr_list = 55,                 /* expr_list  */
  YYSYMBOL_expr_listc = 56,                /* expr_listc  */
  YYSYMBOL_expr_stmts = 57,                /* expr_stmts  */
  YYSYMBOL_case_stmts = 58,                /* case_stmts  */
  YYSYMBOL_let_init = 59,                  /* let_init  */
  YYSYMBOL_let_initc = 60                  /* let_initc  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   461

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  45
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  16
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  204

#define YYMAXUTOK   284


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      41,    42,    33,    31,    44,    32,    37,    34,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    43,    38,
      29,    30,     2,     2,    36,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,    35,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,     2
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   177,   177,   181,   186,   191,   195,   199,   204,   205,
     209,   214,   218,   223,   228,   234,   235,   236,   237,   238,
     239,   240,   241,   242,   243,   244,   245,   250,   256,   260,
     266,   271,   282,   291,   296,   303,   309,   315,   321,   327,
     333,   338,   344,   349,   354,   359,   364,   370,   375,   380,
     385,   391,   397,   402,   407,   412,   417,   423,   424,   429,
     435,   439,   445,   450,   455,   460,   466,   473,   479,   496,
     502,   507,   510,   515,   520,   525
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "CLASS", "ELSE", "FI",
  "IF", "IN", "INHERITS", "LET", "LOOP", "POOL", "THEN", "WHILE", "CASE",
  "ESAC", "OF", "DARROW", "NEW", "ISVOID", "STR_CONST", "INT_CONST",
  "BOOL_CONST", "TYPEID", "OBJECTID", "ASSIGN", "NOT", "LE", "ERROR",
  "'<'", "'='", "'+'", "'-'", "'*'", "'/'", "'~'", "'@'", "'.'", "';'",
  "'{'", "'}'", "'('", "')'", "':'", "','", "$accept", "program",
  "class_list", "class", "feature_list", "feature", "formal_list",
  "formalsc", "formal", "expr", "expr_list", "expr_listc", "expr_stmts",
  "case_stmts", "let_init", "let_initc", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   284,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,    60,
      61,    43,    45,    42,    47,   126,    64,    46,    59,   123,
     125,    40,    41,    58,    44
};
#endif

#define YYPACT_NINF (-132)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-3)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      11,     9,    34,   100,  -132,    21,  -132,    52,  -132,    56,
      79,  -132,  -132,  -132,    66,    68,     0,     2,  -132,  -132,
     -18,    20,    76,  -132,    81,    26,    97,   103,   115,    97,
      87,  -132,  -132,    96,    80,    98,  -132,   105,   107,   109,
     120,    67,  -132,   139,   126,   127,  -132,  -132,   132,  -132,
    -132,   204,  -132,  -132,    90,    97,    93,   204,     4,   204,
     111,   161,   204,  -132,  -132,  -132,   -10,   204,   204,   135,
     204,   353,   147,   148,  -132,   149,   150,   268,    29,   152,
    -132,   242,   153,   280,  -132,    91,   204,   204,   413,    91,
     156,   365,    58,   291,   204,   204,   204,   204,   204,   204,
     204,   167,   168,  -132,   204,   204,   204,   159,   204,   204,
       6,  -132,   170,   204,  -132,    85,   413,   413,   155,  -132,
    -132,   163,  -132,   377,  -132,   424,   424,   424,   130,   130,
      91,    91,   162,   173,   305,   317,   329,   176,   341,   217,
     413,    29,   160,    -5,   255,   177,   184,   -11,   185,  -132,
    -132,  -132,   196,   204,    32,    36,    37,   193,    84,   204,
    -132,   209,   204,  -132,  -132,  -132,   211,  -132,   192,   204,
     195,   198,  -132,  -132,  -132,  -132,  -132,  -132,  -132,  -132,
    -132,   228,    62,   175,   220,   215,   413,   204,  -132,  -132,
     204,  -132,  -132,   204,   224,   200,   175,   389,   204,  -132,
    -132,  -132,   401,  -132
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     3,     0,     1,     0,     4,     0,
       0,    11,     5,    11,     0,     0,     0,     0,     9,    11,
       0,     0,     0,    10,     0,     0,    28,     0,     0,    28,
       0,     6,     8,     0,     0,     0,    30,     0,     0,     0,
       0,     0,     7,     0,     0,    27,    23,    24,     0,    25,
      26,     0,    13,    31,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    54,    53,    55,    52,     0,     0,     0,
       0,     0,     0,     0,    29,     0,     0,     0,     0,     0,
      56,     0,     0,     0,    40,    41,     0,    60,    50,    46,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    14,     0,     0,     0,     0,     0,     0,
       0,    71,     0,     0,    58,     0,    32,    62,     0,    57,
      64,     0,    38,     0,    51,    48,    47,    49,    42,    43,
      44,    45,     0,     0,     0,     0,     0,     0,     0,     0,
      74,     0,     0,     0,     0,     0,     0,     0,    59,    34,
      65,    63,     0,    60,     0,     0,     0,     0,     0,     0,
      75,     0,     0,    69,    37,    68,     0,    39,     0,     0,
       0,     0,    17,    16,    18,    15,    20,    19,    22,    21,
      12,     0,     0,     0,     0,     0,    61,    60,    33,    36,
       0,    72,    70,     0,     0,     0,     0,     0,     0,    35,
      73,    67,     0,    66
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -132,  -132,  -132,   253,    70,  -132,   234,  -132,   212,   -51,
     -72,  -132,  -132,  -132,  -132,  -131
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    16,    23,    35,    45,    36,   117,
     118,   148,    92,   147,    80,   111
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      71,    20,   109,    20,   167,    78,    77,   141,    81,    83,
     160,    85,   163,   168,     1,    86,    88,    89,    91,    93,
     162,    28,     9,    26,    21,    27,    21,    20,    79,    10,
     142,    87,     5,   172,     6,   116,   109,   174,   176,   110,
      22,   123,    24,   125,   126,   127,   128,   129,   130,   131,
      21,   191,   192,   134,   135,   136,   138,   139,   140,   121,
      11,    29,   144,    30,    57,   200,    33,    58,    50,   109,
     173,    59,    60,   110,   175,   177,    61,    62,    63,    64,
      65,   171,    66,    17,    67,   179,   145,   190,    40,    25,
      12,    72,    51,    68,    75,    13,    14,    69,   122,    70,
      -2,     7,    15,     1,    18,    52,   110,    19,   181,   146,
      41,   183,    82,    73,    31,   195,    76,    57,   186,    32,
      58,    34,   180,    43,    59,    60,    37,   101,   102,    61,
      62,    63,    64,    65,    42,    66,    90,    67,    38,   196,
      44,    57,   197,    46,    58,    47,    68,   202,    59,    60,
      69,    48,    70,    61,    62,    63,    64,    65,    49,    66,
     137,    67,    53,    99,   100,    57,   101,   102,    58,    54,
      68,    55,    59,    60,    69,    56,    70,    61,    62,    63,
      64,    65,   109,    66,    84,    67,   104,   105,   106,   107,
     132,   114,   133,   143,    68,   112,   119,   149,    69,   152,
      70,   150,    94,   161,    95,    96,    97,    98,    99,   100,
      57,   101,   102,    58,   153,   165,   157,    59,    60,   110,
     170,   159,    61,    62,    63,    64,    65,   166,    66,   169,
      67,   178,   182,   189,   184,   185,   187,   193,   194,    68,
     188,   198,   199,    69,    94,    70,    95,    96,    97,    98,
      99,   100,   113,   101,   102,    94,     8,    95,    96,    97,
      98,    99,   100,    39,   101,   102,   164,    74,     0,    94,
       0,    95,    96,    97,    98,    99,   100,     0,   101,   102,
     108,     0,    94,     0,    95,    96,    97,    98,    99,   100,
       0,   101,   102,     0,     0,    94,   115,    95,    96,    97,
      98,    99,   100,     0,   101,   102,     0,    94,     0,    95,
      96,    97,    98,    99,   100,     0,   101,   102,    94,     0,
      95,    96,    97,    98,    99,   100,     0,   101,   102,     0,
       0,     0,    94,   124,    95,    96,    97,    98,    99,   100,
       0,   101,   102,     0,    94,   154,    95,    96,    97,    98,
      99,   100,     0,   101,   102,     0,    94,   155,    95,    96,
      97,    98,    99,   100,     0,   101,   102,     0,    94,   156,
      95,    96,    97,    98,    99,   100,     0,   101,   102,     0,
      94,   158,    95,    96,    97,    98,    99,   100,     0,   101,
     102,   103,    94,     0,    95,    96,    97,    98,    99,   100,
       0,   101,   102,   120,    94,     0,    95,    96,    97,    98,
      99,   100,     0,   101,   102,   151,    94,     0,    95,    96,
      97,    98,    99,   100,     0,   101,   102,   201,    94,     0,
      95,    96,    97,    98,    99,   100,     0,   101,   102,   203,
      94,     0,    95,    96,    97,    98,    99,   100,     0,   101,
     102,    -3,     0,    -3,    -3,    97,    98,    99,   100,     0,
     101,   102
};

static const yytype_int16 yycheck[] =
{
      51,     1,     7,     1,    15,     1,    57,     1,    59,    60,
     141,    62,   143,    24,     3,    25,    67,    68,    69,    70,
      25,     1,     1,    41,    24,    43,    24,     1,    24,     8,
      24,    41,    23,     1,     0,    86,     7,     1,     1,    44,
      40,    92,    40,    94,    95,    96,    97,    98,    99,   100,
      24,   182,   183,   104,   105,   106,   107,   108,   109,     1,
      39,    41,   113,    43,     6,   196,    40,     9,     1,     7,
      38,    13,    14,    44,    38,    38,    18,    19,    20,    21,
      22,   153,    24,    13,    26,     1,     1,    25,     1,    19,
      38,     1,    25,    35,     1,    39,    40,    39,    40,    41,
       0,     1,    23,     3,    38,    38,    44,    39,   159,    24,
      23,   162,     1,    23,    38,   187,    23,     6,   169,    38,
       9,    24,    38,    43,    13,    14,    23,    36,    37,    18,
      19,    20,    21,    22,    38,    24,     1,    26,    23,   190,
      42,     6,   193,    38,     9,    38,    35,   198,    13,    14,
      39,    42,    41,    18,    19,    20,    21,    22,    38,    24,
       1,    26,    23,    33,    34,     6,    36,    37,     9,    43,
      35,    44,    13,    14,    39,    43,    41,    18,    19,    20,
      21,    22,     7,    24,    23,    26,    39,    39,    39,    39,
      23,    38,    24,    23,    35,    43,    40,    42,    39,    37,
      41,    38,    27,    43,    29,    30,    31,    32,    33,    34,
       6,    36,    37,     9,    41,    38,    40,    13,    14,    44,
      24,     4,    18,    19,    20,    21,    22,    43,    24,    44,
      26,    38,    23,     5,    23,    43,    41,    17,    23,    35,
      42,    17,    42,    39,    27,    41,    29,    30,    31,    32,
      33,    34,    10,    36,    37,    27,     3,    29,    30,    31,
      32,    33,    34,    29,    36,    37,    11,    55,    -1,    27,
      -1,    29,    30,    31,    32,    33,    34,    -1,    36,    37,
      12,    -1,    27,    -1,    29,    30,    31,    32,    33,    34,
      -1,    36,    37,    -1,    -1,    27,    16,    29,    30,    31,
      32,    33,    34,    -1,    36,    37,    -1,    27,    -1,    29,
      30,    31,    32,    33,    34,    -1,    36,    37,    27,    -1,
      29,    30,    31,    32,    33,    34,    -1,    36,    37,    -1,
      -1,    -1,    27,    42,    29,    30,    31,    32,    33,    34,
      -1,    36,    37,    -1,    27,    40,    29,    30,    31,    32,
      33,    34,    -1,    36,    37,    -1,    27,    40,    29,    30,
      31,    32,    33,    34,    -1,    36,    37,    -1,    27,    40,
      29,    30,    31,    32,    33,    34,    -1,    36,    37,    -1,
      27,    40,    29,    30,    31,    32,    33,    34,    -1,    36,
      37,    38,    27,    -1,    29,    30,    31,    32,    33,    34,
      -1,    36,    37,    38,    27,    -1,    29,    30,    31,    32,
      33,    34,    -1,    36,    37,    38,    27,    -1,    29,    30,
      31,    32,    33,    34,    -1,    36,    37,    38,    27,    -1,
      29,    30,    31,    32,    33,    34,    -1,    36,    37,    38,
      27,    -1,    29,    30,    31,    32,    33,    34,    -1,    36,
      37,    27,    -1,    29,    30,    31,    32,    33,    34,    -1,
      36,    37
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    46,    47,    48,    23,     0,     1,    48,     1,
       8,    39,    38,    39,    40,    23,    49,    49,    38,    39,
       1,    24,    40,    50,    40,    49,    41,    43,     1,    41,
      43,    38,    38,    40,    24,    51,    53,    23,    23,    51,
       1,    23,    38,    43,    42,    52,    38,    38,    42,    38,
       1,    25,    38,    23,    43,    44,    43,     6,     9,    13,
      14,    18,    19,    20,    21,    22,    24,    26,    35,    39,
      41,    54,     1,    23,    53,     1,    23,    54,     1,    24,
      59,    54,     1,    54,    23,    54,    25,    41,    54,    54,
       1,    54,    57,    54,    27,    29,    30,    31,    32,    33,
      34,    36,    37,    38,    39,    39,    39,    39,    12,     7,
      44,    60,    43,    10,    38,    16,    54,    54,    55,    40,
      38,     1,    40,    54,    42,    54,    54,    54,    54,    54,
      54,    54,    23,    24,    54,    54,    54,     1,    54,    54,
      54,     1,    24,    23,    54,     1,    24,    58,    56,    42,
      38,    38,    37,    41,    40,    40,    40,    40,    40,     4,
      60,    43,    25,    60,    11,    38,    43,    15,    24,    44,
      24,    55,     1,    38,     1,    38,     1,    38,    38,     1,
      38,    54,    23,    54,    23,    43,    54,    41,    42,     5,
      25,    60,    60,    17,    23,    55,    54,    54,    17,    42,
      60,    38,    54,    38
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    45,    46,    47,    47,    47,    48,    48,    48,    48,
      49,    49,    50,    50,    50,    50,    50,    50,    50,    50,
      50,    50,    50,    50,    50,    50,    50,    51,    51,    52,
      52,    53,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    55,
      55,    56,    56,    57,    57,    57,    58,    58,    58,    59,
      59,    59,    60,    60,    60,    60
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     3,     6,     8,     7,     5,
       2,     0,    10,     4,     6,    10,    10,    10,    10,    10,
      10,    10,    10,     4,     4,     4,     4,     2,     0,     3,
       0,     3,     3,     6,     4,     8,     7,     5,     3,     5,
       2,     2,     3,     3,     3,     3,     2,     3,     3,     3,
       2,     3,     1,     1,     1,     1,     2,     3,     3,     2,
       0,     3,     0,     3,     2,     3,     7,     6,     2,     4,
       6,     2,     5,     7,     2,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YY_LOCATION_PRINT
#  if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#   define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

#  else
#   define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#  endif
# endif /* !defined YY_LOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize;

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yynerrs = 0;
  yystate = 0;
  yyerrstatus = 0;

  yystacksize = YYINITDEPTH;
  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;


  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 177 "cool.y"
                                { SET_NODELOC((yylsp[0])); (yyloc) = (yylsp[0]); ast_root = program((yyvsp[0].classes)); }
#line 1621 "cool.tab.c"
    break;

  case 3:
#line 182 "cool.y"
    { SET_NODELOC((yylsp[0])); 
    (yyval.classes) = single_Classes((yyvsp[0].class_));
    parse_results = (yyval.classes); 
    }
#line 1630 "cool.tab.c"
    break;

  case 4:
#line 187 "cool.y"
    { SET_NODELOC((yylsp[-1]));
     (yyval.classes) = append_Classes((yyvsp[-1].classes),single_Classes((yyvsp[0].class_))); 
    parse_results = (yyval.classes); 
    }
#line 1639 "cool.tab.c"
    break;

  case 5:
#line 191 "cool.y"
                           { yyerrok; }
#line 1645 "cool.tab.c"
    break;

  case 6:
#line 196 "cool.y"
    { SET_NODELOC((yylsp[-5]));
     (yyval.class_) = class_((yyvsp[-4].symbol),idtable.add_string("Object"),(yyvsp[-2].features),
    stringtable.add_string(curr_filename)); }
#line 1653 "cool.tab.c"
    break;

  case 7:
#line 200 "cool.y"
    { SET_NODELOC((yylsp[-7])); 
    (yyval.class_) = class_((yyvsp[-6].symbol),(yyvsp[-4].symbol),(yyvsp[-2].features),stringtable.add_string(curr_filename)); 
    }
#line 1661 "cool.tab.c"
    break;

  case 8:
#line 204 "cool.y"
                                                  { yyerrok; }
#line 1667 "cool.tab.c"
    break;

  case 9:
#line 205 "cool.y"
                                 { yyerrok; }
#line 1673 "cool.tab.c"
    break;

  case 10:
#line 210 "cool.y"
    {
        SET_NODELOC((yylsp[0]));
        (yyval.features) = append_Features((yyvsp[-1].features), single_Features((yyvsp[0].feature)));
    }
#line 1682 "cool.tab.c"
    break;

  case 11:
#line 214 "cool.y"
      { (yyval.features) = nil_Features(); }
#line 1688 "cool.tab.c"
    break;

  case 12:
#line 219 "cool.y"
    {
        SET_NODELOC((yylsp[-9]));
        (yyval.feature) = method((yyvsp[-9].symbol), (yyvsp[-7].formals), (yyvsp[-4].symbol), (yyvsp[-2].expression));
    }
#line 1697 "cool.tab.c"
    break;

  case 13:
#line 224 "cool.y"
    {
        SET_NODELOC((yylsp[-3]));
        (yyval.feature) = attr((yyvsp[-3].symbol), (yyvsp[-1].symbol), no_expr());
    }
#line 1706 "cool.tab.c"
    break;

  case 14:
#line 229 "cool.y"
    {
        SET_NODELOC((yylsp[-5]));
        (yyval.feature) = attr((yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expression));
    }
#line 1715 "cool.tab.c"
    break;

  case 15:
#line 234 "cool.y"
                                                            { yyerrok; }
#line 1721 "cool.tab.c"
    break;

  case 16:
#line 235 "cool.y"
                                                           { yyerrok; }
#line 1727 "cool.tab.c"
    break;

  case 17:
#line 236 "cool.y"
                                                             { yyerrok; }
#line 1733 "cool.tab.c"
    break;

  case 18:
#line 237 "cool.y"
                                                              { yyerrok; }
#line 1739 "cool.tab.c"
    break;

  case 19:
#line 238 "cool.y"
                                                              { yyerrok; }
#line 1745 "cool.tab.c"
    break;

  case 20:
#line 239 "cool.y"
                                                                { yyerrok; }
#line 1751 "cool.tab.c"
    break;

  case 21:
#line 240 "cool.y"
                                                                 { yyerrok; }
#line 1757 "cool.tab.c"
    break;

  case 22:
#line 241 "cool.y"
                                                                { yyerrok; }
#line 1763 "cool.tab.c"
    break;

  case 23:
#line 242 "cool.y"
                           { yyerrok; }
#line 1769 "cool.tab.c"
    break;

  case 24:
#line 243 "cool.y"
                                { yyerrok; }
#line 1775 "cool.tab.c"
    break;

  case 25:
#line 244 "cool.y"
                             { yyerrok; }
#line 1781 "cool.tab.c"
    break;

  case 26:
#line 245 "cool.y"
                                { yyerrok; }
#line 1787 "cool.tab.c"
    break;

  case 27:
#line 251 "cool.y"
    {
       SET_NODELOC((yylsp[-1]));
       (yyval.formals) = append_Formals(single_Formals((yyvsp[-1].formal)), (yyvsp[0].formals));
    }
#line 1796 "cool.tab.c"
    break;

  case 28:
#line 256 "cool.y"
    {
       (yyval.formals) = nil_Formals(); 
    }
#line 1804 "cool.tab.c"
    break;

  case 29:
#line 261 "cool.y"
    {
        SET_NODELOC((yylsp[0]));
        (yyval.formals) = append_Formals((yyvsp[-2].formals), single_Formals((yyvsp[0].formal)));
    }
#line 1813 "cool.tab.c"
    break;

  case 30:
#line 266 "cool.y"
    {
       (yyval.formals) = nil_Formals(); 
    }
#line 1821 "cool.tab.c"
    break;

  case 31:
#line 272 "cool.y"
    {
        SET_NODELOC((yylsp[-2]));
        (yyval.formal) = formal((yyvsp[-2].symbol), (yyvsp[0].symbol));
    }
#line 1830 "cool.tab.c"
    break;

  case 32:
#line 283 "cool.y"
    {
        SET_NODELOC((yylsp[-2]));
        (yyval.expression) = assign((yyvsp[-2].symbol), (yyvsp[0].expression));
    }
#line 1839 "cool.tab.c"
    break;

  case 33:
#line 292 "cool.y"
    {
        SET_NODELOC((yylsp[-5]));
        (yyval.expression) = dispatch((yyvsp[-5].expression), (yyvsp[-3].symbol), (yyvsp[-1].expressions));
    }
#line 1848 "cool.tab.c"
    break;

  case 34:
#line 297 "cool.y"
    {
        SET_NODELOC((yylsp[-3]));

        (yyval.expression) = dispatch(object(idtable.add_string("self")), (yyvsp[-3].symbol), (yyvsp[-1].expressions)); /*need to add self keyword when shorthand is used*/
    }
#line 1858 "cool.tab.c"
    break;

  case 35:
#line 304 "cool.y"
    {
       SET_NODELOC((yylsp[-7]));
       (yyval.expression) = static_dispatch((yyvsp[-7].expression), (yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expressions)); 
    }
#line 1867 "cool.tab.c"
    break;

  case 36:
#line 310 "cool.y"
    {
        SET_NODELOC((yylsp[-6]));
        (yyval.expression) = cond((yyvsp[-5].expression), (yyvsp[-3].expression), (yyvsp[-1].expression));
    }
#line 1876 "cool.tab.c"
    break;

  case 37:
#line 316 "cool.y"
    {
        SET_NODELOC((yylsp[-4]));
        (yyval.expression) = loop((yyvsp[-3].expression), (yyvsp[-1].expression));   
    }
#line 1885 "cool.tab.c"
    break;

  case 38:
#line 322 "cool.y"
    {
        SET_NODELOC((yylsp[-2]));
        (yyval.expression) = block((yyvsp[-1].expressions));
    }
#line 1894 "cool.tab.c"
    break;

  case 39:
#line 328 "cool.y"
    {
        SET_NODELOC((yylsp[-4]));
        (yyval.expression) = typcase((yyvsp[-3].expression), (yyvsp[-1].cases));
    }
#line 1903 "cool.tab.c"
    break;

  case 40:
#line 334 "cool.y"
    {
        SET_NODELOC((yylsp[-1]));
        (yyval.expression) = new_((yyvsp[0].symbol));
    }
#line 1912 "cool.tab.c"
    break;

  case 41:
#line 339 "cool.y"
    {
       SET_NODELOC((yylsp[-1])); 
       (yyval.expression) = isvoid((yyvsp[0].expression));
    }
#line 1921 "cool.tab.c"
    break;

  case 42:
#line 345 "cool.y"
    {
        SET_NODELOC((yylsp[-2])); 
        (yyval.expression) = plus((yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1930 "cool.tab.c"
    break;

  case 43:
#line 350 "cool.y"
    {
        SET_NODELOC((yylsp[-2]));
        (yyval.expression) = sub((yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1939 "cool.tab.c"
    break;

  case 44:
#line 355 "cool.y"
    {
       SET_NODELOC((yylsp[-2])); 
       (yyval.expression) = mul((yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1948 "cool.tab.c"
    break;

  case 45:
#line 360 "cool.y"
    {
       SET_NODELOC((yylsp[-2])); 
       (yyval.expression) = divide((yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1957 "cool.tab.c"
    break;

  case 46:
#line 365 "cool.y"
    {
        SET_NODELOC((yylsp[-1]));  
        (yyval.expression) = neg((yyvsp[0].expression));
    }
#line 1966 "cool.tab.c"
    break;

  case 47:
#line 371 "cool.y"
    {
        SET_NODELOC((yylsp[-2]));
        (yyval.expression) = lt((yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1975 "cool.tab.c"
    break;

  case 48:
#line 376 "cool.y"
    {
        SET_NODELOC((yylsp[-2]));      
        (yyval.expression) = leq((yyvsp[-2].expression), (yyvsp[0].expression));
    }
#line 1984 "cool.tab.c"
    break;

  case 49:
#line 381 "cool.y"
    {
       SET_NODELOC((yylsp[-2]));
       (yyval.expression) = eq((yyvsp[-2].expression), (yyvsp[0].expression));  
    }
#line 1993 "cool.tab.c"
    break;

  case 50:
#line 386 "cool.y"
    {
       SET_NODELOC((yylsp[-1]));
       (yyval.expression) = comp((yyvsp[0].expression)); 
    }
#line 2002 "cool.tab.c"
    break;

  case 51:
#line 392 "cool.y"
    {
        SET_NODELOC((yylsp[-1]));
        (yyval.expression) = (yyvsp[-1].expression); 
    }
#line 2011 "cool.tab.c"
    break;

  case 52:
#line 398 "cool.y"
    {
        SET_NODELOC((yylsp[0]));
        (yyval.expression) = object((yyvsp[0].symbol));   
    }
#line 2020 "cool.tab.c"
    break;

  case 53:
#line 403 "cool.y"
    {
        SET_NODELOC((yylsp[0]));
        (yyval.expression) = int_const((yyvsp[0].symbol));
    }
#line 2029 "cool.tab.c"
    break;

  case 54:
#line 408 "cool.y"
    {
        SET_NODELOC((yylsp[0]));
        (yyval.expression) = string_const((yyvsp[0].symbol));
    }
#line 2038 "cool.tab.c"
    break;

  case 55:
#line 413 "cool.y"
    {
        SET_NODELOC((yylsp[0]));
        (yyval.expression) = bool_const((yyvsp[0].boolean));
    }
#line 2047 "cool.tab.c"
    break;

  case 56:
#line 418 "cool.y"
    {
        SET_NODELOC((yylsp[-1]));
        (yyval.expression) = (yyvsp[0].expression);
    }
#line 2056 "cool.tab.c"
    break;

  case 57:
#line 423 "cool.y"
                    { yyerrok; }
#line 2062 "cool.tab.c"
    break;

  case 58:
#line 424 "cool.y"
                    { yyerrok; }
#line 2068 "cool.tab.c"
    break;

  case 59:
#line 430 "cool.y"
    {
       SET_NODELOC((yylsp[-1]));
       (yyval.expressions) = append_Expressions(single_Expressions((yyvsp[-1].expression)), (yyvsp[0].expressions));
    }
#line 2077 "cool.tab.c"
    break;

  case 60:
#line 435 "cool.y"
    {
        (yyval.expressions) = nil_Expressions();
    }
#line 2085 "cool.tab.c"
    break;

  case 61:
#line 440 "cool.y"
    {
       SET_NODELOC((yylsp[0]));
       (yyval.expressions) = append_Expressions((yyvsp[-2].expressions), single_Expressions((yyvsp[0].expression)));
    }
#line 2094 "cool.tab.c"
    break;

  case 62:
#line 445 "cool.y"
    {
        (yyval.expressions) = nil_Expressions();
    }
#line 2102 "cool.tab.c"
    break;

  case 63:
#line 451 "cool.y"
    {
        SET_NODELOC((yylsp[-1]));
        (yyval.expressions) = append_Expressions((yyvsp[-2].expressions), single_Expressions((yyvsp[-1].expression)));
    }
#line 2111 "cool.tab.c"
    break;

  case 64:
#line 456 "cool.y"
    {
       SET_NODELOC((yylsp[-1]));
       (yyval.expressions) = single_Expressions((yyvsp[-1].expression));
    }
#line 2120 "cool.tab.c"
    break;

  case 65:
#line 460 "cool.y"
                           { yyerrok; }
#line 2126 "cool.tab.c"
    break;

  case 66:
#line 467 "cool.y"
    {
        SET_NODELOC((yylsp[-5]));
        // create a branch, use it to create a list of single case
        // and append the list to the list matched by case_stmts, i.e $1
        (yyval.cases) = append_Cases((yyvsp[-6].cases), single_Cases(branch((yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expression))));
    }
#line 2137 "cool.tab.c"
    break;

  case 67:
#line 474 "cool.y"
    {
        SET_NODELOC((yylsp[-5]));
        (yyval.cases) = single_Cases(branch((yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expression)));   
    }
#line 2146 "cool.tab.c"
    break;

  case 68:
#line 479 "cool.y"
                { yyerrok; }
#line 2152 "cool.tab.c"
    break;

  case 69:
#line 497 "cool.y"
    {
        SET_NODELOC((yylsp[-3]));
        (yyval.expression) = let((yyvsp[-3].symbol), (yyvsp[-1].symbol), no_expr(), (yyvsp[0].expression)); 
    }
#line 2161 "cool.tab.c"
    break;

  case 70:
#line 503 "cool.y"
    {
         SET_NODELOC((yylsp[-5]));
         (yyval.expression) = let((yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expression), (yyvsp[0].expression));
    }
#line 2170 "cool.tab.c"
    break;

  case 71:
#line 507 "cool.y"
                      { yyerrok; }
#line 2176 "cool.tab.c"
    break;

  case 72:
#line 511 "cool.y"
    {
        SET_NODELOC((yylsp[-3]));
        (yyval.expression) = let((yyvsp[-3].symbol), (yyvsp[-1].symbol), no_expr(), (yyvsp[0].expression));
    }
#line 2185 "cool.tab.c"
    break;

  case 73:
#line 516 "cool.y"
    {
        SET_NODELOC((yylsp[-5]));
        (yyval.expression) = let((yyvsp[-5].symbol), (yyvsp[-3].symbol), (yyvsp[-1].expression), (yyvsp[0].expression));
    }
#line 2194 "cool.tab.c"
    break;

  case 74:
#line 521 "cool.y"
    {
        SET_NODELOC((yylsp[-1]));
        (yyval.expression) = (yyvsp[0].expression); // the return type is still expr
    }
#line 2203 "cool.tab.c"
    break;

  case 75:
#line 525 "cool.y"
                          { yyerrok; }
#line 2209 "cool.tab.c"
    break;


#line 2213 "cool.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 529 "cool.y"

    
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
    
    
