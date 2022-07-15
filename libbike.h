#ifndef _LIBbike_t_H
#define _LIBbike_t_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Date
{
    int day;
    int mounth;
    int year;

} date_t;

typedef struct BikeData
{
    date_t Date;
    char *gear;
    double distance;

    double speedTotal;
    double speedMed;
    double speedMax;

    double heartRateTotal;
    double heartRateMed;
    double heartRateMax;
    // int hrValid; da pra ser uma variavel local

    double cadenceTotal;
    double cadenceMed;
    // int cadenceVal; da pra ser uma variavel local

    double altitude;
    double clunth_altitude;

    int quantData;
} BikeData_t;

typedef struct Bike
{
    BikeData_t *bike;
    struct bike *nextBike;
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
BikeData_t *initBike();
char *getGearBike(FILE *arq, char *gear);
char *createBikeByGear(FILE *arq, char *gear);
int open_log(char *file, char *namepath);

#endif