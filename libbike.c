#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libbike.h"

#define LINESIZE 1024

int open_log(char *file, char *namepath)
{
    FILE *arq;
    char line[LINESIZE + 1];
    char *separator;
    double valor = 0;
    char *content;
    char *eptr;
    char *name_log;

    /* separadores */
    separator = malloc(LINESIZE);
    name_log = malloc(LINESIZE);
    eptr = malloc(LINESIZE);

    printf(namepath, "\n");
    
    strcat(name_log, file);
    strcat(name_log, "/");
    strcat(name_log, namepath);

    arq = fopen(name_log, "r");

    if (!arq)
    {
        printf(name_log);
        perror("Erro ao abrir/criar arquivo");
        exit(1);
    }

    fgets(line, LINESIZE, arq); /* tenta ler uma linha */
    while (!feof(arq))          /* testa depois de tentar ler! */
    {
        separator = strtok(line, ": ");
        printf("%s\n", separator);

        content = strtok(NULL, " ");
        if (strcmp(separator, "distance") == 0)
        {
            valor += strtod(content, &eptr);
            // printf("valor: %.2f km\n", valor / 1000);
        }
        /* printf("%s \n", separator); */

        fgets(line, LINESIZE, arq); /* tenta ler a próxima linha */
    }

    free(name_log);

    /* fecha o arquivo */
    fclose(arq);
}