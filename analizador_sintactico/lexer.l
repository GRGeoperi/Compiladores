%{
#include "parser.tab.h"
#include <stdlib.h>
#include <stdio.h>
%}

digit       [0-9]
sign        [\+\-]?
decimal     {sign}({digit}+\.{digit}*|{digit}*\.{digit}+)

%%

{sign}{digit}+ {
    yylval.num = atoi(yytext);
    printf("LEXEMA: Número entero '%s' => %d\n", yytext, yylval.num);
    return ENTERO;
}

{decimal} {
    yylval.dec = atof(yytext);
    printf("LEXEMA: Número decimal '%s' => %f\n", yytext, yylval.dec);
    return DECIMAL;
}

[+*/-] {
    printf("LEXEMA: Operador '%s'\n", yytext);
    return *yytext;
}

[Mm][Oo][Dd] {
    printf("LEXEMA: Función módulo 'MOD'\n");
    return MOD;
}

"(" {
    printf("LEXEMA: Paréntesis izquierdo '('\n");
    return '(';
}

")" {
    printf("LEXEMA: Paréntesis derecho ')'\n");
    return ')';
}

"," {
    printf("LEXEMA: Coma ','\n");
    return COMA;
}

\n {
    return '\n';
}

[ \t\r]+   ;

. {
    printf("LEXEMA: Carácter no reconocido '%s'\n", yytext);
}

%%

int yywrap() {
    return 1;
}
