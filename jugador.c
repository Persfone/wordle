#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define WORD_LENGTH 5

// Estructura para almacenar cada palabra con su prioridad
typedef struct Word {
    char palabra[WORD_LENGTH + 1];
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

// Insertar palabra en el árbol binario de acuerdo a su prioridad
Nodo* insertar_palabra(Nodo *raiz, Word palabra) {
    if (raiz == NULL) {
        return crear_nodo(palabra);
    }

    if (palabra.prioridad > raiz->palabra.prioridad) {
        raiz->izquierda = insertar_palabra(raiz->izquierda, palabra);
    } else {
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
    char linea[8];

    while (fgets(linea, sizeof(linea), archivo)) {
        count++;
    }

    fclose(archivo);
    return count;
}

// Cargar palabras desde el archivo
void cargar_palabras(const char *filename, Word *palabras) {
    FILE *archivo = fopen(filename, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    char linea[8];
    int count = 0;
    //sigue hasta que fgets retorne NULL
    while (fgets(linea, sizeof(linea), archivo)) {
        // guarda la palabra en token
        char *token = strtok(linea, ",");
        //copia la palabra en la estructura palabras
        strcpy(palabras[count].palabra, token);
        //hace lo mismo pero con la prioridad, sigue en la misma linea
        token = strtok(NULL, ",");
        //lo copia en parte de prioridad de palabras 
        palabras[count].prioridad = atoi(token);
        count++;
    }

    fclose(archivo);
}


int cumple_condiciones(const char *palabra, const char *letras_verdes, const char *letras_naranjas) {
    // Verificar las letras verdes en las posiciones correctas
    for (int i = 0; i < WORD_LENGTH; i++) {
        // Si la letra verde no está en la posición correcta, la palabra no cumple
        if (letras_verdes[i] != '\0') {
            return 0;
        }
    }

    // Verificar las letras naranjas (deben estar presentes pero no en la posición incorrecta)
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (letras_naranjas[i] != '\0') {
            // Usamos strchr para buscar la letra naranja en la palabra
            char *posicion_letra = strchr(palabra, letras_naranjas[i]);

            // Si la letra no está presente en la palabra o está en la misma posición que en la cadena de letras naranjas, la palabra no cumple
            if (posicion_letra == NULL) {
                return 0;
            }
        }
    }

    return 1;
}


// Función para solicitar letras verdes y naranjas al usuario
void ingresar_letras(char *letras_verdes, char *letras_naranjas) {
    //esta parte estaria conectada con el jugable que es el que le pasa las letras verdes y narajas/amarillas
    printf("Ingrese las letras verdes (posicion correcta) con '_' para posiciones vacias (ej: a___e):\n");
    scanf("%5s", letras_verdes);

    printf("Ingrese las letras naranjas (presentes en posicion incorrecta) con '_' para posiciones vacias (ej: __p__):\n");
    scanf("%5s", letras_naranjas);
}

// Filtrar palabras y construir el árbol
Nodo* filtrar_palabras(Nodo *arbol, Word *palabras, int num_palabras, const char *letras_verdes, const char *letras_naranjas) {
    for (int i = 0; i < num_palabras; i++) {
        if (cumple_condiciones(palabras[i].palabra, letras_verdes, letras_naranjas)) {
            printf("Palabra que cumple condiciones: %s\n", palabras[i].palabra);
            arbol = insertar_palabra(arbol, palabras[i]);
        }
    }
    return arbol;
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

    // Definir arreglos para letras verdes y naranjas
    char letras_verdes[WORD_LENGTH + 1];
    char letras_naranjas[WORD_LENGTH + 1];

    // Solicitar al usuario las letras verdes y naranjas
    ingresar_letras(letras_verdes, letras_naranjas);

    Nodo *arbol = NULL;
    arbol = filtrar_palabras(arbol, palabras, num_palabras, letras_verdes, letras_naranjas);
    // Filtrar las palabras y construir el árbol de prioridad
    for (int i = 0; i < num_palabras; i++) {
        if (cumple_condiciones(palabras[i].palabra, letras_verdes, letras_naranjas)) {
            arbol = insertar_palabra(arbol, palabras[i]);
        }
    }

    // Imprimir la palabra de la raíz del árbol
    if (arbol != NULL) {
        //esta parte estaria conectada con el jugable tambien, tipo de aca sale la nueva palabra para otro intento
        printf("La palabra en la raiz del arbol es: %s\n", arbol->palabra.palabra);
    } else {
        printf("No hay palabras que cumplan las condiciones.\n");
    }

    // Liberar memoria dinámica
    free(palabras);

    return 0;
}
