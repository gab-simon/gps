#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libbike.h"

#define LINESIZE 1024

int open_log(char *file, char *namepath)
{
    FILE *arq;
    long numbytes;
    char *text;
    char line[LINESIZE + 1];
    char *separator;
    double valor = 0;
    char *content;
    char *eptr;
    char *name_log;

    /* separadores */
    // separator = malloc(LINESIZE);
    name_log = malloc(LINESIZE * 10);
    eptr = malloc(LINESIZE);
    content = malloc(LINESIZE);

    strcat(name_log, file);
    strcat(name_log, "/");
    strcat(name_log, namepath);

    arq = fopen(name_log, "r");
    printf(name_log);

    if (!arq)
    {
        perror("Erro ao abrir/criar arquivo");
        printf("\n\n%s\n", name_log);
        exit(1);
    }

    // char ch;
    // while ((ch = fgetc(arq)) != EOF)
    // {
    //     putchar(ch);
    // }

    fgets(line, LINESIZE, arq); /* tenta ler uma linha */
    while (!feof(arq))          /* testa depois de tentar ler! */
    {
        separator = strtok(line, ":");
        // printf("%s\n", separator);

        // content = strtok(NULL, " ");
        // printf("%s\n", content);

        if (strcmp(separator, "distance") == 0)
        {
            content = strtok(NULL, " ");
            printf("%s\n", content);
            if (strtod(content, &eptr) != 0)
            {
                valor += strtod(content, &eptr);
                printf("valor: %.6f km\n", valor / 1000);
            }
        }
        /* printf("%s \n", separator); */

        fgets(line, LINESIZE, arq); /* tenta ler a próxima linha */
    }

    /* fecha o arquivo */
    // free(content);
    // free(file);
    // free(namepath);
    fclose(arq);

    return 0;
}