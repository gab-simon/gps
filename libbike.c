#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libbike.h"

#define LINESIZE 1024

lista_t *lista_cria()
{
    lista_t *l;

    if ((l = malloc(sizeof(lista_t))) == NULL)
        return 0;

    l->ini = NULL;
    l->tamanho = 0;
    return l;
}

lista_t *lista_destroi(lista_t *l)
{
    nodo_l_t *tmp1 = l->ini;
    nodo_l_t *tmp2 = l->ini->prox;

    while ((tmp1 != NULL) && (tmp2 != NULL))
    {
        free(tmp1);
    }

    free(l);
    l = NULL;

    return NULL;
}

int lista_insere_inicio(lista_t *l, double distance)
{
    nodo_l_t *tmp;

    if ((tmp = malloc(sizeof(nodo_l_t))) == NULL)
        return 0;

    tmp->bike->distance = distance;

    tmp->prox = l->ini;
    l->ini = tmp;
    l->tamanho++;

    return 1;
}

void lista_imprime(lista_t *l)
{
    nodo_l_t *tmp = l->ini;

    while (tmp != NULL)
    {
        printf("%.f\taaaaaaaaaaaaaaaaaaa", tmp->distance);
        tmp = tmp->prox;
    }
    printf("\n\n");
}

int open_log(char *file, char *namepath)
{
    FILE *arq;
    lista_t *l;

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
    lista_insere_inicio(l, valor);
    /* fecha o arquivo */
    // free(content);
    // free(file);
    // free(namepath);

    lista_imprime(l);
    lista_destroi(l);
    fclose(arq);

    return 0;
}