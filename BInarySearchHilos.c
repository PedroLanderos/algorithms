//Binary Search DONE
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include<pthread.h>

#define Num_hilos 5
//divide el arreglo en 2 partes, el inicio y el final
/*
    1. Ordenar el arreglo de menor a mayor
    2. Comparar si el elemento actual(1) es el elemento a buscar
    3. Si no es, comparar la mitad del arreglo <--- hay que encontrar la mitad del arreglo
    4. Si el elemento es mayor eliminar la parte izquierda, si es menor eliminar la parte derecha
    5. LLamar recurisvamente la llamada hasta encontrar el elemento
*/


//Metodo ordenamiento quick de la practica anterior
//#region Ordenar

void Rellenar(int *vector, int size, const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    int i;
    for (i = 0; i < size; i++)
    {
        if (fscanf(archivo, "%d", &vector[i]) != 1)
        {
            printf("Error al leer el archivo.\n");
            break;
        }
    }

    fclose(archivo);
}

void Intercambiar(int *vector, int i, int j)
{
    int temp = *(vector + j);
    *(vector + j) = *(vector + i);
    *(vector + i) = temp;
}

int Pivot(int *vector, int p, int r)
{
    int i, j, piv;
    piv = vector[p];
    i = p + 1;
    j = r;

    while(i <= j)
    {
        while(*(vector + i) <= piv && i <= r)
            i++;
        while(*(vector + j) > piv)
            j--;
        if (i < j)
            Intercambiar(vector, i , j);
    }

    Intercambiar(vector, p , j);

    return j;
}

void Quick(int *vector, int p, int r)
{
    int j;
    if (p < r)
    {
        j = Pivot(vector, p, r);
        Quick(vector, p, j - 1);
        Quick(vector, j + 1, r);
    }
}

// #endregion

//estructura de los hilos
typedef struct
{
	int valorBuscado;
 	int *vector; //parte del vector que se recorrera
	int inicio; //inicio de la parte en donde se buscara
	int final; //final de la parte en donde se buscara
}Hilo;

//parametros necesarios, numero a buscar, inicio y fin
int Search(int n, int *vector, int start, int end)
{
    if(start > end) //caso base
        return INT_MAX;  //valor default (int mas grande)

    int half = (start + end) / 2; //obtener la mitad del arreglo

    if(*(vector + half) == n) //si el valor esta en la posicion de enmedio (logica de BS)
        return 1; //se encontro el numero
    else
    {
        if(*(vector + half) < n) 
            return Search(n, vector, half + 1, end); //regresar la mitad derecha
        else
            return Search(n, vector, start, half - 1); //regresar la mitad izquierrda
    }
}

void *BusquedaHilos(void *apuntador) //se pasa un tipo de dato puntero para poder manejar los hilos
{
	Hilo *hilo = (Hilo *)apuntador;//se convierte el tipo de dato apuntador a la estructura requerida de los hilos para poder acceder a sus propiedades
	
	//se llama a la funcion de busqueda binaria pero solo la parte que le toca del hilo
	int result = Search(hilo->valorBuscado, hilo->vector, hilo->inicio, hilo->final);  

	if(result == 1)
		printf("Valor encontrado");
	else if(result == INT_MAX)
        printf("Valor no encontrado");
}

void Imprimir(int *vector, int n)
{
    int i;
    for(i  = 0; i < n; i++)
    {
        printf("%i ", *(vector + i));
    }

    printf("\n\n");
}

int main(int argc, char const *argv[])
{
    int n = atoi(argv[1]);
    int value = atoi(argv[2]);
    int *vector = (int *)malloc(n * sizeof(int));  // Corregir la definición de vector

    Rellenar(vector, n, "NumerosPruebas.txt");
    Imprimir(vector, n);
    Quick(vector, 0, n - 1);
    Imprimir(vector, n);

    int i;
    int tamanoSeccionHilo = n / Num_hilos;
    pthread_t hilos[Num_hilos];
    Hilo hilo[Num_hilos];

    for (i = 0; i < Num_hilos; i++)
    {
        hilo[i].valorBuscado = value;
        hilo[i].vector = vector;
        hilo[i].inicio = i * tamanoSeccionHilo;
        hilo[i].final = (i + 1) * tamanoSeccionHilo - 1;

        pthread_create(&hilos[i], NULL, BusquedaHilos, (void *)&hilo[i]);
    }

    for (i = 0; i < Num_hilos; i++)
    {
        pthread_join(hilos[i], NULL); //terminar que el hilo finalice su parte
    }

    free(vector);  // Liberar la memoria después de usarla

    return 0;
}