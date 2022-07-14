#ifndef _LIBbike_t_H
#define _LIBbike_t_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bike {
    double cadence;
    double speed;
    double distance;
    double heart_rate;
    double enhanced_altitude;
};
typedef struct bike;
struct nodo_l {
    struct bike;
    struct nodo_l* prox;
};
typedef struct nodo_l nodo_l_t;

struct lista {
    nodo_l_t* ini;
    int tamanho;
    char nome_bike[100];
};
typedef struct lista lista_t;

lista_t* lista_cria ();
lista_t* lista_destroi (lista_t* l);
int lista_insere_inicio (lista_t* l, double distance);
void lista_imprime (lista_t* l);
int open_log(char *file, char *namepath);

#endif