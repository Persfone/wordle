#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_LENGTH 5

// Estructura para almacenar cada palabra con su prioridad
typedef struct Word {
    char palabra[WORD_LENGTH + 1]; // +1 para el terminador nulo '\0'
    int prioridad;
} Word;

// Nodo del árbol binario de prioridad
typedef struct Nodo {
    Word palabra;
    struct Nodo *izquierda;
    struct Nodo *derecha;
} Nodo;

// Función para crear un nuevo nodo
Nodo* crear_nodo(Word palabra) {
    Nodo* nuevo_nodo = (Nodo*) malloc(sizeof(Nodo));
    nuevo_nodo->palabra = palabra;
    nuevo_nodo->izquierda = NULL;
    nuevo_nodo->derecha = NULL;
    return nuevo_nodo;
}

// Función para insertar una palabra en el árbol según su prioridad
Nodo* insertar_palabra(Nodo *raiz, Word palabra) {
    if (raiz == NULL) {
        return crear_nodo(palabra);
    }

    // Insertar en el subárbol izquierdo si la prioridad es mayor
    if (palabra.prioridad > raiz->palabra.prioridad) {
        raiz->izquierda = insertar_palabra(raiz->izquierda, palabra);
    }
    // Insertar en el subárbol derecho si la prioridad es menor o igual
    else {
        raiz->derecha = insertar_palabra(raiz->derecha, palabra);
    }

    return raiz;
}

// Contar las palabras en el archivo
int contar_palabras(const char *filename) {
    FILE *archivo = fopen(filename, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    int count = 0;
    char linea[8]; // Suponiendo que una línea no supera 20 caracteres

    // Leer el archivo línea por línea
    while (fgets(linea, sizeof(linea), archivo)) {
        count++; // Contar cada línea
    }

    fclose(archivo);
    return count;
}

// Función para cargar las palabras desde un archivo y almacenarlas en un arreglo de palabras
void cargar_palabras(const char *filename, Word *palabras) {
    FILE *archivo = fopen(filename, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    char linea[20]; // Buffer para cada línea
    int count = 0;

    // Leer línea por línea
    while (fgets(linea, sizeof(linea), archivo)) {
        // Dividir la línea en palabra y prioridad
        char *token = strtok(linea, ",");
        strcpy(palabras[count].palabra, token);
        
        token = strtok(NULL, ",");
        palabras[count].prioridad = atoi(token);

        count++;
    }

    fclose(archivo);
}

// Función para recorrer el árbol e imprimirlo en orden
void recorrer_arbol(Nodo *raiz) {
    if (raiz != NULL) {
        recorrer_arbol(raiz->izquierda); // Recorrer subárbol izquierdo
        printf("Palabra: %s, Prioridad: %d\n", raiz->palabra.palabra, raiz->palabra.prioridad);
        recorrer_arbol(raiz->derecha); // Recorrer subárbol derecho
    }
}

// Función principal
int main() {
    // Contar el número de palabras en el archivo
    int num_palabras = contar_palabras("palabras.txt");

    // Asignar memoria dinámica para almacenar las palabras
    Word *palabras = (Word *) malloc(num_palabras * sizeof(Word));

    if (palabras == NULL) {
        printf("Error al asignar memoria.\n");
        exit(1);
    }

    // Cargar palabras y prioridades desde archivo
    cargar_palabras("palabras.txt", palabras);

    Nodo *arbol = NULL;

    // Insertar todas las palabras en el árbol
    for (int i = 0; i < num_palabras; i++) {
        arbol = insertar_palabra(arbol, palabras[i]);
    }

    // Recorrer e imprimir el árbol en orden
    printf("Palabras en el árbol ordenadas por prioridad:\n");
    recorrer_arbol(arbol);

    // Liberar memoria dinámica
    free(palabras);

    return 0;
}
