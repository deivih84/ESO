#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fichero;
	int i = 1, cont = 1;
	char c, preC = '_';

    if (argc == 1) {
        printf("UVazip: file1 [file2 ...]\n");
        exit(1);
    }
	while (i < argc) {
		if ((fichero = fopen(argv[i], "r")) == NULL) {
			printf("UVazip: no puedo abrir fichero\n");
			exit(1);
		}
		i++;
		if (preC == '_') {
			preC = fgetc(fichero);
		}
		while ((c = fgetc(fichero)) != EOF) {	
			if (c != preC) {
		                fwrite(&cont, sizeof(int), 1, stdout);
				printf("%c", preC);
				cont = 1;
			} else if (preC == c) {
				cont++;
			}
            preC = c;
		}
		fclose(fichero);
	}
    fwrite(&cont, sizeof(int), 1, stdout);
    printf("%c", preC);

	return 0;
}
