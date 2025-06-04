%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex(void);
%}

%union {
    int num;
    float dec;
}

%token <num> ENTERO
%token <dec> DECIMAL
%token MOD
%token COMA

%type <dec> expr

%start input

%%

input:
    /* vacío */
    | input expr '\n' {
        printf("RESULTADO: %f\n\n", $2);
    }
    ;

expr:
      expr '+' expr {
          $$ = $1 + $3;
          printf("GRAMÁTICA: Expresión -> Expresión + Expresión (%f + %f)\n", $1, $3);
      }
    | expr '-' expr {
          $$ = $1 - $3;
          printf("GRAMÁTICA: Expresión -> Expresión - Expresión (%f - %f)\n", $1, $3);
      }
    | expr '*' expr {
          $$ = $1 * $3;
          printf("GRAMÁTICA: Expresión -> Expresión * Expresión (%f * %f)\n", $1, $3);
      }
    | expr '/' expr {
          if ($3 != 0) {
              $$ = $1 / $3;
              printf("GRAMÁTICA: Expresión -> Expresión / Expresión (%f / %f)\n", $1, $3);
          } else {
              yyerror("División entre cero");
              $$ = 0;
          }
      }
    | MOD '(' expr COMA expr ')' {
          $$ = (int)$3 % (int)$5;
          printf("GRAMÁTICA: Expresión -> MOD(%f, %f) = %d\n", $3, $5, (int)$$);
      }
    | '(' expr ')' {
          $$ = $2;
          printf("GRAMÁTICA: Expresión -> (Expresión)\n");
      }
    | ENTERO {
          $$ = $1;
          printf("GRAMÁTICA: Expresión -> Número entero (%d)\n", $1);
      }
    | DECIMAL {
          $$ = $1;
          printf("GRAMÁTICA: Expresión -> Número decimal (%f)\n", $1);
      }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "ERROR: %s\n", s);
}

int main(void) {
    printf("Ingresa expresiones matemáticas (Ctrl+D para terminar):\n\n");
    yyparse();
    return 0;
}

