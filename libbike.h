#ifndef _LIBbike_t_H
#define _LIBbike_t_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Histogram
{
    int *class;
} Histogram_t;
typedef struct Date
{
    int day;
    int mounth;
    int year;
} Date_t;

typedef struct BikeData
{
    Date_t Date;
    Histogram_t *Histogram;
    char *gear;
    double distance;
    double speedTotal;
    double speedMed;
    double speedMax;
    double heartRateTotal;
    double heartRateMed;
    double heartRateMax;
    double cadenceTotal;
    double cadenceMed;
    double altitude;
    double clunth_altitude;

    int quantData;
} BikeData_t;

typedef struct Bike
{
    BikeData_t *bike;
    struct Bike *nextBike;
    int id;
} Bike_t;

typedef struct BikeRack
{
    struct BikeRack *nextRack;
    struct BikeRack *backRack;
    Bike_t *element;
    Bike_t *lastElement;

    int quant;
    char *gear;
} BikeRack_t;

BikeRack_t *initRoot();
BikeRack_t* getGear(BikeRack_t *root, int op);
Bike_t *createNodoBike(BikeData_t *bike);
BikeData_t *initBike();
BikeData_t *bikeInfo(FILE *arq);

// Histogram_t *initHistogram();
// Histogram_t *Histogram(BikeRack_t *root);

void sortByCumulativeClimb(BikeRack_t *root);
void sortByDistance(BikeRack_t *root);

void deleteBikeRack(BikeRack_t *root);
void discorvedGear(BikeRack_t *root);

void insertBike(BikeRack_t *root, BikeData_t *bike, int element);
void printInfos(BikeRack_t *root);
void printInfoBike(BikeRack_t *root);

void momentData(char *dateMoment, Date_t *dateInfo);

void printHistogram(BikeRack_t *root);
void printTotal(BikeRack_t *root);
char *getGearBike(FILE *arq, char *gear);
char *createBikeByGear(FILE *arq, char *gear);
char *readLine(FILE *arq, BikeData_t *bike, char *info, double *valueField, char *nameField);

#endif