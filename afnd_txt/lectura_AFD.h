#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Almacena "estados", "alfabeto" y "estadosAceptacion" del txt
typedef struct Tupla
{
    char *conjunto;
    int cardinalidad;
}tupla;

// Reune las transiciones definidas del txt
typedef struct Transiciones
{
    char **conjunto;
    int cardinalidad;
}transiciones;

// Define un autómata finito determinista
typedef struct Quintupla
{
    tupla qoppa;
    tupla sigma;
    char *qoppaSubZero;
    transiciones delta;
    tupla digamma;
}quintupla;

// Lee el archivo de texto y obtiene la tupla dada por la línea objetivo
tupla Obtener_Tupla(FILE *Archivo, int LineaObjetivo);

// Lee el archivo de texto y obtiene el estado inicial dada por la línea objetivo
char *Obtener_Estado_Inicial(FILE *Archivo, int LineaObjetivo);

// Lee el archivo de texto y obtiene todas las transiciones dadas desde la línea objetivo hasta el final del archivo
transiciones Obtener_Transiciones(FILE *Archivo, int LineaObjetivo);

// Crea un autómata finito no determinista a partir de las tuplas y transiciones obtenidas
quintupla Crear_AFND(tupla Estados, tupla Alfabeto, char *EstadoInicial, tupla EstadosAceptacion, transiciones FuncionTransicion);

int Transicion_Existe(transiciones FuncionTransicion, char *EstadoActual, char Simbolo);

int Existe_Transicion_Error(transiciones FuncionTransicion);

transiciones Agregar_Transiciones_Faltantes(transiciones FuncionTransicion, tupla Estados, tupla Alfabeto);

void Procesar_Cadena_AFND(quintupla AFND, const char *cadena, char *estadoActual, int indice, char *camino, int *aceptada);

int Procesar_Cadena(quintupla AFND, const char *cadena);

void Guardar_AFND(quintupla AFND, const char *nombreArchivo);
