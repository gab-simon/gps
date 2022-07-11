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

  if (strcmp(argv[1], "-d") == 0)
  {
    namepath = argv[2];
    // printf(namepath);
  }

  /* verificar se tem /
  //  const char *extension = "/";

  // scanf("%c",namepath);

  // char *name_with_extension;
  // name_with_extension = malloc(strlen(1));
  // strcpy(name_with_extension, namepath);
  // strcat(name_with_extension, extension);*/

  dp = opendir(namepath);

  while ((dirp = readdir(dp)) != NULL)
  {
    // printf("%s\n", dirp->d_name);
    open_log(namepath, dirp->d_name);
  }

  closedir(dp);

  free(namepath);
  exit(EXIT_SUCCESS);
}