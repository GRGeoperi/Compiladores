#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Lenguaje
{
    char **conjunto;
    int longitud;
} lenguaje;

void Liberar_Memoria(lenguaje A);
void Imprimir_Conjunto(lenguaje A);
lenguaje Eliminar_Repeticiones(lenguaje A);
lenguaje Unir_Lenguajes(lenguaje A, lenguaje B);
lenguaje Concatenar_Elementos(lenguaje A, lenguaje B);
lenguaje Concatenar_Lenguajes(lenguaje A, lenguaje B);
lenguaje Potencia_Lenguaje(lenguaje A, int Potencia);
