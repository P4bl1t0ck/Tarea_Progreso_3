#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define MAX_LENGTH 50

void ingresarProducto(FILE *archivo, int ID[], char nombre[][MAX_LENGTH], float precio[], int stock[], int *producto);
void verProductos(FILE *archivo, int ID[], char nombre[][MAX_LENGTH], float precio[], int stock[], int producto);
void modificarProducto(FILE *archivo, int ID[], char nombre[][MAX_LENGTH], float precio[], int stock[], int producto);
void eliminarProducto(FILE *archivo, int ID[], char nombre[][MAX_LENGTH], float precio[], int stock[], int *producto);

int main() {
    int menu;
    int producto = 0;
    int ID[MAX], stock[MAX];
    char nombre[MAX][MAX_LENGTH];
    float precio[MAX];

    FILE *archivo; 
    archivo = fopen("inventario.txt", "w");
    archivo = fopen("inventario.txt", "r+");

    if (archivo == NULL) {
        printf("No se pudo abrir el archivo del inventario.\n");
        return 1;
    }

    do {
        printf("\n-- INVENTARIO --\n");
        printf("\n1. Ingresar un producto");
        printf("\n2. Ver productos");
        printf("\n3. Modificar un producto");
        printf("\n4. Eliminar un producto");
        printf("\n5. Salir");
        printf("\n\nIngrese una opcion: ");
        scanf("%d", &menu);

        switch(menu) {
            case 1:
                ingresarProducto(archivo, ID, nombre, precio, stock, &producto);
                break;
            case 2:
                verProductos(archivo, ID, nombre, precio, stock, producto);
                break;
            case 3:
                modificarProducto(archivo, ID, nombre, precio, stock, producto);
                break;
            case 4:
                eliminarProducto(archivo, ID, nombre, precio, stock, &producto);
                break;
            case 5:
                printf("\nSaliendo del programa...\n\n");
                break;
            default:
                printf("\nOpcion no valida.\n");
                break;
        }

    } while(menu != 5);

    fclose(archivo);
    return 0;
}

void ingresarProducto(FILE *archivo, int ID[], char nombre[][MAX_LENGTH], float precio[], int stock[], int *producto) {
    if (*producto < MAX) {
        int nuevoID;
        char nuevoNombre[MAX_LENGTH];
        float nuevoPrecio;
        int nuevoStock;

        printf("\nIngrese el ID del producto: ");
        scanf("%d", &nuevoID);
        printf("Ingrese el nombre del producto: ");
        scanf("%s", &nuevoNombre);
        printf("Ingrese el precio del producto: ");
        scanf("%f", &nuevoPrecio);
        printf("Ingrese el stock del producto: ");
        scanf("%d", &nuevoStock);

        fprintf(archivo, "%d %s %.2f %d\n", nuevoID, nuevoNombre, nuevoPrecio, nuevoStock);

        ID[*producto] = nuevoID;
        strcpy(nombre[*producto], nuevoNombre);
        precio[*producto] = nuevoPrecio;
        stock[*producto] = nuevoStock;

        (*producto)++;

        printf("\nProducto ingresado exitosamente.\n");
    } else {
        printf("\nNo se pueden ingresar mas productos. Limite alcanzado.\n");
    }
}

void verProductos(FILE *archivo, int ID[], char nombre[][MAX_LENGTH], float precio[], int stock[], int producto) {
    if (producto > 0) {
        printf("\n-- LISTA DE PRODUCTOS --\n");
        printf("\nID\tNombre\t\tPrecio\tStock");

        rewind(archivo);
        int i = 0;
        while (fscanf(archivo, "%d %s %f %d", &ID[i], nombre[i], &precio[i], &stock[i]) == 4) {
            printf("\n%d\t%s\t\t%.2f\t%d", ID[i], nombre[i], precio[i], stock[i]);
            i++;
        }
    } else {
        printf("\nNo hay productos ingresados.\n");
    }
}

void modificarProducto(FILE *archivo, int ID[], char nombre[][MAX_LENGTH], float precio[], int stock[], int producto) {
    int modificar, check = 0;
    printf("\nIngrese el ID del producto que desea modificar: ");
    scanf("%d", &modificar);

    for (int i = 0; i < producto; i++) {
        if (modificar == ID[i]) {
            printf("Ingrese el nuevo nombre del producto: ");
            scanf("%s", &nombre[i]);
            printf("Ingrese el nuevo precio del producto: ");
            scanf("%f", &precio[i]);
            printf("Ingrese el nuevo stock del producto: ");
            scanf("%d", &stock[i]);
            check = 1;
            printf("\nProducto modificado exitosamente.\n");

            rewind(archivo);
            for (int j = 0; j < producto; j++) {
                fprintf(archivo, "%d %s %.2f %d\n", ID[j], nombre[j], precio[j], stock[j]);
            }

            break;
        }
    }

    if (!check) {
        printf("\nEl ID ingresado no corresponde a ningun producto.\n");
    }
}

void eliminarProducto(FILE *archivo, int ID[], char nombre[][MAX_LENGTH], float precio[], int stock[], int *producto) {
    int eliminar, check = 0;
    printf("\nIngrese el ID del producto que desea eliminar: ");
    scanf("%d", &eliminar);

    for (int i = 0; i < *producto; i++) {
        if (eliminar == ID[i]) {
            for (int j = i; j < *producto - 1; j++) {
                ID[j] = ID[j+1];
                strcpy(nombre[j], nombre[j+1]);
                precio[j] = precio[j+1];
                stock[j] = stock[j+1];
            }
            (*producto)--;
            check = 1;
            printf("\nProducto eliminado exitosamente.\n");

            rewind(archivo);
            for (int j = 0; j < *producto; j++) {
                fprintf(archivo, "%d %s %.2f %d\n", ID[j], nombre[j], precio[j], stock[j]);
            }


            break;
        }
    }

    if (!check) {
        printf("\nEl ID ingresado no corresponde a ningun producto.\n");
    }
}