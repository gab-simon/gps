#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
  DIR *dp;
  struct dirent *dirp;

  const char *extension = "/";
  char *namepath;

  scanf("%c",namepath);

  char *name_with_extension;
  name_with_extension = malloc(strlen(namepath));
  strcpy(name_with_extension, namepath);
  strcat(name_with_extension, extension);             /* add the extension */

  dp = opendir(name_with_extension);

  while ((dirp = readdir(dp)) != NULL)
    printf("%s\n", dirp->d_name);

  closedir(dp);
  free(name_with_extension);
  exit(EXIT_SUCCESS);
}