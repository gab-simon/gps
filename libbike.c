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

void deleteBikeRack(BikeRack_t *root)
{
    /* Variaveis auxiliares */
    BikeRack_t *auxRack = root;
    Bike_t *auxBike;

    /* Percorre todos os nodosRaiz e nodosBicicleta de forma iterativa*/
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

Bike_t *createNodoBike(Bike_t *bike)
{
    /* Cria a estrutura e verifica se houve erro no malloc */
    Bike_t *nodoBike = malloc(sizeof(Bike_t));
    if (nodoBike == NULL)
    {
        printf("Error ao criar nodo da bike.");
        return NULL;
    }

    /* Atribuicao de valores default */
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

void insertionSortDistancia(BikeRack_t *root)
{
    BikeRack_t *auxRack = root;
    Bike_t *bike;
    Bike_t *key;
    int i, j;

    /* While para percorrer os nodosRaiz */
    while (root != NULL)
    {
        Bike_t **array = malloc(sizeof(Bike_t) * root->quant); // Cria vetor para ordenar atividades
        bike = root->element;
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

void insertBike(BikeRack_t *root, BikeData_t *bike, int element)
{

    BikeRack_t *NodoNextBike;

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
        root->lastElement->nextBike = NodoNextBike;
        root->lastElement = NodoNextBike;
        root->quant++;
        root->lastElement->id = element;
    }
    /* Caso modelo analisado de bicicleta nao tenha sido inserido */
    else
    {
        root->nextRack = initRoot();
        root->nextRack->element = createNodoBike(bike);
        root->nextRack->quant++;
        root->nextRack->element = root->nextRack->element;
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
    // formataData(info, &bike->Date);
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
            if (value > bike->speedMax)
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
