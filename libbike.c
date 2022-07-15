#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libbike.h"

#define TAM_MAX 100
#define LINESIZE 1024

BikeRack_t *initRoot()
{
    BikeRack_t *root = malloc(sizeof(BikeRack_t));
    if (root == NULL)
    {
        printf("Erro ao criar root!");
        return NULL;
    }
    root->element = NULL;
    root->nextRack = NULL;
    root->quant = 0;
    root->gear = malloc(sizeof(char) * TAM_MAX);

    return root;
}

BikeData_t *initBike()
{
    BikeData_t *bike = malloc(sizeof(BikeData_t));
    if (bike == NULL)
        return NULL;

    bike->altitude = 0;
    bike->clunth_altitude = 0;
    bike->quantData = 0;
    bike->distance = 0;
    bike->speedTotal = 0;
    bike->speedMax = 0;
    bike->speedMed = 0;
    bike->heartRateTotal = 0;
    bike->heartRateMax = 0;
    bike->heartRateMed = 0;
    bike->cadenceTotal = 0;
    bike->cadenceMed = 0;
    bike->gear = malloc(sizeof(char) * TAM_MAX);
    // strcpy(bike->gear, "");

    bike->Date.year = 0;
    bike->Date.mounth = 0;
    bike->Date.day = 0;

    return bike;
}

char *createBikeByGear(FILE *arq, char *gear)
{

    /* Cria o token e verifica se houve erro no malloc */
    char *token = malloc(sizeof(char) * TAM_MAX);
    if (token == NULL)
    {
        printf("Erro ao criar token!\n");
        return NULL;
    }

    /* Obtem o conteudo da linha do arquivo */
    fgets(token, TAM_MAX, arq);
    char *saveToken = token; /* Usado para dar free no malloc do token */

    /* Recorta o nome do field "Gear" e pega o modelo juntamente com espaços */
    token = strtok(token, ": ");
    token = strtok(NULL, " ");
    while (token != NULL)
    {
        strcat(gear, token);
        strcat(gear, " ");
        token = strtok(NULL, " ");
    }
    strtok(gear, "\n");
    free(saveToken);
    return gear;
}

char *getGearBike(FILE *arq, char *gear)
{

    /* Cria o token e verifica se houve erro no malloc */
    char *token = malloc(sizeof(char) * TAM_MAX);
    if (token == NULL)
    {
        printf("Erro ao criar token!\n");
        return NULL;
    }

    /* Obtem o conteudo da linha do arquivo */
    fgets(token, TAM_MAX, arq);
    char *saveToken = token; /* Usado para dar free no malloc do token */

    /* Recorta o nome do atributo "Gear" e pega o modelo juntamente com espaços */
    token = strtok(token, ": ");
    token = strtok(NULL, " ");
    while (token != NULL)
    {
        strcat(gear, token);
        strcat(gear, " ");
        token = strtok(NULL, " ");
    }
    strtok(gear, "\n");
    free(saveToken);
    return gear;
}

int open_log(char *file, char *namepath)
{
    FILE *arq;

    BikeRack_t *root = initRoot();

    long numbytes;
    char *text;
    char line[LINESIZE + 1];
    char *separator;
    double value = 0;
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
                value += strtod(content, &eptr);
                printf("value: %.6f km\n", value / 1000);
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

BikeData_t *bikeInfo(FILE *arq)
{
    BikeData_t *bike = initBike();

    /* Cria info e verifica se houve erro no malloc */
    char *info = malloc(sizeof(char) * TAM_MAX);

    if (info == NULL)
    {
        printf("Erro ao criar info!\n");
        return NULL;
    }
    /* Declaração de variáveis usadas na função */
    double value;
    char *field;

    /* Modelo da bicicleta */
    bike->gear = getGearBike(arq, bike->gear);

    /* Data do log */
    fgets(info, TAM_MAX, arq);
    // formataData(info, &bike->Date);
    int quantAltitude = 0;
    int quantHeartRate = 0;
    int quantCadence = 0;
    while (!feof(arq))
    {

        field = lerLinha(arq, bike, &value, field, info);

        /* Subida acumulada */
        if (!strcmp(field, "altitude"))
        {
            if (value > bike->altitude && bike->altitude > 0)
                bike->clunth_altitude = bike->clunth_altitude + value - bike->altitude;
            bike->altitude = value;
            quantAltitude++;
        }

        /* Distância */
        else if (!strcmp(field, "distance"))
            bike->distance = value;

        /* Velocidade */
        else if (!strcmp(field, "speed"))
        {
            if (value > bike->speedMax)
                bike->speedMax = value;
            bike->speedTotal = bike->speedTotal + value;
        }

        /* Heart Rate */
        else if (!strcmp(field, "heart_rate") && value > 0)
        {
            if (value > bike->heartRateMax)
                bike->heartRateMax= value;
            bike->heartRateTotal = bike->heartRateTotal + value;
            quantHeartRate++;
        }

        /* Cadence */
        else if (!strcmp(field, "cadence") && value > 0)
        {
            bike->cadenceTotal = bike->cadenceTotal + value;
            quantCadence++;
        }
    }

    /* Cálculo das médias */
    bike->speedMed = bike->speedTotal / bike->quantData;
    bike->heartRateMed = bike->heartRateTotal / quantHeartRate;
    bike->cadenceMed = bike->cadenceTotal / quantCadence;

    free(info);
    return bike;
}
