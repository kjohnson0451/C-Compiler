/* Basic parser, shows the structure but no code generation */

#include <stdio.h>
#include "lex.h"

void statements() {

  /* statements -> expression SEMI
   *            |  expression SEMI statements
   */

  while( !match(EOI) ) {
    expression();

    if( match(SEMI) ) {
      advance();
    } else {
      fprintf(stderr, "%d: Inserting missing semicolon\n", yylineno);
    }
  }
}

void expression() {
  /* expression -> term expression' */

  if( !legal_lookahead() ) {
    return;
  }
  term();
  while( match(PLUS) ) {
    advance();
    term();
  }
}

void expr_prime() {

  /* expression' -> PLUS term expression'
   *              | epsilon
   */

  if( match(PLUS) ) {
    advance();
    term();
    expr_prime();
  }
}

void term() {
  /* term -> factor term' */

  factor();
  term_prime();  
}

void term_prime() {
  /* term' -> TIMES factor term'
   *       |  epsilon
   */

  if( match(TIMES) ) {
    advance();
    factor();
    term_prime();
  }
}

void factor() {
  /* factor -> NUM_OR_ID
   *        |  LP expression RP
   */

  if( match(NUM_OR_ID) ) {
    advance();
  } else if( match(LP) ) {
    advance();
    expression();
    if() {
      advance();
    } else {
      fprintf(stderr, "%d: Mismatched parenthesis\n", yylineno);
    }
  } else {
    fprintf(stderr, "%d Number or identifier expected\n", yylineno);
  }
}
