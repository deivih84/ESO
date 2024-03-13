//
// Creado por David el 26/02/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>
#include <fcntl.h>


int ejecutar(char *args[], char *redir);
void trim (char *s);

int main(int argc, char *argv[]) {
    FILE *fich;
    char *linea, *comando, *token, *redir; //*prog;
    char *pDel = "&", *sDel = ">", *tDel = " ";
    char **args;
    char error_message[30] = "An error has occurred\n";
    int bandera = 1, i, cont = 0; // j = 0;
    size_t tam = 255;
    //int fOut;
    //pid_t pid;


    linea = malloc(255 * sizeof(char));
    comando = malloc(256 * sizeof(char)); // Espacio 16 comandos, 256 por cada uno. DE SOBRA :)
    token = malloc(64 * sizeof(char));
    args = malloc(8 * 16 * sizeof(char));

    if (argc == 2) { // Modo batch (lectura desde fichero)
        if ((fich = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "%s", error_message);
            exit(1);
        }
        while ((getline(&linea, &tam, fich)) != -1) {
            //TODO leer todo el fichero en busca de comandos
        }
    } else if (argc == 1) {
        while (bandera) {
            printf("UVash> ");
            getline(&linea, &tam, stdin);
            linea[strlen(linea) - 1] = '\0';

            while ((comando = strsep(&linea, pDel)) != NULL) { //Separador "&"
                // Separador ">"
                token = strsep(&comando, sDel);
                redir = strsep(&comando, sDel);

//                            printf("Se redirige por la salida normal\n");

                i = 0;
                while ((args[i] = strsep(&token, tDel)) != NULL) { //Separador " "
                    if (strcmp(args[i], "") == 0) {
                        args[i] = NULL;
                    } else {
                        i++;
                    }
                }
		//printf("Se ejecutará con: %s y %s en la salida %s\n", args[0], args[1], redir);

                bandera = ejecutar(args, redir);

                // TODO cerrar el fichero fout
                // Ejecutar con args y redireccionar al segundo token, (si no hay, pasar por stdout)
            }

            for (int j = 0; j < cont; ++j) {
                wait(NULL);
            }
            //printf("__%d__", bandera);
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

int ejecutar(char *args[], char *redir) {
    int fOut;
    FILE *fich;

    int argc = 0;
    while (args[argc] != NULL) argc++;


    if (strcmp("exit", args[0]) == 0) { // ------------exit??
//        printf("Se ejecutará con: %s y %s en la salida %s\n", args[0], args[1], redir);

        exit(0);
    } else { // cd y normal
        int pid = fork(); // PE I DE

        if (pid == 0) { // Código de proceso hijo
            if (strcmp("cd", args[0]) == 0) { // -----------CD??
                if (argc == 0 || argc > 1) {
			fprintf(stderr, "An error has occurred\n");
                }
            } else { // ------------NORMAL??
                if (redir != NULL) { // REDIRECCION
			//while (redir[0] == ' ') {
                        //	for (int j = 0; j < strlen(redir); j++)
                        //    		redir[j] = redir[j + 1];
			//}
			//while (redir[strlen(redir) - 1] == ' ')
			//	redir [strlen(redir) - 1] = '\0';
			trim(redir);


                    	if ((fich = fopen(redir, "w")) == NULL) {
                        	fprintf(stderr, "An error has occurred\n");
                    	}

                    	// Para la redirección de los programas
                    	fOut = fileno(fich);
			dup2(fOut, 1);
                    	dup2(fOut, 2);
                }
            }

            execvp(args[0], args);
            fprintf(stderr, "An error has occurred\n");
        } else {
            wait(NULL);
        }
        return 1; // Si hay errores se continua :)
    }
}
void trim (char *cad){
        while (cad[0] == ' ' || cad[0] == '\t') 
        	for (int j = 0; j < strlen(cad); j++)
                	cad[j] = cad[j + 1];
        while (cad[strlen(cad) - 1] == ' '  || cad[strlen(cad) - 1] == '\t')  
        	cad[strlen(cad) - 1] = '\0';
}
