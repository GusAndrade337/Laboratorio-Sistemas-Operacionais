#include <stdio.h>
#include <stdlib.h>

int main () {
   char ch;
   char nome_arquivo[50];
   FILE *entrada;
   scanf ("%s", nome_arquivo);
   entrada = fopen (nome_arquivo, "r");
   if (entrada == NULL) {
      printf ("\nArquivo nao encontrado");
      return -1;
   }
    while (!feof(entrada)) {
        ch = fgetc(entrada);
        printf("%c", ch);
    }
    fclose(entrada);
    return 0;
}
