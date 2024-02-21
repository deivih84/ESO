#include <stdio.h>
#include <stdlib.h>

//char *imprimirBinario(int numero) {
//    char cad[255];
//    for (int i = sizeof(int) * 8 - 1; i >= 0; i--) {
//        int bit = (numero >> i) & 1;
//        sprintf(cad, "%d", bit);
//    }
//    return cad;
//}

int main(int argc, char *argv[]) {
	FILE *fichero;
	int i = 1, cont = 0;
	char c;
	char preC = '7';
//    char datos[255];

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
			if (preC != '7' && c != preC) {
//                itoa(cont, datos,2);
                fwrite(&cont, sizeof(int), 1, stdout);
//                imprimirBinario(cont);
				printf("%c", preC);
				cont = 1;
			} else {
				cont++;
			}
			preC = c;
		} while (c != EOF);
		fclose(fichero);
	}
	return 0;
}
