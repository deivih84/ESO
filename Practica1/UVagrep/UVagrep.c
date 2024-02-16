#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
        FILE *fichero;
        int i = 2;
        char *linea = NULL;
	size_t bytes = 0;


	if (argc == 1) {
		printf("UVagrep: searchterm [file ...]\n"); 
		exit(1);
	} else if (argc == 2) { // Entrada estandar   
                while (getline(&linea, &bytes, stdin) != -1) {
                        if (strstr(linea, argv[1]) != NULL) {
        	                printf("%s", linea);
			}
                }
		return 0;
        } else { // Entrada por fichero
                i = 2;

                while (i < argc) {
                        if ((fichero = fopen(argv[i], "r")) == NULL) {
                                printf("UVagrep: cannot open file\n");
                                exit(1);
                        }

                        while ((getline(&linea, &bytes, fichero)) != -1) {
                                if (strstr(linea, argv[1]) != NULL) {
                                        printf("%s", linea);
                                }
                        }
                        i++;
                        fclose(fichero);
                }
		return 0;
        }
	free(linea);
}
