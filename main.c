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