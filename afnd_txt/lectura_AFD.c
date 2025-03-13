#include "lectura_AFD.h"

tupla Obtener_Tupla(FILE *Archivo, int LineaObjetivo)
{
    tupla objetivo;
    objetivo.conjunto = NULL;
    objetivo.cardinalidad = 0;
    char cadenaCruda[256];
    char cadenaTratada[256];
    int indice = 0;
    int lineaActual = 0;

    rewind(Archivo);
    while (fgets(cadenaCruda, sizeof(cadenaCruda), Archivo) != NULL)
    {
        if (lineaActual == LineaObjetivo)
        {
            cadenaCruda[strcspn(cadenaCruda, "\n")] = '\0';
            for (int i = 0; cadenaCruda[i] != '\0'; i++)
            {
                if (cadenaCruda[i] != ',')
                {
                    cadenaTratada[indice++] = cadenaCruda[i];
                }
            }
            cadenaTratada[indice] = '\0';
            objetivo.conjunto = strdup(cadenaTratada);
            objetivo.cardinalidad = strlen(cadenaTratada);
            break;
        }
        lineaActual++;
    }
    return objetivo;
}

char *Obtener_Estado_Inicial(FILE *Archivo, int LineaObjetivo)
{
    char *estadoInicial = NULL;
    char cadenaCruda[256];
    int lineaActual = 0;

    rewind(Archivo);
    while (fgets(cadenaCruda, sizeof(cadenaCruda), Archivo) != NULL)
    {
        if (lineaActual == LineaObjetivo)
        {
            cadenaCruda[strcspn(cadenaCruda, "\n")] = '\0';
            estadoInicial = strdup(cadenaCruda);
            break;
        }
        lineaActual++;
    }
    return estadoInicial;
}

transiciones Obtener_Transiciones(FILE *Archivo, int LineaObjetivo)
{
    transiciones objetivo;
    objetivo.conjunto = NULL;
    objetivo.cardinalidad = 0;
    char cadenaCruda[256];
    char cadenaTratada[256];
    int indice = 0;
    int lineaActual = 0;

    rewind(Archivo);
    while (fgets(cadenaCruda, sizeof(cadenaCruda), Archivo) != NULL)
    {
        if (lineaActual >= LineaObjetivo)
        {
            cadenaCruda[strcspn(cadenaCruda, "\n")] = '\0';
            for (int i = 0; cadenaCruda[i] != '\0'; i++)
            {
                if (cadenaCruda[i] != ',')
                {
                    cadenaTratada[indice++] = cadenaCruda[i];
                }
            }
            cadenaTratada[indice] = '\0';
            objetivo.conjunto = realloc(objetivo.conjunto, (objetivo.cardinalidad + 1) * sizeof(char *));
            objetivo.conjunto[objetivo.cardinalidad] = strdup(cadenaTratada);
            objetivo.cardinalidad++;
        }
        lineaActual++;
    }
    return objetivo;
}
