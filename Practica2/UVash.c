//
// Creado por David el 26/02/2024.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>


int ejecutar(char *args[], char *redir);
void trim(char *cad);
void *xmalloc(unsigned short size);
void error(void);


int main(int argc, char *argv[]) {
    FILE *fich;
    char *linea, *comandos, *token, *redir, **args;
    int bandera = 1, itArgumentos, contComandos, batch, prim = 1;
    size_t cant = 255; // Cantidad de bytes que va a leer el getline y se va a guardar en linea
    pid_t pid;

    linea = xmalloc(255 * sizeof(char)); // Reserva de la cantidad justa de memoria :)
    comandos = xmalloc(255 * sizeof(char)); // Espacio 16 comandos, 255 por cada uno. DE SOBRA :)
    token = xmalloc(64 * sizeof(char));
    args = xmalloc(8 * 128 * sizeof(char));

    if (argc == 2) { //                                                     ---MODO BATCH---
        if ((fich = fopen(argv[1], "r")) == NULL) {
            error();
            exit(1);
        }
        batch = 1;
    } else if (argc == 1) { //                                            ---MODO INTERACTIVO---
        fich = stdin;
        batch = 0;
    } else { // ERROR CATASTRÓFICO
        error();
        exit(-1);
    }

    while (bandera) {
        if (!batch) printf("\033[1m\033[38;2;255;87;51mUVash> \033[0m");
        if (getline(&linea, &cant, fich) == -1) {
            if (prim) exit(1);
            exit(0);
        }
        prim = 0;
        trim(linea);
        if (linea[0] == '&' || linea[0] == '>') error();
        else {
            linea[strlen(linea) - 1] = '\0';

            contComandos = 0;
            comsWhile:
            while ((comandos = strsep(&linea, "&")) != NULL) { //Separador de __COMANDOS__

                token = strsep(&comandos, ">");

                trim(comandos);
                if (comandos != NULL) {
                    for (int i = 0; i < strlen(comandos); ++i)
                        if (comandos[i] == ' ' || comandos[i] == '>') {
                            error();
                            goto comsWhile;
                        }
                }
                redir = strsep(&comandos, ">");
                trim(redir);

                if (redir != NULL && strcmp(redir, "") == 0) {
                    error();
                    goto comsWhile;
                }

                itArgumentos = 0;
                while ((args[itArgumentos] = strsep(&token, " ")) != NULL) { //Separador de ----ARGUMENTOS----
                    trim(args[itArgumentos]);
                    if (strcmp(args[itArgumentos], "") == 0) args[itArgumentos] = NULL;
                    else itArgumentos++; // Avanza porfa
                }

                if (args[0] != NULL) {
                    if (strcmp("exit", args[0]) == 0) { //                                              ----------EXIT??
                        if (args[1] != NULL) error();
                        else exit(0);
                    } else if (strcmp("cd", args[0]) == 0) { //                                         ------------CD??
                        if (args[1] == NULL || args[2] != NULL) { // argc será al menos 1 siempre
                            error();
                        } else if (chdir(args[1]) == -1) error(); // Cabiar de directorio
                    } else { //                                                                         --------NORMAL??
                        if (getpid() != 0) { // SOY PADRE🧐
                            pid = fork(); // PE I DE
                            contComandos++;
                        }

                        if (pid == 0) bandera = ejecutar(args, redir);
                    }
                }
            }
            // ESPERAR A TODOS LOS FORKS
            if (pid != 0) for (int j = 0; j < contComandos; ++j) wait(NULL);
        }
    }

    if (argc == 2) fclose(fich);
    free(linea);
    free(comandos);
    free(token);
    free(args);

    return 0;
}

int ejecutar(char *args[], char *redir) {
    int fOut;

    if (redir != NULL) { //                                                        ----REDIRECCIÓN----
        if ((fOut = open(redir, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1) error();

        // Para la redirección de los programas
        dup2(fOut, 1);
        dup2(fOut, 2);
    }

    if (execvp(args[0], args) == -1) error(); // Ejecución argumento normal

    if (redir != NULL) close(fOut); // Cerrar si se va a redirigir :) Cerrar es sano
    return 0; // NO se continua :)
}

void trim(char *cad) { // Función para quitar los espacios molestos de una string
    if (cad != NULL) {
        while (cad[0] == ' ' || cad[0] == '\t')
            for (int j = 0; j < strlen(cad); j++)
                cad[j] = cad[j + 1];
        while (cad[strlen(cad) - 1] == ' ' || cad[strlen(cad) - 1] == '\t')
            cad[strlen(cad) - 1] = '\0';
    }
}

void *xmalloc(unsigned short size) {
    void *tmp;
    if ((tmp = malloc(size)) == NULL){
        fprintf(stderr, "ERROR CATASTRÓFICO: No hay memoria!!\n");
        fflush(stderr);
        exit(2);
    }
return tmp;
}

void error(void) {
     fprintf(stderr, "An error has occurred\n");
}
