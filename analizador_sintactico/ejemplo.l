dir [0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5]
NUM [0-9]+
%%
{dir}"."{dir}"."{dir}"."{dir} {
    printf("IP valida\n");
}

{NUM} {
    printf("Numero enetero %s\n", yytext);
}

"+"|"*" {
    printf("Signo de operacion\n");
}

"("|")" {
    printf("Signo parentesis\n");
}

"," {
    printf("Coma\n");
}

[Mm][Oo][dD] {
    printf("Modulo\n");
}

"\n" {
    printf("Salto de linea\n");
}
