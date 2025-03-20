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
        // Agregar 'E' a la tupla de estados si no está presente
        int existeE = 0;
        for (int i = 0; i < Estados.cardinalidad; i++)
        {
            if (Estados.conjunto[i] == 'E')
            {
                existeE = 1;
                break;
            }
        }
        if (!existeE)
        {
            Estados.conjunto = realloc(Estados.conjunto, (Estados.cardinalidad + 1) * sizeof(char));
            Estados.conjunto[Estados.cardinalidad] = 'E';
            Estados.cardinalidad++;
        }

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

// ...existing code...

void Procesar_Cadena_AFND(quintupla AFND, const char *cadena, char *estadoActual, int indice, char *camino, int *aceptada)
{
    if (cadena[indice] == '\0')
    {
        for (int i = 0; i < AFND.digamma.cardinalidad; i++)
        {
            if (AFND.digamma.conjunto[i] == *estadoActual)
            {
                printf("Camino aceptado: %s\n", camino);
                *aceptada = 1;
                return;
            }
        }
        return;
    }

    char simbolo = cadena[indice];
    int simboloValido = 0;
    for (int i = 0; i < AFND.sigma.cardinalidad; i++)
    {
        if (AFND.sigma.conjunto[i] == simbolo)
        {
            simboloValido = 1;
            break;
        }
    }

    if (!simboloValido)
    {
        printf("Símbolo '%c' no pertenece al alfabeto en el estado '%c'. Intentando sin este símbolo.\n", simbolo, *estadoActual);
        Procesar_Cadena_AFND(AFND, cadena, estadoActual, indice + 1, camino, aceptada);
        return;
    }

    for (int j = 0; j < AFND.delta.cardinalidad; j++)
    {
        if (AFND.delta.conjunto[j][0] == *estadoActual && AFND.delta.conjunto[j][1] == simbolo)
        {
            char nuevoEstado = AFND.delta.conjunto[j][2];
            char nuevoCamino[256];
            snprintf(nuevoCamino, sizeof(nuevoCamino), "%s -> %c", camino, nuevoEstado);
            Procesar_Cadena_AFND(AFND, cadena, &nuevoEstado, indice + 1, nuevoCamino, aceptada);
        }
    }
}

int Procesar_Cadena(quintupla AFND, const char *cadena)
{
    char estadoActual = AFND.qoppaSubZero[0];
    char camino[256];
    snprintf(camino, sizeof(camino), "%c", estadoActual);
    int aceptada = 0;
    Procesar_Cadena_AFND(AFND, cadena, &estadoActual, 0, camino, &aceptada);
    return aceptada;
}

void Guardar_AFND(quintupla AFND, const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL)
    {
        perror("Error al crear el archivo");
        return;
    }

    fprintf(archivo, "%s\n", AFND.qoppa.conjunto);
    fprintf(archivo, "%s\n", AFND.sigma.conjunto);
    fprintf(archivo, "%s\n", AFND.qoppaSubZero);
    fprintf(archivo, "%s\n", AFND.digamma.conjunto);
    for (int i = 0; i < AFND.delta.cardinalidad; i++)
    {
        fprintf(archivo, "%s\n", AFND.delta.conjunto[i]);
    }

    fclose(archivo);
}
