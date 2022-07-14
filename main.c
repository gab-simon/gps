#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

#include "libbike.h"

int main(int argc, char *argv[])
{
  DIR *dp;
  struct dirent *dirp;
  char *namepath;
  int op;

  if (strcmp(argv[1], "-d") == 0)
  {
    namepath = argv[2];
  }

  dp = opendir(namepath);
  printf("1. Mostra todas as bicicletas encontradas.\n");
  printf("2. Informe uma bicicleta.\n");
  printf("3. Lista todas atividades agrupadas por bicicleta e ordenadas pela data.\n");
  printf("4. Lista todas atividades agrupadas por bicicleta e ordenadas pela distância.\n");
  printf("5. Lista todas atividades ordenadas pela subida acumulada.\n");
  printf("6. Histograma.\n");
  printf("Sair");
  scanf("%i", &op);

  while ((dirp = readdir(dp)) != NULL)
  {
    if (op == 1)
    {
      printf("%s\n", dirp->d_name);
      open_log(namepath, dirp->d_name);
    }
  }

  closedir(dp);

  free(namepath);
  exit(EXIT_SUCCESS);
}