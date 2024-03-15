//
// Creado por David el 26/02/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>


int ejecutar(char *args[], char *redir);

void trim(char *s);

int main(int argc, char *argv[]) {
    FILE *fich;
    char *linea, *comandos, *token, *redir; //*prog;
    char **args;
    char error_message[30] = "An error has occurred\n";
    int bandera = 1, itArgumentos, contComandos = 0; // j = 0;
    size_t tam = 255;
    //int fOut;
    pid_t pid;


    linea = malloc(255 * sizeof(char));
    comandos = malloc(255 * sizeof(char *)); // Espacio 16 comandos, 255 por cada uno. DE SOBRA :)
    token = malloc(64 * sizeof(char));
    args = malloc(8 * 128 * sizeof(char));

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
            //printf("\033[1m\033[38;2;255;87;51mUVash> \033[0m"); 
            printf("UVash> "); // Para pasar los tests
            getline(&linea, &tam, stdin);
            linea[strlen(linea) - 1] = '\0';

            contComandos = 0;
            while ((comandos = strsep(&linea, "&")) != NULL) { //Separador de __COMANDOS__

                token = strsep(&comandos, ">");
                redir = strsep(&comandos, ">");

                itArgumentos = 0; // Iterador de argumentos
                while ((args[itArgumentos] = strsep(&token, " ")) != NULL) { //Separador de __ARGUMENTOS__
                    trim(args[itArgumentos]);
                    if (strcmp(args[itArgumentos], "") == 0) {
                        args[itArgumentos] = NULL;
                    } else {
                        itArgumentos++; // Avanza porfa
                    }
                }
                //printf("Se ejecutará con: %s y %s en la salida %s\n", args[0], args[1], redir);

                if (strcmp("exit", args[0]) == 0) { // ------------EXIT??😎
                    printf("Acaba el programa %d\n", getpid());
                    exit(0);
                } else if (strcmp("cd", args[0]) == 0) { // ------------CD??😎
//                    nArgs = 0;
//                    while (args[argc] != NULL) trim(args[argc++]);
                    if (args[1] == NULL || args[2] != NULL) { // argc será al menos 1 siempre (== 0)
                        fprintf(stderr, "An error has occurredARGUSDE CE,DE\n");
                    } else if (chdir(args[1]) == -1) fprintf(stderr, "An error has occurred, En cd\n"); // Hacer cd
                } else {
                    if (getpid() != 0) { // SOY PADRE🧐
                        pid = fork(); // PE I DE
                        printf("Soy %d y padre\n", pid);
                        contComandos++;
                    }

                    if (pid == 0) {
                        bandera = ejecutar(args, redir);
                    }
                }


                // TODO cerrar el fichero fout
                // Ejecutar con args y redireccionar al segundo token, (si no hay, pasar por stdout)
            }

            if (pid != 0)
                for (int j = 0; j < contComandos; ++j) { // ESPERAR COMANDOS PARALELOS 😗
                    printf("A MIMIR:%d_%d_\n", j, pid);

                    wait(NULL);
                }
            //printf("__%d__", bandera);
        }
    } else {
        fprintf(stderr, "%s", error_message);
    }


    free(linea);
    free(comandos);
    free(token);
    free(args);

    return 0;
}

int ejecutar(char *args[], char *redir) {
    int fOut;

    // ------------NORMAL??😎
    if (redir != NULL) { // REDIRECCION 🤑
        trim(redir);

        if ((fOut = open(redir, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) {
            fprintf(stderr, "An error has occurredABRIR\n");
        }

        // Para la redirección de los programas
        dup2(fOut, 1);
        dup2(fOut, 2);
    }

    if (execvp(args[0], args) == -1) { // Ejecución argumento normal
        fprintf(stderr, "An error has occurredEJEC\n");
    }


    return 0; // Si hay errores NO se continua :)
}


void trim(char *cad) {
    while (cad[0] == ' ' || cad[0] == '\t')
        for (int j = 0; j < strlen(cad); j++)
            cad[j] = cad[j + 1];
    while (cad[strlen(cad) - 1] == ' ' || cad[strlen(cad) - 1] == '\t')
        cad[strlen(cad) - 1] = '\0';
}
