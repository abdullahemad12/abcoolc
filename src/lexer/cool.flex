/*
 *  The scanner definition for COOL.
 */

/*
 *  Stuff enclosed in %{ %} in the first section is copied verbatim to the
 *  output, so headers and global definitions are placed here to be visible
 * to the code in the file.  Don't remove anything that was here initially
 */
%option noyywrap
%{
#include <cool-parse.h>
#include <stringtab.h>
#include <utilities.h>

/* The compiler assumes these identifiers. */
#define yylval cool_yylval
#define yylex  cool_yylex

/* Max size of string constants */
#define MAX_STR_CONST 1025
#define YY_NO_UNPUT   /* keep g++ happy */

extern FILE *fin; /* we read from this file */

/* define YY_INPUT so we read from the FILE fin:
 * This change makes it possible to use this scanner in
 * the Cool compiler.
 */
#undef YY_INPUT
#define YY_INPUT(buf,result,max_size) \
	if ( (result = fread( (char*)buf, sizeof(char), max_size, fin)) < 0) \
		YY_FATAL_ERROR( "read() in flex scanner failed");

char string_buf[MAX_STR_CONST]; /* to assemble string constants */
char *string_buf_ptr;

extern int curr_lineno;
extern int verbose_flag;

extern YYSTYPE cool_yylval;


/*prototypes*/
int convertEscapedToAscii(char* src, int src_length, char* dest, int dest_length);
int skipCommentSection();
%}

/*
 * Define names for regular expressions here.
 */

DARROW              =>

ASSIGN              <-

LE                  <=

NOT                 (N|n)(O|o)(T|t)

INTEGERS            [0-9]+

TBOOLEAN            t(R|r)(U|u)(E|e)

FBOOLEAN            f(A|a)(L|l)(S|s)(E|e)

TYPEID              [A-Z](([A-Za-z0-9]|_)*) 

OBJECTID            [a-z](([A-Za-z0-9]|_)*)     

NEWLINE             \n

SPECIALCHARACTERS   [\t\r\b\f\v]|" "

STARTCOMMENT        \(\*

CLOSECOMMENT        \*\)  

ONELINECOMMENT      "-""-".*\n|"-""-".*

STRING              \"(\\\n|\\[^\0]|[^\0\n\"\\])*\"

ESCAPEDNULSTR       \".*\\\0.*\"

NULSTR              \".*\0.*\"


UNMATCHEDSTR        \"

CLASS               (C|c)(L|l)(A|a)(S|s)(S|s)

ELSE                (E|e)(L|l)(S|s)(E|e)

FI                  (F|f)(I|i)

IF                  (I|i)(F|f)

IN                  (I|i)(N|n)

INHERITS            (I|i)(N|n)(H|h)(E|e)(R|r)(I|i)(T|t)(S|s)

LET                 (L|l)(E|e)(T|t)

LOOP                (L|l)(O|o)(O|o)(P|p)

POOL                (P|p)(O|o)(O|o)(L|l)

THEN                (T|t)(H|h)(E|e)(N|n)

WHILE               (W|w)(H|h)(I|i)(L|l)(E|e)

CASE                (C|c)(A|a)(S|s)(E|e)

ESAC                (E|e)(S|s)(A|a)(C|c)

OF                  (O|o)(F|f)

NEW                 (N|n)(E|e)(W|w)

ISVOID              (I|i)(S|s)(V|v)(O|o)(I|i)(D|d)

%%




 /*Key words*/


 /*
  *  comments
  */

 /*
  * nested comments
  * skip all the input till the closing tag or EOF
  */
{STARTCOMMENT} {
    int err = skipCommentSection();
    if(err) 
    {
        cool_yylval.error_msg = "EOF in comment";
        return ERROR;
    }
}

 /**
   * Handle unmatched bracket error
   * simply if a dangling bracket was matched, it means that 
   * no previously matching open bracket was seen because if it 
   * was, it would have been already consumed
   */
{CLOSECOMMENT} {
   cool_yylval.error_msg = "Unmatched *)";
   return ERROR;
}   

 /*one line comment*/
{ONELINECOMMENT} {  
        if(yytext[yyleng-1] == '\n') {
            ++curr_lineno;
        }
}

 /**
   * single line comments 
   */

 /*
  *  The multiple-character operators.
  */
{DARROW} { return DARROW; }

{ASSIGN} { return ASSIGN; }

{LE} { return LE; }



 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */
{NOT} { return NOT; }


{TBOOLEAN} {
    cool_yylval.boolean = true;
    return BOOL_CONST;
}

{FBOOLEAN} {
    cool_yylval.boolean = false;
    return BOOL_CONST;
}

{CLASS} { return CLASS; }

{ELSE} { return ELSE; }

{FI}  { return FI; } 

{IF}  { return IF; }

{IN}  { return IN; }

{INHERITS} { return INHERITS; }

{ISVOID}  { return ISVOID; }

{LET} { return LET; }

{LOOP} { return LOOP; }

{POOL} { return POOL; }

{THEN} { return THEN; }

{WHILE} { return WHILE; }

{CASE} { return CASE; }

{ESAC} { return ESAC; }

{NEW} { return NEW; }

{OF} { return OF; }

 /**
   * 10.1 Integers and Identifiers
   */
 /**
   * when a group of digits is matched, simply add them to the string table
   */
{INTEGERS} {
    cool_yylval.symbol = inttable.add_string(yytext);
    return INT_CONST;
}
 /**
   * when a word starting with a capital letter is matched
   */  
{TYPEID} {
    cool_yylval.symbol = idtable.add_string(yytext);
    return TYPEID;
}


 /**
   * single characters 
   */
   
 /* on new line skip and increment the line number */
{NEWLINE} { ++curr_lineno; } 

  /* Other special characters skip */
{SPECIALCHARACTERS} { }


\{ { return '{'; }

\} { return '}'; }

\( { return '('; }

\) { return ')'; }

\: { return ':'; }

\; { return ';'; }

\. { return '.'; }

\, { return ','; } 

\@ { return '@'; }

\+ { return '+'; }

\- { return '-'; }

\* { return '*'; }

\/ { return '/'; }

\~ { return '~'; }

\< { return '<'; }

\= { return '='; }



 /**
   * when a word starting with a small letter is matched
   */
{OBJECTID} {
    cool_yylval.symbol = idtable.add_string(yytext);
    return OBJECTID;
}   
   
 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *  valid strings meet the following criteria: 
  *  1. They start and end with quotations
  *  2. characters in the string can be any except for the following: \0  
  *  3. \n character is only allowed if it follows a escape character \
  *  4. \ character is only allowed if it perceeds any other allowed character including itself
  *  Any character not satisfying this criteria is invalid 
  */
  
{STRING} {
    int err =  convertEscapedToAscii(yytext, yyleng, string_buf, MAX_STR_CONST);
    if(err == -1) 
    {
        cool_yylval.error_msg = "String constant too long"; 
        return ERROR;
    }
    cool_yylval.symbol = stringtable.add_string(string_buf);
    return STR_CONST;
}


 /*
  * Error Handling for strings
  * Three errors that could occur in a string according 
  * to the COOL language specifications:
  * 1. The string is too long to be treated as a constant (handled when processing a valid string)
  * 2. The string contains a null terminator byte (any other characters are allowed given that they may satisfy some condition)
  * 3. The string has an unmatched quotation due to one the following reasons:
  *          A. An unescaped newline was encountered before the closing quotation was found
  *          B. EOF occured before the closing quotation was found
  */
  
 /*matches strings that contains the null character in them*/
{NULSTR} {
    cool_yylval.error_msg = "String contains null character";
    return ERROR;
}

{ESCAPEDNULSTR} {
    cool_yylval.error_msg = "String contains escaped null character";
    return ERROR; 
}

 /*the only other possible case for an invalid string is if only the string had
   an unmatched quotation*/
{UNMATCHEDSTR} {
    // consume the rest of the input until a new line or EOF
    char c;
    char prev= '"';
    while((c=yyinput()) != EOF && c != 0) 
    {
        if(prev != '\\') 
        {
             // only skip if the new line is escaped
            if(c == '\n')
            {
                ++curr_lineno;
                break;
            }
            else 
            {
                // we dont really care what c is in this case 
                // I set it to a nul terminator to avoid having it mistaken for
                // a backslash escape
                c = '\0';
            }

        }
        prev = c;
    }
    
    cool_yylval.error_msg = "Unterminated string constant";
    return ERROR;
}



 /*the given character could not be matched in any possible way. probably an error*/
. {
   cool_yylval.error_msg = yytext;
   return ERROR;
}


%%



/****************
 *    helpers   *
 ****************/
 
/**
  * EFFECTS: converts the escaped character to the correct ASCII character value.
  *          special characters and their conversions:
  *                    - 'n' => '\n'
  *                    - 'b' => '\b'
  *                    - 'f' => '\f'
  *                    - 't' => '\t'
  *                    - '0' => '\0'
  *           Any other character is returned as it is
  * REQUIRES: the given character to be preceeded by a bachslash 
  * RETURNS: the correct conversion of the given character
  * PARAMETERS: char c: the given character
  */ 
char convertEscapedCharacter(char c)
{
    if(c == '\n')
    {
        ++curr_lineno;
    }
    switch(c)
    {
        case 'n': return '\n';
        case 'b': return '\b';
        case 'f': return '\f';
        case 't': return '\t';
        case '0': return '0';
        default: return c;
    }
}

/**
  * EFFECTS: Converts the escaped characters to it is equivalent ASCII code
  * MODIFIES: dest 
  * REQUIRES: 
  *  - src and dest to be pointers to initialized strings. 
  *  - src to be null terminated
  *  - src to be a valid string. i.e this function should only be called when matched with a valid string "STRING"
  * RETURNS: returns zero on success, and non-zero integer otherwise 
  * ERRORS: 
  * -1: the string is too long
  * PARAMETERS: 
  * - char* src: pointer to the source string
  * - char* dest: pointer to the destination string
  * - int dest_length: the maximum length of the string to be processed. typically the size of the destination buffer
  */ 
int convertEscapedToAscii(char* src, int src_length, char* dest, int dest_length)
{
    int strptr = 0;
    int i;
    // from 1 to -1 to skip the quotation
    for(i = 1; i < src_length-1 && strptr < dest_length; i++) 
    {
        if(src[i] == '\\')
        {
            // because this is a valid string, there must always be a next character 
            // that is different from \0. 
            dest[strptr++] = convertEscapedCharacter(src[i+1]);
            // skip over the next character since we have already read it
            ++i; 
        }
        else 
        {
            dest[strptr++] = src[i];
        }
    }
    if(strptr >= dest_length - 1) 
    {
        return -1;
    }
    // terminate the string
    dest[strptr] = '\0'; 
    return 0;
}


/**
  * EFFECTS: skips the comment section including all the nested comments 
  * MODIFIES: the input pointer
  * RETURNS: 0 if the comment block was closed successfully, 1 otherwise
  * ERRORS: 
  * n: returned when EOF is reached but no closing bracket was found. 
  *    n is the number of brackets that was opened but not matched
  */
int skipCommentSection()
{
    int n_opened = 1;
    char c;
    char prev = ' ';
    while((c=yyinput()) != EOF && c != 0 && n_opened > 0)
    {
        // update line count
        if(c == '\n') 
        {
            ++curr_lineno;
        }
        if(prev == '*' && c == ')') {
            --n_opened;
        }
        else if(prev == '(' && c == '*'){
            ++n_opened;
        }
        prev = c;
    }
    if(c == '\n')
    {
        ++curr_lineno;
    }
    return n_opened;
}
