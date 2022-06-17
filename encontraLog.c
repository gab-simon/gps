#include <stdio.h>
#include <stdlib.h>

#define LINESIZE 1024

int main()
{
  FILE *arq;
  int i;
  char line[LINESIZE + 1];
  // abre o arquivo em escrita
  arq = fopen("4252839552.log", "r");
  if (!arq)
  {
    perror("Erro ao abrir/criar arquivo");
    exit(1);
  }

  // escreve os caracteres ascii
  // TODO: strtok
  i = 1;
  fgets(line, LINESIZE, arq); // tenta ler uma linha
  while (!feof(arq))          // testa depois de tentar ler!
  {
    printf("%d: %s", i, line);
    fgets(line, LINESIZE, arq); // tenta ler a próxima linha
    i++;
  }

  // fecha o arquivo
  fclose(arq);
}