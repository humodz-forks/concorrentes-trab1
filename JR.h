#ifndef _JR_H_
#define _JR_H_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
typedef struct matrizes
{
    double **MA;
    double *MB;
    double *X;
    double *OLD_X; 
    double *ROW_TEST;
    int **interval_thread;
    pthread_t *array_threads;
    int n_threads;
    int J_ORDER;
    int J_ROW_TEST;
    double J_ERROR;
    int J_ITE_MAX;
    int number_matriz;
}MATRIZES;



MATRIZES * inicializaVariaveis(int id_matriz,int n_threads);

double erro (MATRIZES *matrizes, int init_interaction);

void inicializaMetodo(MATRIZES *matrizes);

double rowTest(MATRIZES *matrizes);

void writeEndX(MATRIZES *matrizes,FILE *arq_save);

int inicioInteracaoSequencial(MATRIZES *matrizes,FILE *arq_save);

void *interacaoConcorrente(void *args);

int inicioInteracaoConcorrente(MATRIZES *matrizes,FILE *arq_save);

void sequencial(int id_matriz);

void concorrente(int id_matriz,int n_threads);

void freeAll(MATRIZES **matrizes);

#endif