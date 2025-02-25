#include "operaciones.c"

int main(void)
{
    lenguaje ejemploA;
    lenguaje ejemploB;
    int opcion;
    int repeticion = 2;

    printf("Ingrese la longitud del conjunto A: ");
    scanf("%d", &ejemploA.longitud);

    ejemploA.conjunto = (char **)malloc(ejemploA.longitud * sizeof(char *));
    for (int i = 0; i < ejemploA.longitud; i++)
    {
        ejemploA.conjunto[i] = (char *)malloc(100 * sizeof(char));
        printf("Ingrese el elemento %d del conjunto A: ", i + 1);
        scanf("%s", ejemploA.conjunto[i]);
    }

    printf("\n");
    printf("Ingrese la longitud del conjunto B: ");
    scanf("%d", &ejemploB.longitud);

    ejemploB.conjunto = (char **)malloc(ejemploB.longitud * sizeof(char *));
    for (int i = 0; i < ejemploB.longitud; i++)
    {
        ejemploB.conjunto[i] = (char *)malloc(100 * sizeof(char));
        printf("Ingrese el elemento %d del conjunto B: ", i + 1);
        scanf("%s", ejemploB.conjunto[i]);
    }

    do
    {
        printf("\n");
        printf("1. Unir lenguajes\n");
        printf("2. Concatenar lenguajes\n");
        printf("3. Potencia de un lenguaje\n");
        printf("Ingrese una opcion: ");
        scanf("%d", &opcion);
        printf("\n");
    
        switch (opcion)
        {
        case 1:
            lenguaje unionAB;
            unionAB = Unir_Lenguajes(ejemploA, ejemploB);
            printf("Union de lenguajes:\n");
            Imprimir_Conjunto(unionAB);
            Liberar_Memoria(unionAB);
            printf("\nProbar otra operacion?\n");
            printf("1. Si\n");
            printf("2. No\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &repeticion);
            break;
        case 2:
            lenguaje concatenacionAB;
            lenguaje concatenacionBA;
            concatenacionAB = Concatenar_Lenguajes(ejemploA, ejemploB);
            concatenacionBA = Concatenar_Lenguajes(ejemploB, ejemploA);
            printf("Concatenacion de lenguajes A con B:\n");
            Imprimir_Conjunto(concatenacionAB);
            printf("Concatenacion de lenguajes B con A:\n");
            Imprimir_Conjunto(concatenacionBA);
            Liberar_Memoria(concatenacionBA);
            Liberar_Memoria(concatenacionAB);
            printf("\nProbar otra operacion?\n");
            printf("1. Si\n");
            printf("2. No\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &repeticion);
            break;
        case 3:
            lenguaje potenciado;
            int potencia;
            int lenguajeAPotenciar;
    
            printf("Ingrese la potencia: ");
            scanf("%d", &potencia);
    
            printf("1. lenguaje A^%d\n", potencia);
            printf("2. lenguaje B^%d\n", potencia);
            printf("Ingrese una opcion: ");
            scanf("%d", &lenguajeAPotenciar);
            printf("\n");
    
            switch (lenguajeAPotenciar)
            {
            case 1:
                potenciado = Potencia_Lenguaje(ejemploA, potencia);
                printf("Lenguaje A^%d\n", potencia);
                Imprimir_Conjunto(potenciado);
                Liberar_Memoria(potenciado);
                printf("\nProbar otra operacion?\n");
                printf("1. Si\n");
                printf("2. No\n");
                printf("Ingrese una opcion: ");
                scanf("%d", &repeticion);
                break;
            case 2:
                potenciado = Potencia_Lenguaje(ejemploB, potencia);
                printf("Lenguaje B^%d\n", potencia);
                Imprimir_Conjunto(potenciado);
                Liberar_Memoria(potenciado);
                printf("\nProbar otra operacion?\n");
                printf("1. Si\n");
                printf("2. No\n");
                printf("Ingrese una opcion: ");
                scanf("%d", &repeticion);
                break;
            default:
                printf("Opcion no valida\n");
                printf("\nProbar otra vez?\n");
                printf("1. Si\n");
                printf("2. No\n");
                printf("Ingrese una opcion: ");
                scanf("%d", &repeticion);
                break;
            }
            break;
        default:
            printf("Opcion no valida\n");
            printf("\nProbar otra vez\n");
            printf("1. Si\n");
            printf("2. No\n");
            printf("Ingrese una opcion: ");
            scanf("%d", &repeticion);
            break;
        }
    } while (repeticion == 1);

    Liberar_Memoria(ejemploA);
    Liberar_Memoria(ejemploB);

    return 0;
}
