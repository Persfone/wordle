#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <assert.h>

#define MAX_INTENTOS 6
#define LARGO_PALABRA 5
#define RESET_COLOR "\e[m"
#define WHITE "\x1B[47m"
#define GREEN "\x1B[42m"
#define YELLOW "\x1B[43m"

#ifdef _WIN32_
    #define limpiar "cls"
#else // Linux o MacOS
    #define limpiar "clear"
#endif

typedef struct intento {
    char palabra[LARGO_PALABRA+1];
    char letras_acertadas[LARGO_PALABRA+1];
} intento;

// Declaración de las funciones
void tablero(int Nintentos, intento intento_actual[]);
int verificar(char palabra_secreta[], intento* intento_actual);