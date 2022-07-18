#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libbike.h"

#define TAM_MAX 150
#define LINESIZE 1024

BikeRack_t *initRoot()
{
    /*Aloca mémoria heap*/
    BikeRack_t *root = malloc(sizeof(BikeRack_t));
    if (root == NULL)
        return NULL;

    /*Inicia os itens da struct*/
    root->element = NULL;
    root->lastElement = NULL;
    root->nextRack = NULL;
    root->quant = 0;
    root->gear = malloc(sizeof(char) * TAM_MAX);
    strcpy(root->gear, "");

    return root;
}

BikeData_t *initBike()
{
    /*Aloca mémoria heap*/
    int i = 0;
    BikeData_t *bike = malloc(sizeof(BikeData_t));
    if (bike == NULL)
        return NULL;

    /*Inicia os itens da struct*/
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
    strcpy(bike->gear, "");
    bike->Date.year = 0;
    bike->Date.mounth = 0;
    bike->Date.day = 0;

    for (i = 0; i < 10; i++)
    {
        bike->Histogram.class[i] = 0;
    }

    return bike;
}

// Histogram_t *initHistogram()
// {
//     Histogram_t *histogram = malloc(sizeof(Histogram_t));

//     int i = 0;

//     if (histogram == NULL)
//         return NULL;

//     for (i = 0; i < 10; i++)
//     {
//         histogram->class[i] = 0;
//     }

//     return histogram;
// }

void deleteBikeRack(BikeRack_t *root)
{
    BikeRack_t *auxRack = root;
    Bike_t *auxBike;

    /* Percorre o bicicletario é*/
    while (root != NULL)
    {
        auxBike = auxRack->element;
        while (auxBike != NULL)
        {
            /* Libera memoria dos nodosBicicleta */
            auxRack->element = auxRack->element->nextBike;
            free(auxBike);
            auxBike = auxRack->element;
        }

        auxRack = root;
        root = root->nextRack;
        free(auxRack->gear);
        free(auxRack);
    }

    return;
}

char *readLine(FILE *arq, BikeData_t *bike, char *info, double *valueField, char *nameField)
{

    /* Pega o conteudo da linha e cria uma copia */
    fgets(info, TAM_MAX, arq);
    char saveInfo[TAM_MAX];
    strcpy(saveInfo, info);

    /* Tratamento caso a linha seja vazia */
    if ((strlen(info) <= 1))
        return "linha vazia";

    /* Pega o nome do atributo e usa a copia de info para obter o valor do atributo */
    nameField = strtok(info, ":");
    *valueField = strtof(strtok(saveInfo, strcat(nameField, ":")), NULL);

    return strtok(nameField, ":");
}

/* Obtem o dia, mês e ano dos logs e insere os dados na struct dataInfo presente na struct bicicletaInfo */
void momentData(char *dateMoment, Date_t *dateInfo)
{

    char *token = malloc(sizeof(char) * TAM_MAX);
    if (token == NULL)
    {
        printf("Erro ao criar token!\n");
        return;
    }

    /* Copia o conteudo da string que possui a data para o token */
    strcpy(token, dateMoment);
    char *saveToken = token; /* Usado para dar free no malloc do token */

    // Tratamento do mês
    token = strtok(token, " ");
    token = strtok(NULL, " ");
    if (strcmp(token, "Jan"))
        dateInfo->mounth = 1;
    else if (strcmp(token, "Feb"))
        dateInfo->mounth = 2;
    else if (strcmp(token, "Mar"))
        dateInfo->mounth = 3;
    else if (strcmp(token, "Apr"))
        dateInfo->mounth = 4;
    else if (strcmp(token, "May"))
        dateInfo->mounth = 5;
    else if (strcmp(token, "Jun"))
        dateInfo->mounth = 6;
    else if (strcmp(token, "Jul"))
        dateInfo->mounth = 7;
    else if (strcmp(token, "Aug"))
        dateInfo->mounth = 8;
    else if (strcmp(token, "Sep"))
        dateInfo->mounth = 9;
    else if (strcmp(token, "Oct"))
        dateInfo->mounth = 10;
    else if (strcmp(token, "Nov"))
        dateInfo->mounth = 11;
    else
        dateInfo->mounth = 12;

    // Tratamento do dia
    token = strtok(NULL, " ");
    dateInfo->day = atoi(token);

    // Tratamento do ano
    token = strtok(NULL, " ");
    dateInfo->year = atoi(token);

    free(saveToken);
    return;
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

Bike_t *createNodoBike(BikeData_t *bike)
{
    /* Cria a estrutura e verifica se houve erro no malloc */
    Bike_t *nodoBike = malloc(sizeof(Bike_t));
    if (nodoBike == NULL)
    {
        printf("Error ao criar nodo da bike.");
        return NULL;
    }

    nodoBike->bike = bike;
    nodoBike->nextBike = NULL;

    return nodoBike;
}

void discorvedGear(BikeRack_t *root)
{
    BikeRack_t *roam = root;
    int i = 1;

    printf("As biciletas(gear) encontradas foram: \n");
    while (roam != NULL)
    {
        printf("%d) %s\n", i, roam->gear);
        roam = roam->nextRack;
        i++;
    }

    return;
}

BikeRack_t *getGear(BikeRack_t *root, int op)
{
    BikeRack_t *auxRack = root;

    int i;
    for (i = 0; i < op - 1; i++)
    {
        if (auxRack == NULL)
            break;
        auxRack = auxRack->nextRack;
    }

    return auxRack;
}

void printInfoBike(BikeRack_t *root)
{
    Bike_t *auxBike;
    printf("MODELO                  DATA           DISTÂNCIA(km)   VEL. MEDIA(km/h)   VEL. MAXIMA(km/h)   HR MEDIO    HR MAXIMO    CADENCIA    SUBIDA ACUMULADA\n");
    auxBike = root->element;
    while (auxBike != NULL)
    {
        printf("%-24s", auxBike->bike->gear);
        printf("%02d/%d/%-10d", auxBike->bike->Date.day, auxBike->bike->Date.mounth, auxBike->bike->Date.year);
        printf("%-16.2f", auxBike->bike->distance / 1000);
        printf("%-19.2f", auxBike->bike->speedMed * 3.6);
        printf("%-20.2f", auxBike->bike->speedMax * 3.6);
        printf("%-12.2f", auxBike->bike->heartRateMed);
        printf("%-13.2f", auxBike->bike->heartRateMax);
        printf("%-12.2f", auxBike->bike->cadenceMed);
        printf("%.2f\n", auxBike->bike->clunth_altitude);
        auxBike = auxBike->nextBike;
    }

    return;
}

void printInfos(BikeRack_t *root)
{

    int i = 0;
    Bike_t *bikeAux;
    BikeRack_t *rootAux = root;
    printf("MODELO                          DATA           DISTÂNCIA(km)   VEL. MEDIA(km/h)   VEL. MAXIMA(km/h)   HR MEDIO    HR MAXIMO    CADENCIA    SUBIDA ACUMULADA\n");
    while (rootAux != NULL)
    {
        bikeAux = rootAux->element;
        while (bikeAux != NULL)
        {
            printf("%-30s", bikeAux->bike->gear);
            printf("%02d/%d/%-10d", bikeAux->bike->Date.day, bikeAux->bike->Date.mounth, bikeAux->bike->Date.year);
            printf("%-16.2f", bikeAux->bike->distance / 1000);
            printf("%-19.2f", bikeAux->bike->speedMax * 3.6);
            printf("%-20.2f", bikeAux->bike->speedMed * 3.6);
            printf("%-12.2f", bikeAux->bike->heartRateMax);
            printf("%-13.2f", bikeAux->bike->heartRateMed);
            printf("%-12.2f", bikeAux->bike->cadenceMed);
            printf("%.2f\n", bikeAux->bike->clunth_altitude);

            i++;
            bikeAux = bikeAux->nextBike;
        }
        rootAux = rootAux->nextRack;
    }
    return;
}

void sortByDistance(BikeRack_t *root)
{
    BikeRack_t *auxRack = root;
    Bike_t *bike;
    Bike_t *key;
    int i, j;

    while (auxRack != NULL)
    {
        Bike_t **array = malloc(sizeof(Bike_t) * 150); // Cria vetor para ordenar atividades
        bike = auxRack->element;
        /* Preenche vetor com os nodosBicicleta filhos da raiz */
        for (i = 0; i < auxRack->quant; i++)
        {
            array[i] = bike;
            bike = bike->nextBike;
        }

        /* Algoritmo do insertionSort */
        for (i = 1; i < auxRack->quant; i++)
        {
            key = array[i];
            j = i - 1;
            while (j >= 0 && array[j]->bike->distance >= key->bike->distance)
            {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = key;
        }

        /* Insere os nodos ordenados do array na mesma raiz */
        auxRack->element = array[0];
        for (i = 0; i < auxRack->quant; i++)
        {
            bike = array[i];
            bike->nextBike = array[i + 1];
        }
        auxRack->lastElement = array[auxRack->quant - 1];
        auxRack->lastElement->nextBike = NULL;

        /* Pula para a proxima raiz e libera a memoria do array criado */
        auxRack = auxRack->nextRack;
        free(array);
    }

    return;
}

// void printCumulativeClimp(BikeRack_t *root)
// {

//     int i, tam = 0;
//     BikeRack_t *auxRack = root;
//     Bike_t **array = malloc(sizeof(Bike_t) * 100);

//     /* Acha a quantidade de atividades total */
//     while (auxRack != NULL)
//     {
//         tam = tam + auxRack->quant;
//         auxRack = auxRack->nextRack;
//     }

//     /* Retorna as atividades ordenadas por subida acumulada em um array */
//     auxRack = root;
//     array = sortByCumulativeClimb(auxRack, array, tam);

//     /* Imprime os dados do array */
//     printf("MODELO                  DATA           DISTÂNCIA(km)   VEL. MEDIA(km/h)   VEL. MAXIMA(km/h)   HR MEDIO(bpm)     HR MAXIMO(bpm)    CADENCIA(rpm)    SUBIDA ACUMULADA(m)\n");
//     i = 0;
//     while (i < tam)
//     {
//         printf("%-24s", array[i]->bike->gear);
//         printf("%02d/%d/%-10d", array[i]->bike->Date.day, array[i]->bike->Date.mounth, array[i]->bike->Date.year);
//         printf("%-16.2f", array[i]->bike->distance / 1000);
//         printf("%-19.2f", array[i]->bike->speedMed * 3.6);
//         printf("%-20.2f", array[i]->bike->speedMax * 3.6);
//         printf("%-12.2f", array[i]->bike->heartRateMed);
//         printf("%-13.2f", array[i]->bike->heartRateMax);
//         printf("%-12.2f", array[i]->bike->cadenceMed);
//         printf("%.2f\n", array[i]->bike->clunth_altitude);
//         i++;
//     }

//     /* Libera memoria do array */
//     free(array);
// }

// Histogram_t *Histogram(BikeRack_t *root)
// {
//     int i = 0;
//     Bike_t *bikeAux;
//     BikeRack_t *rootAux = root;
//     Histogram_t *auxHistogram = initHistogram();
//     while (rootAux != NULL)
//     {
//         bikeAux = rootAux->element;
//         while (bikeAux != NULL)
//         {
//             if (((bikeAux->bike->distance / 1000) >= 20) && ((bikeAux->bike->distance / 1000) <= 29))
//                 auxHistogram->class[i] += 1;
//             else if (((bikeAux->bike->distance / 1000) >= 30) && ((bikeAux->bike->distance / 1000) <= 39))
//                 auxHistogram->class[i] += 1;
//             else if (((bikeAux->bike->distance / 1000) >= 40) && ((bikeAux->bike->distance / 1000) <= 49))
//                 auxHistogram->class[i] += 1;
//             else if (((bikeAux->bike->distance / 1000) >= 50) && ((bikeAux->bike->distance / 1000) <= 59))
//                 auxHistogram->class[i] += 1;
//             else if (((bikeAux->bike->distance / 1000) >= 60) && ((bikeAux->bike->distance / 1000) <= 69))
//                 auxHistogram->class[i] += 1;
//             else if (((bikeAux->bike->distance / 1000) >= 70) && ((bikeAux->bike->distance / 1000) <= 79))
//                 auxHistogram->class[i] += 1;
//             else if (((bikeAux->bike->distance / 1000) >= 80) && ((bikeAux->bike->distance / 1000) <= 89))
//                 auxHistogram->class[i] += 1;
//             else if (((bikeAux->bike->distance / 1000) >= 90) && ((bikeAux->bike->distance / 1000) <= 99))
//                 auxHistogram->class[i] += 1;
//             else if (((bikeAux->bike->distance / 1000) >= 100) && ((bikeAux->bike->distance / 1000) <= 109))
//                 auxHistogram->class[i] += 1;
//             else if (((bikeAux->bike->distance / 1000) >= 110) && ((bikeAux->bike->distance / 1000) <= 119))
//                 auxHistogram->class[i] += 1;
//             else if (((bikeAux->bike->distance / 1000) >= 110) && ((bikeAux->bike->distance / 1000) <= 119))
//                 auxHistogram->class[i] += 1;
//         }
//         i++;
//     }

//     return auxHistogram;
// }

// void printHistogram(BikeRack_t *root)
// {
//     int i, j;
//     int lim1 = 20, lim2 = 29;
//     BikeRack_t *rootAux = root;
//     Bike_t *bikeAux;

//     Histogram_t *auxHistogram;
//     auxHistogram = Histogram(root);

//     while (rootAux != NULL)
//     {
//         bikeAux = rootAux->element;
//         while (bikeAux != NULL && lim2 <= 109)
//         {

//             for (i = 0; i <= 10; i++)
//             {
//                 printf("%d - %d |", lim1, lim2);
//                 for (j = 0; auxHistogram->class[i]; j++)
//                 {
//                     printf("*");
//                 }
//                 printf("\n");
//                 lim1 += 10;
//                 lim2 += 10;
//             }
//             printf("       123456789#1233456789#123456789\n");
//             printf("Distancia|              Quantidade\n\n");
//         }
//     }
// }

void printTotal(BikeRack_t *root)
{
    // int i = 0;
    // Bike_t *bikeAux;
    BikeRack_t *rootAux = root;
    printf("Quantidade de Atividades    Total Percorrido(km)    Pedal mais longo(km)    Pedal mais curto(km)    Distância Média(km/h)\n");
    while (rootAux != NULL)
    {
        printf("%d", rootAux->quant);
        // bikeAux = rootAux->element;
        // // while (bikeAux != NULL)
        // // {
        // //     printf("%-30s", bikeAux->bike->gear);
        // //     printf("%02d/%d/%-10d", bikeAux->bike->Date.day, bikeAux->bike->Date.mounth, bikeAux->bike->Date.year);
        // //     printf("%-16.2f", bikeAux->bike->distance / 1000);
        // //     printf("%-19.2f", bikeAux->bike->speedMax * 3.6);
        // //     printf("%-20.2f", bikeAux->bike->speedMed * 3.6);
        // //     printf("%-12.2f", bikeAux->bike->heartRateMax);
        // //     printf("%-13.2f", bikeAux->bike->heartRateMed);
        // //     printf("%-12.2f", bikeAux->bike->cadenceMed);
        // //     printf("%.2f\n", bikeAux->bike->clunth_altitude);

        // //     i++;
        // //     bikeAux = bikeAux->nextBike;
        // // }
        rootAux = rootAux->nextRack;
    }
}

void sortByCumulativeClimb(BikeRack_t *root)
{
    BikeRack_t *auxRack = root;
    Bike_t *bike;
    Bike_t *key;
    int i, j;

    while (auxRack != NULL)
    {
        Bike_t **array = malloc(sizeof(Bike_t) * 150); // Cria vetor para ordenar atividades
        bike = auxRack->element;
        /* Preenche vetor com os nodosBicicleta filhos da raiz */
        for (i = 0; i < auxRack->quant; i++)
        {
            array[i] = bike;
            bike = bike->nextBike;
        }

        /* Algoritmo do insertionSort */
        for (i = 1; i < auxRack->quant; i++)
        {
            key = array[i];
            j = i - 1;
            while (j >= 0 && array[j]->bike->clunth_altitude >= key->bike->clunth_altitude)
            {
                array[j + 1] = array[j];
                j--;
            }
            array[j + 1] = key;
        }

        /* Insere os nodos ordenados do array na mesma raiz */
        auxRack->element = array[0];
        for (i = 0; i < auxRack->quant; i++)
        {
            bike = array[i];
            bike->nextBike = array[i + 1];
        }
        auxRack->lastElement = array[auxRack->quant - 1];
        auxRack->lastElement->nextBike = NULL;

        /* Pula para a proxima raiz e libera a memoria do array criado */
        auxRack = auxRack->nextRack;
        free(array);
    }
}

void insertBike(BikeRack_t *root, BikeData_t *bike, int element)
{
    Bike_t *NodoNextBike;

    /* Caso seja a primeira insercao */
    if (root->element == NULL)
    {
        root->element = createNodoBike(bike);
        root->quant++;
        root->lastElement = root->element;
        root->element->id = element;
        strcpy(root->gear, bike->gear);
    }
    /* Caso modelo analisado de bicicleta ja tenha sido inserido */
    else if (strcmp(root->gear, bike->gear) == 0)
    {
        NodoNextBike = createNodoBike(bike);
        root->quant++;
        root->lastElement->nextBike = NodoNextBike;
        root->lastElement = NodoNextBike;
        root->lastElement->id = element;
    }
    /* Caso modelo analisado de bicicleta nao tenha sido inserido */
    else
    {
        root->nextRack = initRoot();
        root->nextRack->element = createNodoBike(bike);
        root->nextRack->quant++;
        root->nextRack->lastElement = root->nextRack->element;
        root->nextRack->element->id = element;
        strcpy(root->nextRack->gear, bike->gear);
    }
    return;
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
    momentData(info, &bike->Date);

    int quantAltitude = 0;
    int quantHeartRate = 0;
    int quantCadence = 0;
    while (!feof(arq))
    {

        field = readLine(arq, bike, info, &value, field);

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
            if (value >= bike->speedMax)
                bike->speedMax = value;
            bike->speedTotal = bike->speedTotal + value;
        }

        /* Heart Rate */
        else if (!strcmp(field, "heart_rate") && value > 0)
        {
            if (value > bike->heartRateMax)
                bike->heartRateMax = value;
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
