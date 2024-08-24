#include <stdio.h>                                                       
#include <stdlib.h>                                                      

void Rellenar(int *vector, int size, const char *nombreArchivo          )
{
    FILE *archivo = fopen(nombreArchivo, "r"                           );

    if (archivo == NULL                                                 )
    {
        printf("No se pudo abrir el archivo.\n"                        );
        return                                                          ;
    }

    int i                                                               ;
    for (i = 0; i < size; i++                                           )
    {
        if (fscanf(archivo, "%d", &vector[i]) != 1                      )
        {
            printf("Error al leer el archivo.\n"                       );
            break                                                       ;
        }
    }

    fclose(archivo                                                     );
}



void Intercambiar(int *vector, int i, int j                             )
{
    int temp = *(vector + j                                            );
    *(vector + j) = *(vector + i                                       );
    *(vector + i) = temp                                                ;
}

int Pivot(int *vector, int p, int r                                     )
{
    int i, j, piv                                                       ;
    piv = vector[p]                                                     ;
    i = p + 1                                                           ;
    j = r                                                               ;

    while(i <= j                                                        )
    {
        while(*(vector + i) <= piv && i <= r                            )
            i++                                                         ;
        while(*(vector + j) > piv                                       )
            j--                                                         ;
        if (i < j                                                       )
            Intercambiar(vector, i , j                                 );
    }

    Intercambiar(vector, p , j                                         );

    return j                                                            ;
}

void Quick(int *vector, int p, int r                                    )
{
    int j                                                               ;
    if (p < r                                                           )
    {
        j = Pivot(vector, p, r                                         );
        Quick(vector, p, j - 1                                         );
        Quick(vector, j + 1, r                                         );
    }
}

void Imprimir(int *vector, int n                                        )
{
    int i                                                               ;
    for(i  = 0; i < n; i++                                              )
    {
        printf("%i ", *(vector + i                                    ));
    }

    printf("\n\n"                                                      );
}

int main(int argc, char const *argv[]                                   )
{
    int n                                                               ;
    scanf("%i", &n                                                     );
    int *vector = (int*)malloc(n * sizeof(int                         ));

    Rellenar(vector, n, "NumerosPruebas.txt"                           );
    Imprimir(vector, n                                                 );
    Quick(vector, 0, n - 1                                             );
    Imprimir(vector, n                                                 );
    
    return 0                                                            ;
}