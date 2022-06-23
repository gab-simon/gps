#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1024

int main()
{
  FILE *arq;
  char line[LINESIZE + 1];
  char *separator;
  double valor;
  char *content;
  char *eptr;

  separator = malloc(LINESIZE);
  eptr = malloc(LINESIZE);

  // abre o arquivo
  arq = fopen("4252839552.log", "rw");
  if (!arq)
  {
    perror("Erro ao abrir/criar arquivo");
    exit(1);
  }

  // TODO: strtok
  fgets(line, LINESIZE, arq); // tenta ler uma linha
  while (!feof(arq))          // testa depois de tentar ler!
  {
    separator = strtok(line, ": ");
    printf("%s\n", separator);

    content = strtok(NULL, " ");
    if (strcmp(separator, "altitude") == 0)
    {
      valor = strtod(content, &eptr);
      printf("valor: %f\n", valor);
    }
    // printf("%s \n", separator);

    fgets(line, LINESIZE, arq); // tenta ler a próxima linha
  }

  // fecha o arquivo
  free(separator);
  fclose(arq);
}