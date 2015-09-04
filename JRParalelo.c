#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
MA       = 
MB       = 
X        =
OLD_X    =
ROW_TEST = 
*/
typedef struct matrizes
{
    double **MA;
    double *MB;
    double *X;
    double *OLD_X; 
    double *ROW_TEST;
}MATRIZES;

//double erro (double *X, double *OLD_X, int J_ORDER)
double erro (MATRIZES *matrizes, int init_interaction)
{
    double ERRO = 0;
    double diferenca;
    double divisor = 0;
    double X_aux;
    for (int i = 0 ; i < J_ORDER; ++i)
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


int main ()
{
    clock_t end, start;
    int J_ORDER, J_ROW_TEST, J_ITE_MAX;
    double J_ERROR;
    //double **MA, *MB, *X, *OLD_X, *ROW_TEST; 
    MATRIZES *matrizes=NULL;
    /* Inicio do programa - leitura dos valores iniciais */
    start = clock();
    matrizes = (MATRIZES *) malloc(sizeof(MATRIZES));
    scanf ("%d %d %lf %d", &J_ORDER, &J_ROW_TEST, &J_ERROR, &J_ITE_MAX);
    matrizes->MA = (double **) malloc (sizeof(double *)*J_ORDER);
    matrizes->MB = (double *) malloc (sizeof(double )*J_ORDER);
    matrizes->X = (double *) malloc (sizeof(double )*J_ORDER);
    matrizes->OLD_X = (double *) malloc (sizeof(double )*J_ORDER);
    matrizes->ROW_TEST = (double *) malloc (sizeof(double )* (J_ORDER+1));
    
    /* Alocação da matrizes A*/
    for(int i = 0; i<J_ORDER; ++i)
    {
        matrizes->MA[i] = (double *) malloc (sizeof(double)*J_ORDER);
    }
    
    /* Leitura dos valores de A*/
    for(int i = 0; i< J_ORDER; ++i)
    {
        for (int j = 0; j<J_ORDER ; ++j)
        {
            scanf ("%lf", &(matrizes->MA[i][j]) );
        }
    }
    
    /* Leitura dos valores de B*/
    for(int i = 0; i<J_ORDER; ++i)
    {
        scanf ("%lf", &(matrizes->MB[i]) );
    }
    printf("tempo de leitura: %lf\n",double(clock() - start)/CLOCKS_PER_SEC);
    start = clock();

    matrizes->ROW_TEST[J_ORDER]=matrizes->MB[J_ROW_TEST];
    for(int i = 0; i<J_ORDER; ++i)
        matrizes->ROW_TEST[i] = matrizes->MA[J_ROW_TEST][i]; /*salva a linha de teste*/
    
    /* Encontra as matrizes L*, I, R* de dentro da matrix MA */
    for(int i = 0; i< J_ORDER; ++i)
    {
        for (int j = 0; j<J_ORDER ; ++j)
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
        for(int i = 0; i < J_ORDER; ++i)
        {
            matrizes->OLD_X[i] = matrizes->X[i];
            matrizes->X[i] = matrizes->MB[i];
            for(int j=0; j<J_ORDER; ++j)
            {
                matrizes->X[i]-=(matrizes->X[j]* matrizes->MA[i][j]);
            }
        }
        //ERRO = erro(X,OLD_X, J_ORDER);
        ERRO = erro(matrizes, 1);
        printf("%d\t\t%lf\n", k, ERRO);
    }
    
    printf("Numero de Interacoes: %d\n",k);
    double rowtest = 0;
    for (int i = 0; i<J_ORDER; ++i)
    {
        rowtest+= matrizes->ROW_TEST[i]*matrizes->X[i];
    }
    printf("RowTest: %d => [%lf] =? %lf\n", J_ROW_TEST, rowtest ,matrizes->ROW_TEST[J_ORDER]);

    printf("tempo de execucao: %lf\n",double(clock() - start)/CLOCKS_PER_SEC);
    
    for(int i = 0; i < J_ORDER ; ++i)
    {
        printf("X[%d] = %lf\n", i, matrizes->X[i]);
    }
    /* Encerramento do programa - Liberação de memória */
    for(int i = 0; i<J_ORDER; ++i)
    {
        free(matrizes->MA[i]);
    }
    
    free(matrizes->MA);
    free(matrizes->MB);
    free(matrizes->X);
    free(matrizes->OLD_X);
    free(matrizes->ROW_TEST);
    free(matrizes);
    return 0;
}