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

    /* Concatena pasta + / + arquivo */
    strcpy(name_log, file);
    strcat(name_log, "/");
    strcat(name_log, namepath);

    arq = fopen(name_log, "r");

    if (!arq)
    {
        perror("Erro ao abrir/criar arquivo");
        exit(1);
    }

    while (!feof(arq))
    {
        /* Insere bicicletas pelo id */
        allBikes[id] = bikeInfo(arq);

        /* Cria uma copia do root principal */
        copyRoot = root;

        /* Compara gear para verificar se ja existe no bicicletario*/
        while ((strcmp(copyRoot->gear, allBikes[id]->gear) != 0) && copyRoot->nextRack != NULL)
            copyRoot = copyRoot->nextRack;
        insertBike(copyRoot, allBikes[id], id);
    }

    fclose(arq);
    return 0;
}

// void freeVetorBicicletas(BikeData_t **bike, int qtArquivos)
// {
//     int i;
//     for (i = 0; i < 20; i++)
//     {
//         free(bike[i]->gear);
//         free(bike[i]);
//     }

//     free(bike);
//     return;
// }

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;
    char *name_file;

    int op = 1;
    int opBike;

    if (strcmp(argv[1], "-d") == 0)
    {
        name_file = argv[2];
    }
    else
    {
        perror("Erro ao abrir diretorio");
        exit(1);
    }

    dp = opendir(name_file);

    BikeRack_t *root = initRoot();
    BikeRack_t *copyRoot;
    BikeData_t **allBikes = malloc(sizeof(BikeData_t *) * 100);

    copyRoot = root;
    int i = 0;

    printf("Logs estao sendo processados.");
    while ((dirp = readdir(dp)) != NULL)
    {
        if (dirp->d_type != 4)
        {
            open_log(name_file, dirp->d_name, root, copyRoot, allBikes, i);
            i++;
        }
        else
        {
            printf("-");
        }
    }

    printf("\n1. Mostra todas as bicicletas encontradas.\n");
    printf("2. Informe uma bicicleta.\n");
    printf("3. Lista todas atividades agrupadas por bicicleta e ordenadas pela data.\n");
    printf("4. Lista todas atividades agrupadas por bicicleta e ordenadas pela distância.\n");
    printf("5. Lista todas atividades ordenadas pela subida acumulada.\n");
    printf("6. Histograma.\n");
    printf("7. Plotar Histograma.\n");
    printf("8. Sair.\n");

    while (op != 8)
    {
        printf("Escolha uma opção: \n");
        scanf("%i", &op);
        if (op == 1)
        {
            printf("\n\n\nResultado\n");
            discorvedGear(root);
        }
        if (op == 2)
        {
            discorvedGear(root);
            printf("Informe a bicicleta desejada: ");
            scanf("%i", &opBike);
            copyRoot = root;

            if (opBike <= 0)
            {
                printf("Informe a bicicleta desejada: ");
            }
            else
            {
                copyRoot = getGear(copyRoot, opBike);
                printInfoBike(copyRoot);
            }
        }
        if (op == 4)
        {
            printf("\n\n\nResultado\n");
            sortByDistance(copyRoot);
            printInfos(copyRoot);
        }
        if (op == 5)
        {
            printf("\n\n\nResultado\n");
            sortByCumulativeClimb(copyRoot);
            printInfos(copyRoot);
        }
        if (op == 6)
        {
            printf("\n\n\nResultado\n");
        }
        if (op == 8)
        {
            printTotal(copyRoot);
        }
    }

    closedir(dp);
    deleteBikeRack(root);
    exit(EXIT_SUCCESS);
    exit(0);
}