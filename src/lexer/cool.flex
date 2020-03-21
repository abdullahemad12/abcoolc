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

bool comment = false;
int commnentnestings = 0;
bool string = false;
int stringnestings = 0;



/*
 *  Add Your own definitions here
 */

%}

/*
 * Define names for regular expressions here.
 */

DARROW          =>

INTEGERS       [0-9]*

TYPEID         [A-Z](([A-Za-z0-9]|_)*) 

OBJECTID       [a-z](([A-Za-z0-9]|_)*)     

NEWLINE        \n

SPECIALCHARACTERS   [\t\r\b\f\v" "]

STARTCOMMENT      \(*  

STRING            \"(\\\"|\\\n|\\.|[^\0|\n|\"|\\])*\"


%%


 /**
   * single characters 
   */
   
 /* on new line skip and increment the line number */
{NEWLINE} { ++curr_lineno; } 

  /* Other special characters skip */
{SPECIALCHARACTERS} { }
 
  /*on EOF */
<<EOF>> { 
   if(string) {
        strcpy(cool_yylval.error_msg, "EOF in string constant"); 
        return ERROR;
    }
    if(comment) {
        strcpy(cool_yylval.error_msg, "EOF in comment"); 
        return ERROR;
    }
    yyterminate();    
 }

 
 /*
  *  Nested comments
  */


 /*
  *  The multiple-character operators.
  */
{DARROW} { return (DARROW); }


{INTEGERS} {
    cool_yylval.symbol = inttable.add_string(yytext);
    return INT_CONST;
}
 /*
  * Keywords are case-insensitive except for the values true and false,
  * which must begin with a lower-case letter.
  */


 /*
  *  String constants (C syntax)
  *  Escape sequence \c is accepted for all characters c. Except for 
  *  \n \t \b \f, the result is c.
  *
  */
{STRING} {
    printf("hello\n");
}

%%


/**
  * EFFECTS: Converts the escaped characters to it is equivalent ASCII code
  * MODIFIES: dest 
  * REQUIRES: src and dest to be pointers to initialized strings. src must be null terminated
  * PARAMETERS: 
  * - char* src: pointer to the source string
  * - char* dest: pointer to the destination string
  * - int max_length: the maximum length of the string to be processed. typically the size of the destination buffer
  */ 
void convertEscapedToAscii(char* src, char* dest, int max_length)
{

}


