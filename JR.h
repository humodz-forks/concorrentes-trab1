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


/*
    inicializaVariaveis cria e retorna uma struct do tipo MATRIZES
    nela eh alocada todos os vetores dinamicamente,
    e le o arquivo da matriz escolhida anteriomente para as variaveis
    dessas struct
*/
MATRIZES * inicializaVariaveis(int id_matriz,int n_threads);


/*
    erro descobre o novo erro pela maior diferenca
    entre o X(vetor atual da interacao atual) e 
    o OLD_X(vetor da interacao anterior)
*/
double erro (MATRIZES *matrizes, int init_interaction);


/*
    inicializaMetodo encontra as matrizes L,J,R
    como especificado no metodos Jaboc-Richardson
*/
void inicializaMetodo(MATRIZES *matrizes);


/*
    dado a linha e o resultado desejado no arquivo
    o rowTest testa o quao proximo linha atual esta 
    do resultado esperado
*/
double rowTest(MATRIZES *matrizes);


/*
    escreve o vetor final X no arquivo
*/
void writeEndX(MATRIZES *matrizes,FILE *arq_save);


/*
    executa as interacoes para achar o resultado do Jaboc-Richardson
    salva cada interacao e seu respectivo erro no arquivo
    e retorna o numero de interacoes
*/
int inicioInteracaoSequencial(MATRIZES *matrizes,FILE *arq_save);

/*
    cada thread entra nessa funcao,
    descobre quais linhas ira executar
    e as executa

*/
void *interacaoConcorrente(void *args);

/*
    abre as threads para execucoes , 
    e espera todas elas terminarem para encontrar o erro,
    faz o criterio de parada com o erro,
    e executar o rowTest e 
    salva a interacao junto com seu respectivo erro no arquivo

*/
int inicioInteracaoConcorrente(MATRIZES *matrizes,FILE *arq_save);

/*
    faz a media , salva no arquivo o numero de interacoes
    o rowtest e o tempo de execucaos
    e exibe na tela o tempo medio o rowtest e o total de interacoes
*/
void sequencial(int id_matriz);


/*
    faz a media , salva no arquivo o numero de interacoes
    o rowtest e o tempo de execucaos
    e exibe na tela o tempo medio o rowtest e o total de interacoes
*/
void concorrente(int id_matriz,int n_threads);


/*
    desaloca todos os dados alocados dinamicamente
*/
void freeAll(MATRIZES **matrizes);

#endif