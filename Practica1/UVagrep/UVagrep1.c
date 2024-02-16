#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
	  // Validar argumentos
	  //   if (argc != 3) {
	  //       fprintf(stderr, "Uso: %s <patron> <archivo>\n", argv[0]);
	  //           return EXIT_FAILURE;
	  //             }
	  //
	  //               // Abrir archivo
	  //                 FILE *archivo = fopen(argv[2], "r");
	  //                   if (archivo == NULL) {
	  //                       fprintf(stderr, "Error al abrir el archivo '%s'\n", argv[2]);
	  //                           return EXIT_FAILURE;
	  //                             }
	  //
	  //                               // Variables
	  //                                 char *linea = NULL;
	  //                                   size_t longitud = 0;
	  //                                     ssize_t leido;
	  //
	  //                                       // Leer líneas del archivo
	  //                                         while ((leido = getline(&linea, &longitud, archivo)) != -1) {
	  //                                             // Buscar patrón en la línea
	  //                                                 if (strstr(linea, argv[1]) != NULL) {
	  //                                                       // Imprimir la línea
	  //                                                             printf("%s", linea);
	  //                                                                 }
	  //                                                                   }
	  //
	  //                                                                     // Liberar memoria
	  //                                                                       free(linea);
	  //
	  //                                                                         // Cerrar archivo
	  //                                                                           fclose(archivo);
	  //
	  //                                                                             return EXIT_SUCCESS;
	  //                        }
	  //
