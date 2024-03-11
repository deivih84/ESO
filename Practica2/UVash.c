//
// Creado por David el 26/02/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


int main(int argc, char *argv[]) {
    FILE *fich;
    char *linea, *comando, *token, *redir; //*prog;
    char *pDel = "&", *sDel = ">", *tDel = " ";
    char **args;
    char error_message[30] = "An error has occurred\n";
    int bandera = 1, i, cont; // j = 0;
    size_t tam = 255;
    int fOut;
    pid_t pid;


    linea = malloc(255 * sizeof(char));
    comando = malloc(256 * sizeof(char)); // Espacio 16 comandos, 256 por cada uno. DE SOBRA :)
    token = malloc(64 * sizeof(char));
    args = malloc(8 * 16 * sizeof(char));

    if (argc == 1) { // Modo interactivo (Lectura por teclado)
        while (bandera) {
            printf("UVash> ");
            getline(&linea, &tam, stdin);
            linea[strlen(linea) - 1] = '\0';

            if (strcmp("exit", linea) == 0) { // exit??🧐
                bandera = 0;
            } else {
                while ((comando = strsep(&linea, pDel)) != NULL) { //Separador "&"
                    pid = fork(); // PE I DE

                    if (pid == 0) { // Código de proceso hijo
                        // Separador ">"
                        token = strsep(&comando, sDel);
                        if ((redir = strsep(&comando, sDel)) != NULL) {
                            if (redir[0] == ' ')
                                for (int i = 0; i < strlen(redir); i++)
                                    redir[i] = redir[i + 1];

                            if ((fich = fopen(redir, "w")) == NULL) {
                                fprintf(stderr, "%s1", error_message);
                            }

                            // Para la redirección de los programas
                            fOut = fileno(fich);
                            dup2(fOut, 1);
                            dup2(fOut, 2);

                        } else {
//                                    redir = "stdout";
//                                    printf("Se redirige por la salida normal\n");
                        }

                        i = 0;
                        while ((args[i] = strsep(&token, tDel)) != NULL) { //Separador " "
                            if (strcmp(args[i], "") == 0) {
                                args[i] = NULL;
                            } else {
//                                        printf("prog:(%s)\n", args[0]);
//                                        printf("arg:(%s)\n", args[i]);
                                i++;
                            }
                        }
//                                printf("Se ejecutará con: %s y %s en la salida %s\n", args[0], args[1], redir);

                        if (execvp(args[0], args) == -1) {
                            fprintf(stderr, "%s2", error_message);
                        }

                        // TODO cerrar el fichero fout
                        // Ejecutar con args y redireccionar al segundo token, (si no hay, pasar por stdout)
                    } else { // Código del proceso Papá
                        cont++;
                    }
                }

                if (pid > 0) {
                    for (int j = 0; j < cont; ++j) {
                        wait(&pid);
                    }
                }

            }
        }
    } else if (argc == 2) { // Modo batch (lectura desde fichero)
        if ((fich = fopen(argv[1], "r")) == NULL) {
            fprintf(stderr, "%s3", error_message);
            exit(1);
        }
        while ((getline(&linea, &tam, fich)) != -1) {
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

