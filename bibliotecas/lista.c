#include "lista.h"

Lista *Crear_Lista()
{
    Lista *lista = (Lista *)malloc(sizeof(Lista));
    lista->cabeza = NULL;
    lista->cola = NULL;
    return lista;
}

void Insertar_Lista(Lista *lista, char *dato)
{
    Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
    nodo->dato = dato;
    nodo->siguiente = NULL;
    if (lista->cabeza == NULL)
    {
        lista->cabeza = nodo;
        lista->cola = nodo;
    }
    else
    {
        lista->cola->siguiente = nodo;
        lista->cola = nodo;
    }
}

void Eliminar_Elemento(Lista *lista, char *dato)
{
    Nodo *nodo = lista->cabeza;
    Nodo *anterior = NULL;
    while (nodo != NULL)
    {
        if (nodo->dato == dato)
        {
            if (anterior == NULL)
            {
                lista->cabeza = nodo->siguiente;
            }
            else
            {
                anterior->siguiente = nodo->siguiente;
            }
            if (nodo == lista->cola)
            {
                lista->cola = anterior;
            }
            free(nodo);
            return;
        }
        anterior = nodo;
        nodo = nodo->siguiente;
    }
}

void Eliminar_Lista(Lista *lista)
{
    Nodo *nodo = lista->cabeza;
    Nodo *siguiente;
    while (nodo != NULL)
    {
        siguiente = nodo->siguiente;
        free(nodo);
        nodo = siguiente;
    }
    free(lista);
}

void Imprimir_Lista(Lista *lista)
{
    Nodo *nodo = lista->cabeza;
    while (nodo != NULL)
    {
        printf("%s ", nodo->dato);
        nodo = nodo->siguiente;
    }
    printf("\n");
}
