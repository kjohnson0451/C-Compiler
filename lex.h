#define EOI         0 /* End of input                 */
#define SEMI        1 /* ;                            */
#define PLUS        2 /* +                            */
#define TIMES       3 /* *                            */
#define L_PAREN     4 /* (                            */
#define R_PAREN     5 /* )                            */
#define NUM_OR_ID   6 /* decimal number or identifier */

extern char *yytext;
extern int  yyleng;
extern int  yylineno;

int lex();
