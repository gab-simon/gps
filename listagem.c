#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

int main(void)
{
  DIR *dirstream;
  struct dirent *direntry;

  // abre um diretório
  dirstream = opendir("./logs");
  if (!dirstream)
  {
    perror("Couldn't open the directory");
    exit(1);
  }

  int a = 0;
  // varre as entradas do diretório aberto
  for (;;)
  {
    // pega a próxima entrada
    direntry = readdir(dirstream);

    // se for nula, encerra a varredura
    if (!direntry)
      break;

    // mostra conteúdo da entrada
    printf("%s\t", direntry->d_name);
    switch (direntry->d_type)
    {
    case DT_REG:
      printf(" (arquivo)\n");
      break;
    default:
      printf(" (outros)\n");
    }
  }

  // fecha o diretório
  closedir(dirstream);

  exit(0);
}