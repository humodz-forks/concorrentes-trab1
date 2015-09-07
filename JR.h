#ifndef _JR_H_
#define _JR_H_
typedef struct matrizes
{
    double **MA;
    double *MB;
    double *X;
    double *OLD_X; 
    double *ROW_TEST;
    int J_ORDER;
    int **interval_thread;
    pthread_t *array_threads;
    int n_threads;
}MATRIZES;

#endif