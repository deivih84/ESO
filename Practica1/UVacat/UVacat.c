#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	FILE *fichero;
	int i = 1;
	char linea[255];

	while (i < argc) {
		if ((fichero = fopen(argv[i], "r")) == NULL) {
			printf("UVacat: no puedo abrir fichero\n");
			exit(1);
		}
		i++;
		while ((fgets(linea, 255, fichero)) != NULL) {
			printf("%s", linea);
		}
		fclose(fichero);
	}
	return 0;
}

