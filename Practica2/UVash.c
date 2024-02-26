//
// Created by forex on 26/02/2024.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    FILE *fichero;
    char linea[255];
    size_t sos;

    if (argc == 1) { // Modo interactivo
        while (1) {
            printf("UVash>");
            //TODO modo interactivo

        }
    } else if (argc == 2) { // Modo batch (lectura desde fichero)
        if ((fichero = fopen(argv[1], "r")) != NULL)
        while((getline(&linea, 255, fichero)) != -1) {
            //TODO leer todo el fichero en busca de comandos

        }
    }
    while (1) {


    }
    return 0;
}

