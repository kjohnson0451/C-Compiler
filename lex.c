#include "lex.h"
#include <stdio.h>
#include <ctype.h>

char *yytext  = ""; /* Lexeme (not '\0' terminated)   */
int   yyleng   = 0; /* Lexeme length.                 */
int   yylineno = 0; /* Input line number              */

static int Lookahead = -1; /* Lookahead token */

int lex() {
  static char input_buffer[128];
  char *current;

  current = yytext + yyleng; /* Skip current lexeme */

  while( 1 ) {               /* Get next one        */
    while( !*current ) {
      /* Get new lines, skipping any leading white space on the line, 
       * until a nonblank line is found.
       */

      current = input_buffer;
      if( !fgets(input_buffer, sizeof(input_buffer), stdin) ) {
        *current = '\0' ;
        return EOI;
      }

      ++yylineno;

      while( isspace(*current) ) {
        ++current;
      }
    }

    for( ; *current ; ++current ) {
      /* Get the next token */

      yytext = current;
      yyleng = 1;

      switch( *current ) {
      case EOF: return EOI;
      case ';': return SEMI;
      case '+': return PLUS;
      case '*': return TIMES;
      case '(': return L_PAREN;
      case ')': return R_PAREN;

      case '\n':
      case '\t':
      case ' ': break;

      default:
        if( !isalnum(*current) ) {
          fprintf(stderr, "Ignoring illegal input <%c>\n", *current);
        } else {
          while( isalnum(*current)) {
            ++current;
          }

          yyleng = current - yytext;
          return NUM_OR_ID;
        }
        break;
      }
    }
  }
}


int match( int token ) {
  /* Return true if "token" matches the current lookahead symbol. */

  if( Lookahead == -1 ) {
    Lookahead = lex();
  }

  return token == Lookahead;
}

void advance() {
  /* Advance the lookahead to the next input symbol. */
  Lookahead = lex();
}
