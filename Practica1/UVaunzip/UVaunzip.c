#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fichero;
	int i = 1, cont = 1, num;
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

		while(fread(&num, sizeof(int), 1, fichero) == 1 && fread(&c, sizeof(char), 1, fichero) == 1) { 
			for (;num > 0; num--)
				printf("%c",c);
		}
		fclose(fichero);
	}
	fwrite(&cont, sizeof(int), 1, stdout);
	printf("%c", preC);

	return 0;
}
