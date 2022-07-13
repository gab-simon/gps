#ifndef _LIBbike_t_H
#define _LIBbike_t_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nodo_l {
    double cadence;
    double speed;
    double distance;
    double heart_rate;
    double enhanced_altitude;       /* lista de numeros inteiros */
    struct nodo_l* prox;  /* ponteiro para o proximo   */
};
typedef struct nodo_l nodo_l_t;

struct lista {
    nodo_l_t* ini;      /* ponteiro para o inicio da lista */
    int tamanho;        /* numero de elementos na lista    */
    char nome_bike[100];
};
typedef struct lista lista_t;
struct bike {
    double cadence;
    double speed;
    double distance;
    double heart_rate;
    double enhanced_altitude;
    struct Bike *proximo;    /* Proximo elemento da lista encadeada de Produtos */
};

typedef struct tipo_produto {
    int codigo;                  /* Codigo do produto */
    double preco;                /* Preco do produto */
    struct tipo_produto *proximo;    /* Proximo elemento da lista encadeada de Produtos */
}  T_bike;

int open_log(char *file, char *namepath);

#endif