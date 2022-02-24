#include <stdio.h>
#include <stdlib.h>

int main () {
    char ch;
    char nome_arquivo_entrada[50];
    char nome_arquivo_saida[50];
    FILE *entrada;
    FILE *saida;
    FILE *validaCopia;
    scanf ("%s", nome_arquivo_entrada);
    entrada = fopen (nome_arquivo_entrada, "r");
    scanf ("%s", nome_arquivo_saida);
    saida = fopen (nome_arquivo_saida,"w");
    if (entrada == NULL) {
        printf ("\nArquivo não encontrado");
        return -1;
    }
    while (!feof(entrada)) {
        ch = fgetc(entrada);
        printf("%c", ch);
        fprintf(saida,"%c",ch);
   }
    validaCopia = fopen (nome_arquivo_saida, "r");
    if (saida == NULL) {
        printf ("\nErro ao criar o arquivo de cópia");
        return -1;
   }
    fclose(entrada);
    fclose(saida);
    return 0;
}
