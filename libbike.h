#ifndef _LIBbike_t_H
#define _LIBbike_t_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// typedef struct
// {
//     char date;
// } bike_t;

typedef struct
{
    double cadence;
    double speed;
    double distance;
    double heart_rate;
    double enhanced_altitude;
} infos_t;

int open_log(char *file, char *namepath);

#endif