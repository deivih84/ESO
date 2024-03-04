//
// Creado por David el 26/02/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>


int main(int argc, char *argv[]) {
    	FILE *fichero;
    	char *linea, *comando, *token, *redir, *prog;
    	char *pDel = "&", *sDel = ">", *tDel = " ";
	char **args;
	char error_message[30] = "An error has occurred\n";
	int bandera = 1, i;
    	size_t tam = 255;	
	


		linea = malloc(255*sizeof(char));
		comando = malloc(128*sizeof(char));
		token = malloc(64*sizeof(char));
		args = malloc(8*16*sizeof(char));
		
	if (argc == 1) { // Modo interactivo (Lectura por teclado)
        	while (bandera) {
            	printf("UVash> ");
            	getline(&linea, &tam, stdin);
				linea[strlen(linea)-1] = '\0';
				
				if(strcmp("exit", linea) == 0){
					break;
				} // Detectar el exit
				
					
				while((comando = strsep(&linea, pDel)) != NULL) { //Separador "&"
					//printf("com:%s\n", comando);
					
					// Separador ">"
					token = strsep(&comando, sDel);
					
					if((redir = strsep(&comando, sDel)) != NULL){
						printf("Se redirige a:%s\n", redir);
					} else {
						redir = "stdout";
						printf("Se redirige a stdout\n");
					}
					//printf("tok:%s\n", token);
					//TODO Utilizar el token principal para los argumentos y el secundario para la redirección.
										
					i = 0;
					prog = strsep(&token, tDel);
					while((args[i] = strsep(&token, tDel)) != NULL) { //Separador " "
					
						printf("arg:%s\n", args[i]);	
					}
					printf("Se ejecutará con: %s y args en la salida %s\n", prog, redir);
					if (execvp(prog, args) == ) {
						fprintf(stderr, "%s", error_message);
					}
				}
				// Ejecutar con args y redireccionar al segundo token, (si no hay, pasar por stdout)
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
	free(comando);
	free(token);
	free(args);
	
	
    return 0;
}

