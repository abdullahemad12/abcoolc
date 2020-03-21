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

%}

/*
 * Define names for regular expressions here.
 */

DARROW              =>

INTEGERS            [0-9]*

TYPEID              [A-Z](([A-Za-z0-9]|_)*) 

OBJECTID            [a-z](([A-Za-z0-9]|_)*)     

NEWLINE             \n

SPECIALCHARACTERS   [\t\r\b\f\v]|" "

STARTCOMMENT        \(*  

STRING              \"(\\\n|\\.|[^\0|\n|\"|\\])*\"

NULSTR              \".*\0.*\"

UNMATCHEDSTR        \"

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
 /*the only other possible case for an invalid string is if only the string had
   an unmatched quotation*/
{UNMATCHEDSTR} {
    // consume the rest of the input until a new line or EOF
    char c;
    char prev= '"';
    while((c=yyinput()) != EOF && c != 0) 
    {
        // only skip if the new line is escaped
        if(prev != '\\' && c == '\n') 
        {
            break;
        }
        prev = c;
    }
    
    cool_yylval.error_msg = "Unterminated string constant";
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
    switch(c)
    {
        case 'n': return '\n';
        case 'b': return '\b';
        case 'f': return '\f';
        case 't': return '\t';
        case '0': return '\0';
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
