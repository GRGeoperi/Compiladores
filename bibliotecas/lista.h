#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    char *dato;
    struct nodo *siguiente;
} Nodo;

typedef struct lista {
    Nodo *cabeza;
    Nodo *cola;
} Lista;

Lista *Crear_Lista();
void Insertar_Lista(Lista *lista, char *dato);
void Eliminar_Elemento(Lista *lista, char *dato);
void Eliminar_Lista(Lista *lista);
void Imprimir_Lista(Lista *lista);
