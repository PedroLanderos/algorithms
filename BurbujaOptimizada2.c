#include<stdlib.h>
#include<stdio.h>

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

int ValidarN(const char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "r");

    int contador = 0;
    int valor;

    while (fscanf(archivo, "%d", &valor) == 1)
    {
        contador++;
    }

    fclose(archivo);

    return contador;
}

void Burbuja(int *vector, int n)
{
    char cambios = 's';
    int i = 0, j, aux;

    while(i <= (n - 2) && cambios != 'n')
    {
        cambios = 'n';
        for(j = 0; j <= ((n - 2) - i); j++)
        {
            if (*(vector + j) > *(vector + (j + 1)))
            {
                aux = *(vector + j);
                *(vector + j) = *(vector + (j + 1));
                *(vector + (j + 1)) = aux;
                cambios = 's';
            }
        }
        i = i + 1;
    }
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
    int *vector;
    int n, nValida;
    scanf("%i", &n);

    vector = (int*)malloc(n*sizeof(int));

	nValida =  ValidarN("NumerosPruebas.txt");
    if(n > nValida)
        printf("No hay suficientes elementos\n");
    else
    {
        Rellenar(vector, n, "NumerosPruebas.txt");
        Imprimir(vector, n);
        Burbuja(vector, n);
        Imprimir(vector, n);
    }
    

    return 0;
}


