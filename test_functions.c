#include <stdio.h>
#include <string.h>

void comprime_texto(char *texto) {
    int i, j;
    int longitud = strlen(texto);

    for (i = 0, j = 0; i < longitud; i++) {
        if (texto[i] != '\n') {
            texto[j] = texto[i];
            j++;
        }
    }
    texto[j] = '\0';
}

int main() {
    char texto[] = "Este es\nun ejemplo\nde texto con\nsaltos de\nlinea.";
    printf("Texto original:\n%s\n", texto);

    comprime_texto(texto);
    printf("Texto comprimido:\n%s\n", texto);

    return 0;
}
