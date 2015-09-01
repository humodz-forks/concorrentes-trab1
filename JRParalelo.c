#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


typedef struct matrizes{
    float **MA;
    float **MLR;
    float *MB;
    float *X;
    float *OLD_X;
    int J_ORDER;
    int index;
}MATRIZES;


//init_interaction eh inicial se ele valer 0, e ja esta na primeira ou
//mais interacao se tiver um valor diferente de 0
float erro (MATRIZES *matrizes,int init_interaction){
    float ERRO = 0;
    float diferenca;
    for (int i=0; i < matrizes->J_ORDER; ++i)
    {
        diferenca = (init_interaction)? matrizes->X[i] - matrizes->OLD_X[i] : matrizes->X[i];
        if(diferenca < 0) diferenca = -diferenca;
        if(diferenca > ERRO) ERRO = diferenca;
    }
    return ERRO;
}

void * paralelo(void *args){

    MATRIZES *matrizes = (MATRIZES *) args;
    matrizes->OLD_X[matrizes->index] = matrizes->X[matrizes->index];
    matrizes->X[matrizes->index] = matrizes->MB[matrizes->index]/matrizes->MA[matrizes->index][matrizes->index];
    for (int j=0; j<matrizes->J_ORDER; ++j)
    {
        matrizes->X[matrizes->index] -= (matrizes->X[j]*matrizes->MLR[matrizes->index][j]);
    }
    return NULL;
}


int main ()
{
    MATRIZES *matrizes=NULL;
    clock_t end, start;
    int J_ROW_TEST, J_ITE_MAX;
    float J_ERROR;    
    pthread_t *array_threads=NULL;
    /* Inicio do programa - leitura dos valores iniciais */
    start = clock();
    matrizes = (MATRIZES *) malloc(sizeof(MATRIZES));
    scanf ("%d %d %f %d", &(matrizes->J_ORDER), &J_ROW_TEST, &J_ERROR, &J_ITE_MAX);
    array_threads = (pthread_t *) malloc(sizeof(pthread_t)*(matrizes->J_ORDER));
    matrizes->MA = (float **) malloc (sizeof(float *)*(matrizes->J_ORDER));
    matrizes->MLR = (float **) malloc (sizeof(float *)*(matrizes->J_ORDER));
    matrizes->MB = (float *) malloc (sizeof(float )*(matrizes->J_ORDER));
    matrizes->X = (float *) malloc (sizeof(float )*(matrizes->J_ORDER));
    matrizes->OLD_X = (float *) malloc (sizeof(float )*(matrizes->J_ORDER));
    
    /* Alocação da matrizes A*/
    for(int i = 0; i<matrizes->J_ORDER; ++i)
    {
        matrizes->MA[i] = (float *) malloc (sizeof(float)*matrizes->J_ORDER);
        matrizes->MLR[i] = (float *) malloc (sizeof(float)*matrizes->J_ORDER);
    }
    
    /* Leitura dos valores de A*/
    for(int i = 0; i< matrizes->J_ORDER; ++i)
    {
        for (int j = 0; j<matrizes->J_ORDER ; ++j)
        {
            scanf ("%f", &(matrizes->MA[i][j]) );
        }
    }
    
    /* Leitura dos valores de B*/
    for(int i = 0; i<matrizes->J_ORDER; ++i)
    {
        scanf ("%f", &(matrizes->MB[i]) );
    }


    printf("tempo de leitura: %lf\n",double(clock() - start)/CLOCKS_PER_SEC);
    start = clock();

    /* Encontra as matrizes L*, I, R* de dentro da matrix MA */
    for(int i = 0; i< matrizes->J_ORDER; ++i)
    {
        for (int j = 0; j<matrizes->J_ORDER ; ++j)
        {
            if(i!=j) matrizes->MLR[i][j]= matrizes->MA[i][j]/matrizes->MA[i][i];
        }
        matrizes->X[i] = matrizes->MB[i]/matrizes->MA[i][i]; /* X é inicializado com o valor de MB* */
        matrizes->MLR[i][i] = 0; /*zera a diagonal principal */
    }
    
    /* Processo iterativo do método Jacobi-Richardson
    
    Iteração inicial, X é inicializado com o valor de MB* */
    printf("Iteracao\t");
    printf("Erro\n");

    float ERRO = erro(matrizes,0);

    printf("0\t%f\n", ERRO);
    int k;
    for ( k = 1; k < J_ITE_MAX && ERRO > J_ERROR; ++k)
    {
        printf("%d\t%f\n", k, ERRO);
        printf("\n");
        for(int i = 0; i < matrizes->J_ORDER; ++i)
        {
            matrizes->index = i;
            if(pthread_create(&array_threads[i], NULL, paralelo, matrizes)) {
                fprintf(stderr, "Error creating thread\n");
                return 1;
            }
        }
        ERRO = erro(matrizes,1);
    }

    printf("Numero de Interacoes: %d\n",k);
    float rowtest = 0;
    for (int i = 0; i<matrizes->J_ORDER; ++i)
    {
        rowtest+= matrizes->MA[J_ROW_TEST][i]*matrizes->X[i];
    }
    printf("RowTest: %d => [%f] =? %f\n", J_ROW_TEST, rowtest ,matrizes->MB[J_ROW_TEST]);

    printf("tempo de execucao: %lf\n",double(clock() - start)/CLOCKS_PER_SEC);

    /* Encerramento do programa - Liberação de memória */
    for(int i = 0; i<matrizes->J_ORDER; ++i)
    {
        free(matrizes->MA[i]);
        free(matrizes->MLR[i]);
    }
    free(matrizes->MA);
    free(matrizes->MLR);
    free(matrizes->MB);
    free(matrizes->X);
    free(matrizes->OLD_X);
    free(matrizes);

  
    return 0;
}