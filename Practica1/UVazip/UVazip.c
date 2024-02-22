#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fichero;
	int i = 1, cont = 0;
	char c;
	char preC = '7';

    if (argc == 1) {
        printf("UVazip: file1 [file2 ...]");
        exit(1);
    }
	while (i < argc) {
		if ((fichero = fopen(argv[i], "r")) == NULL) {
			printf("UVazip: no puedo abrir fichero\n");
			exit(1);
		}
		i++;

		do {
			c = fgetc(fichero);
			if (preC != '7' && c != preC && c != EOF) {
		                fwrite(&cont, sizeof(int), 1, stdout);
				printf("%c", preC);
				cont = 1;
			} else if (preC == c) {
				cont++;
			}
			preC = c;
		} while (c != EOF);
		fclose(fichero);
	}
	return 0;
}
