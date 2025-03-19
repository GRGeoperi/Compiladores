#include "lectura_AFD.c"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Uso: %s <archivo_entrada> <cadena>\n", argv[0]);
        return 1;
    }

    tupla estados;
    tupla alfabeto;
    char *estadoInicial;
    tupla estadosAceptacion;
    transiciones transiciones;
    quintupla AFND;
    const char *cadena;
    int resultado;

    FILE *archivo = fopen(argv[1], "r");

    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return 1;
    }
    
    estados = Obtener_Tupla(archivo, 0);
    alfabeto = Obtener_Tupla(archivo, 1);
    estadoInicial = Obtener_Estado_Inicial(archivo, 2);
    estadosAceptacion = Obtener_Tupla(archivo, 3);
    transiciones = Obtener_Transiciones(archivo, 4);
    transiciones = Agregar_Transiciones_Faltantes(transiciones, estados, alfabeto);
    AFND = Crear_AFND(estados, alfabeto, estadoInicial, estadosAceptacion, transiciones);
    cadena = argv[2];
    resultado = Procesar_Cadena(AFND, cadena);

    if (resultado)
    {
        printf("La cadena %s es aceptada por el AFND.\n", cadena);
    }
    else
    {
        printf("La cadena %s no es aceptada por el AFND.\n", cadena);
    }

    Guardar_AFND(AFND, "AFND_resultado.txt");

    free(estadoInicial);
    free(estados.conjunto);
    free(alfabeto.conjunto);
    free(estadosAceptacion.conjunto);
    for (int i = 0; i < transiciones.cardinalidad; i++)
    {
        free(transiciones.conjunto[i]);
    }
    free(transiciones.conjunto);
    fclose(archivo);
    
    return 0;
}
