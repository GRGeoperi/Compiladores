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
            indice = 0;
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

quintupla Crear_AFND(tupla Estados, tupla Alfabeto, char *EstadoInicial, tupla EstadosAceptación, transiciones FuncionTransicion)
{
    quintupla quintupla;
    quintupla.qoppa = Estados;
    quintupla.sigma = Alfabeto;
    quintupla.qoppaSubZero = EstadoInicial;
    quintupla.digamma = EstadosAceptación;
    quintupla.delta = FuncionTransicion;
    return quintupla;
}

int Transicion_Existe(transiciones FuncionTransicion, char *EstadoActual, char Simbolo)
{
    for (int i = 0; i < FuncionTransicion.cardinalidad; i++)
    {
        if (FuncionTransicion.conjunto[i][0] == EstadoActual[0] && FuncionTransicion.conjunto[i][1] == Simbolo)
        {
            return 1;
        }
    }
    return 0;
}

int Existe_Transicion_Error(transiciones FuncionTransicion)
{
    for (int i = 0; i < FuncionTransicion.cardinalidad; i++)
    {
        if (FuncionTransicion.conjunto[i][2] == 'E')
        {
            return 1;
        }
    }
    return 0;
}

transiciones Agregar_Transiciones_Faltantes(transiciones FuncionTransicion, tupla Estados, tupla Alfabeto)
{
    // Agregar transiciones de los estados si no existen
    for (int i = 0; i < Estados.cardinalidad; i++)
    {
        for (int j = 0; j < Alfabeto.cardinalidad; j++)
        {
            if (!Transicion_Existe(FuncionTransicion, &Estados.conjunto[i], Alfabeto.conjunto[j]))
            {
                char nuevaTransicion[4] = {Estados.conjunto[i], Alfabeto.conjunto[j], 'E', '\0'};
                FuncionTransicion.conjunto = realloc(FuncionTransicion.conjunto, (FuncionTransicion.cardinalidad + 1) * sizeof(char *));
                FuncionTransicion.conjunto[FuncionTransicion.cardinalidad] = strdup(nuevaTransicion);
                FuncionTransicion.cardinalidad++;
            }
        }
    }
    // Si existe alguna transicion a E entonces agregar transiciones a sí mismo
    if (Existe_Transicion_Error(FuncionTransicion))
    {
        for (int j = 0; j < Alfabeto.cardinalidad; j++)
        {
            char nuevaTransicion[4] = {'E', Alfabeto.conjunto[j], 'E', '\0'};
            FuncionTransicion.conjunto = realloc(FuncionTransicion.conjunto, (FuncionTransicion.cardinalidad + 1) * sizeof(char *));
            FuncionTransicion.conjunto[FuncionTransicion.cardinalidad] = strdup(nuevaTransicion);
            FuncionTransicion.cardinalidad++;
        }
    }
    return FuncionTransicion;
}
