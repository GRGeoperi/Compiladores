variable [a-zA-Z_][a-zA-Z0-9_]*
entero [-]?[0-9]+
decimal [-]?[0-9]+\.[0-9]+
potencia [-]?[0-9]+(\.[0-9]+)?\^[-]?[0-9]+
suma [-]?[0-9]+(\.[0-9]+)?\+[-]?[0-9]+(\.[0-9]+)?
resta [-]?[0-9]+(\.[0-9]+)?-[-]?[0-9]+(\.[0-9]+)?
multiplicacion [-]?[0-9]+(\.[0-9]+)?\*[-]?[0-9]+(\.[0-9]+)?
division [-]?[0-9]+(\.[0-9]+)?"/"[-]?[1-9][0-9]*(\.[0-9]+)?
modulo [-]?[0-9]+%[-]?[1-9][0-9]*
%%
{variable} {
    printf("Nombre de variable");
}

{entero} {
    printf("Número entero");
}

{decimal} {
    printf("Número decimal");
}

{potencia} {
    printf("Potencia");
}

{suma} {
    printf("Operación de suma");
}

{resta} {
    printf("Operación de resta");
}

{multiplicacion} {
    printf("Operación de multiplicación");
}

{division} {
    printf("Operación de división");
}

{modulo} {
    printf("Operación de módulo");
}
