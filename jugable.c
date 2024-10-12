#include "jugable.h"

int main(int argc, char** argv) {
    
    // Definicion de variables
    char palabra_secreta[LARGO_PALABRA+1]; 
    intento intento_actual[MAX_INTENTOS];

    // Verifica si la palabra secreta es válida
    assert(argc > 1 && strlen(argv[1]) == 5);
    strcpy(palabra_secreta, argv[1]); 

    // Inicialización de los intentos
    for (int i = 0; i < MAX_INTENTOS; i++) {
        strcpy(intento_actual[i].letras_acertadas, "*****");
    }

    // Menú inicial
    printf("\n\n\t\t\t\tWORDLE: EL JUEGO");
    printf("\n\n\t\tAdivina la palabra secreta con 6 intentos.\n");
    sleep(1);
    printf("\n\n\t\t\tPulse ENTER para continuar");
    getchar();

    // Bucle de intentos
    for (int Nintentos = 0; Nintentos < MAX_INTENTOS; Nintentos++) {
        system(limpiar);  // Limpia pantalla
        tablero(Nintentos, intento_actual);  // Muestra tablero
        printf("Intentos restantes: %d\n", MAX_INTENTOS-Nintentos);

        // Pide palabra y verifica que sea válida
        while(strlen(intento_actual[Nintentos].palabra) != 5){
            printf("Ingrese la palabra de 5 letras que desea adivinar: ");
            scanf("%s", intento_actual[Nintentos].palabra);
        }

        // Si adivina la palabra
        if (verificar(palabra_secreta, &intento_actual[Nintentos])) {
            system(limpiar);
            printf("\n\n\t\t\t  ¡HAS GANADO! La palabra secreta era: %s\n\n", palabra_secreta);
            return 0;
        } 
    }

    // Fin del juego si no adivina
    printf("Lo siento, no adivinaste la palabra. La palabra secreta era: %s\n\n", palabra_secreta);
    return 0;
}

// Dibuja el tablero con los intentos hasta el momento
void tablero(int Nintentos, intento intento_actual[]) {
    printf("\n\n\t\t\t   WORDLE: EL JUEGO");
    printf("\n\n\t\t\t╔═══╦═══╦═══╦═══╦═══╗");

    // Imprime cada intento
    for (int j = 0; j < Nintentos; j++) {    
        printf("\n\t\t\t║");
        for(int i = 0; i < LARGO_PALABRA; i++) {
            // Colores: verde si es correcto, amarillo si es letra en lugar incorrecto o blanco si no está en la palabra
            if(isalpha(intento_actual[j].letras_acertadas[i]))
                printf(" %s%c%s ║", GREEN, intento_actual[j].palabra[i], RESET_COLOR);
            else if(intento_actual[j].letras_acertadas[i] == '+')
                printf(" %s%c%s ║", YELLOW, intento_actual[j].palabra[i], RESET_COLOR);
            else
                printf(" %s%c%s ║", WHITE, intento_actual[j].palabra[i], RESET_COLOR);
        }
        printf("\n\t\t\t╠═══╬═══╬═══╬═══╬═══╣");
    }
    printf("\n\t\t\t║   ║   ║   ║   ║   ║");
    printf("\n\t\t\t╚═══╩═══╩═══╩═══╩═══╝\n\n");
}

// Verifica el intento actual comparándolo con la palabra secreta
int verificar(char palabra_secreta[], intento* intento_actual) {
    if (strcmp(intento_actual->palabra, palabra_secreta) == 0) 
        return 1;  // Palabra adivinada correctamente
    else {
        // Compara letras del intento con la palabra secreta
        for (int i = 0; i < LARGO_PALABRA; i++) {
            if (palabra_secreta[i] == intento_actual->palabra[i])
                intento_actual->letras_acertadas[i] = intento_actual->palabra[i];
            else {
                for (int j = 0; j < LARGO_PALABRA; j++) {
                    if (palabra_secreta[i] == intento_actual->palabra[j]){
                        intento_actual->letras_acertadas[j] = '+';
                        j = LARGO_PALABRA;
                    }
                }
            }
        }
        return 0;  // Aún no adivina
    }
}
