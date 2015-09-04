#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/*
MA       = 
MB       = 
X        =
OLD_X    =
ROW_TEST = 
interval_thread = intervalo de linhas da matriz que cada thread ira ler
*/
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

//double erro (double *X, double *OLD_X, int J_ORDER)
double erro (MATRIZES *matrizes, int init_interaction)
{
    double ERRO = 0;
    double diferenca;
    double divisor = 0;
    double X_aux;
    for (int i = 0 ; i < matrizes->J_ORDER; ++i)
    {
        /* Calcula modulo infinito de Xk - Xk-1 */
        diferenca = (init_interaction)? matrizes->X[i] - matrizes->OLD_X[i] : matrizes->X[i];
        if(diferenca < 0.0) diferenca = -diferenca;
        if(diferenca > ERRO) ERRO = diferenca;
        /* Calcula o erro infinito de Xk */
        X_aux = matrizes->X[i];
        if(X_aux < 0.0) X_aux = -X_aux;
        if(X_aux > divisor) divisor = X_aux;
    }
    /* Divide os dois erros infinitos calculados anteriormente = Encontra o erro final */
    return ERRO/divisor;
}

void * paralelo(void *args){

    MATRIZES *matrizes = (MATRIZES *) args;

    pthread_t self = pthread_self();
    int i =0;

    /*Descubro qual a thread que estou*/
    for(i=0; i < matrizes->n_threads; ++i)
    {
        if(matrizes->array_threads[i]==self)
            break;
    }
    for(int j=matrizes->interval_thread[i][0]; j <= matrizes->interval_thread[i][1]; ++j)
    {
        matrizes->OLD_X[j] = matrizes->X[j];
        matrizes->X[j] = matrizes->MB[j];
        for(int k=0; k < matrizes->J_ORDER; k++)
        {
            matrizes->X[j] -= (matrizes->OLD_X[k] * matrizes->MA[j][k]);
        }
    }

    /*matrizes->OLD_X[i] = matrizes->X[i];
    matrizes->X[i] = matrizes->MB[i];
    for(int j=0; j<matrizes->J_ORDER; ++j)
    {
        matrizes->X[i]-=(matrizes->X[j]* matrizes->MA[i][j]);
    }*/
    return NULL;
}

int main ()
{
    clock_t end, start;
    int J_ROW_TEST, J_ITE_MAX;
    double J_ERROR;
    
    //double **MA, *MB, *X, *OLD_X, *ROW_TEST; 
    MATRIZES *matrizes=NULL;
    /* Inicio do programa - leitura dos valores iniciais */
    start = clock();
    matrizes = (MATRIZES *) malloc(sizeof(MATRIZES));
    scanf ("%d %d %lf %d", &(matrizes->J_ORDER), &J_ROW_TEST, &J_ERROR, &J_ITE_MAX);
    matrizes->MA = (double **) malloc (sizeof(double *)*matrizes->J_ORDER);
    matrizes->MB = (double *) malloc (sizeof(double )*matrizes->J_ORDER);
    matrizes->X = (double *) malloc (sizeof(double )*matrizes->J_ORDER);
    matrizes->OLD_X = (double *) malloc (sizeof(double )*matrizes->J_ORDER);
    matrizes->ROW_TEST = (double *) malloc (sizeof(double )* (matrizes->J_ORDER+1));
    matrizes->n_threads=4;//4 pois eh o que meu pc possui
    matrizes->interval_thread = (int **) malloc(sizeof(int *)* matrizes->n_threads);
    matrizes->array_threads = (pthread_t *) malloc(sizeof(pthread_t)* matrizes->n_threads);

    for(int i = 0; i < matrizes->n_threads; ++i)
    {
        // 2 pois conta a linha inicial e final que cada thread vai ler
        matrizes->interval_thread[i] = (int *) malloc(sizeof(int)*2); 
        if(i==0)
        {
            matrizes->interval_thread[i][0] = 0;
            matrizes->interval_thread[i][1] = matrizes->J_ORDER/matrizes->n_threads -1;
        }
        else
        {
            matrizes->interval_thread[i][0] =  
                                matrizes->J_ORDER/matrizes->n_threads + matrizes->interval_thread[i-1][0];

            if(i+1 == matrizes->n_threads)
            {//garante que quando J_ORDER/n_threads nao der inteiro pegue todas as linhas
             //deixando a ultima thread com algumas linhas a mais, caso a divisao nao der inteiro
            
                matrizes->interval_thread[i][1] = matrizes->J_ORDER-1;
            }
            else
            {
                matrizes->interval_thread[i][1] = 
                                matrizes->J_ORDER/matrizes->n_threads +
                                         matrizes->interval_thread[i-1][1];
            }
        }
    }
    
    /* Alocação da matrizes A*/
    for(int i = 0; i<matrizes->J_ORDER; ++i)
    {
        matrizes->MA[i] = (double *) malloc (sizeof(double)*matrizes->J_ORDER);
    }
    
    /* Leitura dos valores de A*/
    for(int i = 0; i< matrizes->J_ORDER; ++i)
    {
        for (int j = 0; j<matrizes->J_ORDER ; ++j)
        {
            scanf ("%lf", &(matrizes->MA[i][j]) );
        }
    }
    
    /* Leitura dos valores de B*/
    for(int i = 0; i<matrizes->J_ORDER; ++i)
    {
        scanf ("%lf", &(matrizes->MB[i]) );
    }
    printf("tempo de leitura: %lf\n",double(clock() - start)/CLOCKS_PER_SEC);
    start = clock();

    matrizes->ROW_TEST[matrizes->J_ORDER]=matrizes->MB[J_ROW_TEST];
    for(int i = 0; i<matrizes->J_ORDER; ++i)
        matrizes->ROW_TEST[i] = matrizes->MA[J_ROW_TEST][i]; /*salva a linha de teste*/
    
    /* Encontra as matrizes L*, I, R* de dentro da matrix MA */
    for(int i = 0; i< matrizes->J_ORDER; ++i)
    {
        for (int j = 0; j<matrizes->J_ORDER ; ++j)
        {
            if(i!=j) matrizes->MA[i][j]/= matrizes->MA[i][i];
        }
        matrizes->MB[i]/= matrizes->MA[i][i]; /* X é inicializado com o valor de MB* */
        matrizes->MA[i][i] = 0; /*zera a diagonal principal */
        matrizes->X[i] = matrizes->MB[i];
    }
    
    /* Processo iterativo do método Jacobi-Richardson
    
    Iteração inicial  */
    printf("Iteracao\tErro < %lf\n", J_ERROR);
    //double ERRO = erro(X,NULL, J_ORDER);
    double ERRO = erro(matrizes,0);
    int k;
    /* Iterações até atingir o critério de parada */
    for ( k = 0; ERRO > J_ERROR && k < J_ITE_MAX ; ++k)
    {

        for(int i=0 ; i < matrizes->n_threads ; ++i){
            if(pthread_create(&(matrizes->array_threads[i]), NULL, paralelo, matrizes)) {
                fprintf(stderr, "Error creating thread\n");
                return 1;
            }       
        }
        for(int i = 0; i < matrizes->n_threads ; ++i)
        {
            pthread_join(matrizes->array_threads[i],NULL);
        } 
        
        //}
        ERRO = erro(matrizes, 1);
        printf("%d\t\t%lf\n", k, ERRO);
    }
    
    printf("Numero de Interacoes: %d\n",k);
    double rowtest = 0;
    for (int i = 0; i<matrizes->J_ORDER; ++i)
    {
        rowtest+= matrizes->ROW_TEST[i]*matrizes->X[i];
    }
    printf("RowTest: %d => [%lf] =? %lf\n", J_ROW_TEST, rowtest ,matrizes->ROW_TEST[matrizes->J_ORDER]);

    printf("tempo de execucao: %lf\n",double(clock() - start)/CLOCKS_PER_SEC);
    
    for(int i = 0; i < matrizes->J_ORDER ; ++i)
    {
        printf("X[%d] = %lf\n", i, matrizes->X[i]);
    }
    /* Encerramento do programa - Liberação de memória */
    for(int i = 0; i<matrizes->J_ORDER; ++i)
    {
        free(matrizes->MA[i]);
    }
    for(int i =0; i< matrizes->n_threads; ++i)
    {
        free(matrizes->interval_thread[i]);
    }
    
    free(matrizes->MA);
    free(matrizes->MB);
    free(matrizes->X);
    free(matrizes->OLD_X);
    free(matrizes->ROW_TEST);
    free(matrizes->interval_thread);
    free(matrizes->array_threads);
    free(matrizes);
    return 0;
}