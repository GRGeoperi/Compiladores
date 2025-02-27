#include "operaciones.h"

void Liberar_Memoria(lenguaje A)
{
    for (int i = 0; i < A.longitud; i++)
    {
        free(A.conjunto[i]);
    }
    free(A.conjunto);
}

void Imprimir_Conjunto(lenguaje A)
{
    for (int i = 0; i < A.longitud; i++)
    {
        printf("%s ", A.conjunto[i]);
    }
    printf("\n");
}

/*
    Toma cada elemento del lenguaje y lo compara con los elementos restantes
    Si encuentra un elemento repetido, lo elimina y mueve los elementos restantes a la izquierda
    Retorna el lenguaje actualizado
*/
lenguaje Eliminar_Repeticiones(lenguaje A)
{
    for (int i = 0; i < A.longitud; i++)
    {
        for (int j = i + 1; j < A.longitud; j++)
        {
            if (strcmp(A.conjunto[i], A.conjunto[j]) == 0)
            {
                free(A.conjunto[j]);
                // Mover los elementos a la izquierda
                for (int k = j; k < A.longitud - 1; k++)
                {
                    A.conjunto[k] = A.conjunto[k + 1];
                }
                A.longitud--;
            }
        }
    }
    return A;
}

/*
    Crea un nuevo lenguaje con la longitud de A + B, luego copia los elementos
    de A y B al nuevo lenguaje y elimina los elementos repetidos
    Retorna el lenguaje actualizado
*/
lenguaje Unir_Lenguajes(lenguaje A, lenguaje B)
{
    lenguaje resultado;
    resultado.longitud = A.longitud + B.longitud;
    resultado.conjunto = (char **)malloc(resultado.longitud * sizeof(char *));

    // Copiar A a resultado
    for (int i = 0; i < A.longitud; i++)
    {
        resultado.conjunto[i] = (char *)malloc(strlen(A.conjunto[i]) * sizeof(char));
        strcpy(resultado.conjunto[i], A.conjunto[i]);
    }

    // Copiar B a resultado
    for (int i = A.longitud; i < resultado.longitud; i++)
    {
        resultado.conjunto[i] = (char *)malloc(strlen(B.conjunto[i - A.longitud]) * sizeof(char));
        strcpy(resultado.conjunto[i], B.conjunto[i - A.longitud]);
    }

    // Eliminar repetidos
    resultado = Eliminar_Repeticiones(resultado);

    return resultado;
}

/*
    Crea un nuevo lenguaje, concatena cada elemento
    de A con B y lo agrega al nuevo lenguaje.
    Retorna el lenguaje actualizado
*/
lenguaje Concatenar_Elementos(lenguaje A, lenguaje B)
{
    lenguaje resultado;
    resultado.longitud = A.longitud * B.longitud;
    resultado.conjunto = (char **)malloc(resultado.longitud * sizeof(char *));

    int contador = 0;
    for (int i = 0; i < A.longitud; i++)
    {
        for (int j = 0; j < B.longitud; j++)
        {
            resultado.conjunto[contador] = (char *)malloc(strlen(A.conjunto[i]) + strlen(B.conjunto[j]) + 1);
            strcpy(resultado.conjunto[contador], A.conjunto[i]);
            strcat(resultado.conjunto[contador], B.conjunto[j]);
            contador++;
        }
    }

    return resultado;
}

/*
    Crea un nuevo lenguaje, concatena cada elemento de A con B
    lo agrega al nuevo lenguaje y elimina los elementos repetidos
    Retorna el lenguaje actualizado
*/
lenguaje Concatenar_Lenguajes(lenguaje A, lenguaje B)
{
    lenguaje resultado;

    // Concatenar A con B
    resultado = Concatenar_Elementos(A, B);

    // Eliminar repetidos
    resultado = Eliminar_Repeticiones(resultado);

    return resultado;
}
/*
    Crea un nuevo lenguaje, copia A al nuevo lenguaje
    Luego concatena A con A Potencia veces teniendo en cuenta si la potencia es cero,
    positiva o negativa. Si es negativa, invierte cada cadena del resultado
    Retorna el lenguaje actualizado
*/
lenguaje Potencia_Lenguaje(lenguaje A, int Potencia)
{
    lenguaje resultado;

    resultado.longitud = A.longitud;
    resultado.conjunto = (char **)malloc(resultado.longitud * sizeof(char *));

    // Copiar A a resultado
    for (int i = 0; i < A.longitud; i++)
    {
        resultado.conjunto[i] = (char *)malloc(strlen(A.conjunto[i]) * sizeof(char));
        strcpy(resultado.conjunto[i], A.conjunto[i]);
    }

    if (Potencia == 0)
    {
        printf("Lambda");
        resultado.longitud = 0;
        resultado.conjunto = NULL;
        return resultado;
    }

    if (Potencia > 0)
    {
        // Generar las potencias del lenguaje
        for (int p = 1; p < Potencia; p++)
        {
            resultado = Concatenar_Lenguajes(resultado, A);
        }
        return resultado;
    }

    if (Potencia < 0)
    {
        // Generar las potencias del lenguaje
        for (int p = 1; p < abs(Potencia); p++)
        {
            resultado = Concatenar_Lenguajes(resultado, A);
        }

        // Invertir cada cadena del resultado
        for (int i = 0; i < resultado.longitud; i++)
        {
            char *cadena = resultado.conjunto[i];
            int longitud = strlen(cadena);
            for (int j = 0; j < longitud / 2; j++)
            {
                char auxiliar = cadena[j];
                cadena[j] = cadena[longitud - j - 1];
                cadena[longitud - j - 1] = auxiliar;
            }
        }
        return resultado;
    }
}
