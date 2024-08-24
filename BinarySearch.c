#include<stdio.h>                                                                                          
#include <limits.h>                                                                                        
#include<stdlib.h>                                                                                         
//divide el arreglo en 2 partes, el inicio y el final                                                      
/*                                                                                                         
    1. Ordenar el arreglo de menor a mayor                                                                 
    2. Comparar si el elemento actual(1) es el elemento a buscar                                           
    3. Si no es, comparar la mitad del arreglo <--- hay que encontrar la mitad del arreglo                 
    4. Si el elemento es mayor eliminar la parte izquierda, si es menor eliminar la parte derecha          
    5. LLamar recurisvamente la llamada hasta encontrar el elemento                                        
*/                                                                                                         


/////Metodo ordenamiento quick de la practica anterior                                                     
// #region Ordenar                                                                                         

void Rellenar(int *vector, int size, const char *nombreArchivo                                            )
{
    FILE *archivo = fopen(nombreArchivo, "r"                                                             );

    if (archivo == NULL                                                                                   )
    {
        printf("No se pudo abrir el archivo.\n"                                                          );
        return                                                                                            ;
    }

    int i                                                                                                 ;
    for (i = 0; i < size; i++                                                                             )
    {
        if (fscanf(archivo, "%d", &vector[i]) != 1                                                        )
        {
            printf("Error al leer el archivo.\n"                                                         );
            break                                                                                         ;
        }
    }

    fclose(archivo                                                                                       );
}

void Intercambiar(int *vector, int i, int j                                                               )
{
    int temp = *(vector + j                                                                              );
    *(vector + j) = *(vector + i                                                                         );
    *(vector + i) = temp                                                                                  ;
}

int Pivot(int *vector, int p, int r                                                                       )
{
    int i, j, piv                                                                                         ;
    piv = vector[p]                                                                                       ;
    i = p + 1                                                                                             ;
    j = r                                                                                                 ;

    while(i <= j                                                                                          )
    {
        while(*(vector + i) <= piv && i <= r                                                              )
            i++                                                                                           ;
        while(*(vector + j) > piv                                                                         )
            j--                                                                                           ;
        if (i < j                                                                                         )
            Intercambiar(vector, i , j                                                                   );
    }

    Intercambiar(vector, p , j                                                                           );

    return j                                                                                              ;
}

void Quick(int *vector, int p, int r                                                                      )
{
    int j                                                                                                 ;
    if (p < r                                                                                             )
    {
        j = Pivot(vector, p, r                                                                           );
        Quick(vector, p, j - 1                                                                           );
        Quick(vector, j + 1, r                                                                           );
    }
}
// #endregion                                                                                              

//parametros necesarios, numero a buscar, inicio y fin                                                     
int Search(int n, int *vector, int start, int end                                                         )
{
    if(start > end) //caso base                                                                            
        return INT_MAX;  //valor default (int mas grande                                                  )

    int half = (start + end) / 2; //obtener la mitad del arreglo                                           

    if(*(vector + half) == n) //si el valor esta en la posicion de enmedio (logica de BS                  )
        return 1; //se encontro el numero                                                                  
    else                                                                                                   
    {
        if(*(vector + half) < n                                                                          ) 
            return Search(n, vector, half + 1, end); //regresar la mitad derecha                           
        else                                                                                               
            return Search(n, vector, start, half - 1); //regresar la mitad izquierrda                      
    }
}

void Imprimir(int *vector, int n                                                                          )
{
    int i                                                                                                 ;
    for(i  = 0; i < n; i++                                                                                )
    {
        printf("%i ", *(vector + i                                                                      ));
    }

    printf("\n\n"                                                                                        );
}

int main(int argc, char const *argv[]                                                                     )
{

    int n                                                                                                 ;
    scanf("%i", &n                                                                                       );
    int value                                                                                             ;
    scanf("%i", &value                                                                                   );
    int *vector = (int*)malloc(n * sizeof(int                                                           ));

    Rellenar(vector, n, "NumerosPruebas.txt"                                                             );
    Imprimir(vector, n                                                                                   );
    Quick(vector, 0, n - 1                                                                               );
    Imprimir(vector, n                                                                                   );
    int find = Search(value, vector, 0, n                                                                );

    if(find == 1                                                                                          )
        printf("Valor encontrado"                                                                        );
    else if(find == INT_MAX                                                                               )
        printf("Valor no encontrado"                                                                     );

    return 0                                                                                              ;
}