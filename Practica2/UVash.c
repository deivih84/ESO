//
// Creado por David el 26/02/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void toLowerCase(char *str);

int main(int argc, char *argv[]) {
    	FILE *fichero;
    	char *linea;
	char error_message[30] = "An error has occurred\n";
	int bandera = 1;
    	size_t tam = 255;	
	

	if (argc == 1) { // Modo interactivo (Lectura por teclado)
        	while (bandera) {
            		printf("UVash> ");
            		getline(&linea, &tam, stdin);
			printf("Ejecutaría _%s_", linea);

			bandera = (strcmp("exit", linea) != 0);
        	}
	} else if (argc == 2) { // Modo batch (lectura desde fichero)
		if ((fichero = fopen(argv[1], "r")) == NULL) {
			printf("UVash: no puedo abrir fichero\n");
			exit(1);
		}
        	while((getline(&linea, &tam, fichero)) != -1) {
            	//TODO leer todo el fichero en busca de comandos

        	}
   	} else {
		fprintf(stderr, "%s", error_message);
	}
    return 0;
}


void toLowerCase(char *str) {
    while (*str) {
        *str = tolower(*str);
        str++;
    }
}
