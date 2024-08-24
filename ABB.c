#include<stdio.h>                                                                                                                                
#include<stdlib.h>                                                                                                                               

typedef struct Nodo                                                                                                                              
{
    int valor                                                                                                                                   ;
    struct Nodo* izquierdo                                                                                                                      ;
    struct Nodo* derecho                                                                                                                        ;
}Nodo                                                                                                                                          ; 

//funcion para crear nodos                                                                                                                       
Nodo* NuevoNodo(int value                                                                                                                       )
{
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo)); //crea el espacio de memoria                                                                      
    nuevo->valor = value; //asigna el valor                                                                                                      
    //asigna como null a sus hijos                                                                                                               
    nuevo->izquierdo = NULL                                                                                                                    ; 
    nuevo->derecho = NULL                                                                                                                       ;
    
    //hace un return del nodo creado                                                                                                             
    return nuevo                                                                                                                                ;
}

Nodo* ABB(Nodo* raiz, int value                                                                                                                 )
{
    //si es el primer valor                                                                                                                      
    if (raiz == NULL                                                                                                                            )
        return NuevoNodo(value                                                                                                                 );
    
    //si tiene al menos 1 nodo                                                                                                                   
    if(value < raiz->valor                                                                                                                     ) 
        raiz->izquierdo = ABB(raiz->izquierdo, value); //se llama recursivamente a la funcion para ordenar el nodo en el lugar indicado          
    else if(value > raiz->valor                                                                                                                 )
        raiz->derecho = ABB(raiz->derecho, value                                                                                               );

    //REGRESAR EL NODO EN SU LUGAR                                                                                                               
    return raiz                                                                                                                                 ;
}

void Rellenar(Nodo** raiz, const char* nombreArchivo, int n                                                                                    ) 
{
    FILE* archivo = fopen(nombreArchivo, "r"                                                                                                   );

     if (archivo == NULL                                                                                                                       ) 
     {
        printf("No se pudo abrir el archivo.\n"                                                                                                );
        return                                                                                                                                  ;
    }

    int valor                                                                                                                                   ;
    int elementosLeidos = 0                                                                                                                     ;

    while (elementosLeidos < n && fscanf(archivo, "%i", &valor) == 1                                                                            )
    {
        *raiz = ABB(*raiz, valor                                                                                                               );
        elementosLeidos++                                                                                                                       ;
    }

    fclose(archivo                                                                                                                             );
}


void Imprimir(Nodo *nodo                                                                                                                        )
{
    if(nodo != NULL                                                                                                                             )
    {
        //imprime in orden (el arbol ya esta ordenado                                                                                           )
        Imprimir(nodo->izquierdo                                                                                                               );
        printf("%i ", nodo->valor                                                                                                              );
        Imprimir(nodo->derecho                                                                                                                 );
    }
    
}

int main(int argc, char const *argv[]                                                                                                           )
{
    int n                                                                                                                                       ;
    scanf("%i", &n                                                                                                                             );
    //inicializar en null el arbol                                                                                                              ;
    Nodo *raiz = NULL                                                                                                                           ;
    //rellena el arbol con el txt                                                                                                                
    Rellenar(&raiz, "NumerosPruebas.txt", n                                                                                                    );
    //imprime in orden el arbo y por lo tanto el vector ordenado                                                                                 
    Imprimir(raiz                                                                                                                              );
    
    return 0                                                                                                                                    ;
}


