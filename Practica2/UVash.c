//
// Creado por David el 26/02/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


int main(int argc, char *argv[]) {
    	FILE *fichero;
    	char *linea, *args, *token;
    	char *pDel = "&", *sDel = ">";
		char error_message[30] = "An error has occurred\n";
		int bandera = 1;
    	size_t tam = 255;	
	


		linea = malloc(255*sizeof(char));
		token = malloc(64*sizeof(char));
		args = malloc(8*sizeof(char));
		
	if (argc == 1) { // Modo interactivo (Lectura por teclado)
        	while (bandera) {
            		printf("UVash> ");
            		getline(&linea, &tam, stdin);
					linea[strlen(linea)-1] = '\0';
					printf("_%s_\n", linea);
					
					bandera = (strcmp("exit", linea) != 0);
					
					
					while((token = strsep(&linea, pDel)) != NULL) {
							args = strsep(&token, sDel);
							printf("_(token:%s) ", token);
							printf("(args:%s)_ \n", args);
					}

					
        	}
	} else if (argc == 2) { // Modo batch (lectura desde fichero)
			if ((fichero = fopen(argv[1], "r")) == NULL) {
					fprintf(stderr, "%s", error_message);
					exit(1);
			}
        	while((getline(&linea, &tam, fichero)) != -1) {
            	//TODO leer todo el fichero en busca de comandos

        	}
   	} else {
		fprintf(stderr, "%s", error_message);
	}
	
	
	free(linea);
	free(token);
	free(args);
	
	
    return 0;
}

