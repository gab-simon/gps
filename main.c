#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>

#include "libbike.h"
#define LINESIZE 100

int open_log(char *file, char *namepath, BikeRack_t *root, BikeRack_t *copyRoot, BikeData_t **allBikes, int id)
{
    FILE *arq;

    char name_log[LINESIZE];

    strcpy(name_log, file);
    strcat(name_log, "/");
    strcat(name_log, namepath);

    arq = fopen(name_log, "r");
    printf("\n");

    if (!arq)
    {
        perror("Erro ao abrir/criar arquivo");
        exit(1);
    }

    while (!feof(arq))
    {
        allBikes[id] = bikeInfo(arq);

        copyRoot = root;
        while ((strcmp(copyRoot->gear, allBikes[id]->gear) != 0) && copyRoot->nextRack != NULL)
            copyRoot = copyRoot->nextRack;
        insertBike(copyRoot, allBikes[id], id);
    }

    fclose(arq);
}

void freeVetorBicicletas(BikeData_t **bike, int qtArquivos)
{
    int i;
    for (i = 0; i < 20; i++)
    {
        free(bike[i]->gear);
        free(bike[i]);
    }

    free(bike);
    return;
}

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
    else
    {
        perror("Erro ao abrir diretorio");
        exit(1);
    }

    dp = opendir(namepath);

    BikeRack_t *root = initRoot();
    BikeRack_t *copyRoot;
    BikeData_t **allBikes = malloc(sizeof(BikeData_t *) * 500);

    copyRoot = root;
    int i = 0;

    while ((dirp = readdir(dp)) != NULL)
    {
        if (dirp->d_type != 4)
        {
            printf("\n%d", i);
            open_log(namepath, dirp->d_name, root, copyRoot, allBikes, i);
            i++;
        }
        else {
            printf("\n Não é um arquivo log\n\n");
        }
    }

    printf("1. Mostra todas as bicicletas encontradas.\n");
    printf("2. Informe uma bicicleta.\n");
    printf("3. Lista todas atividades agrupadas por bicicleta e ordenadas pela data.\n");
    printf("4. Lista todas atividades agrupadas por bicicleta e ordenadas pela distância.\n");
    printf("5. Lista todas atividades ordenadas pela subida acumulada.\n");
    printf("6. Histograma.\n");
    printf("Sair");
    scanf("%i", &op);

    if (op == 1)
    {
        printf("\n\n\nResultado\n");
        discorvedGear(root);
    }
    if (op == 4) {
        printf("\n\n\nResultado\n");
        insertionSortDistancia(copyRoot);
    }

    closedir(dp);

    deleteBikeRack(root);
    exit(EXIT_SUCCESS);
    exit(0);
}