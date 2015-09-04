#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct matrizes
{
    double **MA;
    double *MB;
    double *X;
    double *OLD_X; 
    double *ROW_TEST;
}MATRIZES;

double erro (double *X, double *OLD_X, int J_ORDER)
{
    double ERRO = 0;
    double diferenca;
    double divisor = 0;
    double X_aux;
    for (int i = 0 ; i < J_ORDER; ++i)
    {
        /* Calcula modulo infinito de Xk - Xk-1 */
        diferenca = (OLD_X)? X[i] - OLD_X[i] : X[i];
        if(diferenca < 0.0) diferenca = -diferenca;
        if(diferenca > ERRO) ERRO = diferenca;
        /* Calcula o erro infinito de Xk */
        X_aux = X[i];
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
    double **MA, *MB, *X, *OLD_X, *ROW_TEST;
    
    /* Inicio do programa - leitura dos valores iniciais */
    start = clock();
    scanf ("%d %d %lf %d", &J_ORDER, &J_ROW_TEST, &J_ERROR, &J_ITE_MAX);
    MA = (double **) malloc (sizeof(double *)*J_ORDER);
    MB = (double *) malloc (sizeof(double )*J_ORDER);
    X = (double *) malloc (sizeof(double )*J_ORDER);
    OLD_X = (double *) malloc (sizeof(double )*J_ORDER);
    ROW_TEST = (double *) malloc (sizeof(double )* (J_ORDER+1));
    
    /* Alocação da matrizes A*/
    for(int i = 0; i<J_ORDER; ++i)
    {
        MA[i] = (double *) malloc (sizeof(double)*J_ORDER);
    }
    
    /* Leitura dos valores de A*/
    for(int i = 0; i< J_ORDER; ++i)
    {
        for (int j = 0; j<J_ORDER ; ++j)
        {
            scanf ("%lf", &MA[i][j]);
        }
    }
    
    /* Leitura dos valores de B*/
    for(int i = 0; i<J_ORDER; ++i)
    {
        scanf ("%lf", &MB[i]);
    }
    printf("tempo de leitura: %lf\n",double(clock() - start)/CLOCKS_PER_SEC);
    start = clock();

    ROW_TEST[J_ORDER]=MB[J_ROW_TEST];
    for(int i = 0; i<J_ORDER; ++i)
        ROW_TEST[i] = MA[J_ROW_TEST][i]; /*salva a linha de teste*/
    
    /* Encontra as matrizes L*, I, R* de dentro da matrix MA */
    for(int i = 0; i< J_ORDER; ++i)
    {
        for (int j = 0; j<J_ORDER ; ++j)
        {
            if(i!=j) MA[i][j]/=MA[i][i];
        }
        MB[i]/=MA[i][i]; /* X é inicializado com o valor de MB* */
        MA[i][i] = 0; /*zera a diagonal principal */
        X[i] = MB[i];
    }
    
    /* Processo iterativo do método Jacobi-Richardson
    
    Iteração inicial  */
    printf("Iteracao\tErro < %lf\n", J_ERROR);
    double ERRO = erro(X,NULL, J_ORDER);
    int k;
    /* Iterações até atingir o critério de parada */
    for ( k = 0; ERRO > J_ERROR && k < J_ITE_MAX ; ++k)
    {
        for(int i = 0; i < J_ORDER; ++i)
        {
            OLD_X[i] = X[i];
            X[i] = MB[i];
            for(int j=0; j<J_ORDER; ++j)
            {
                X[i]-=(X[j]*MA[i][j]);
            }
        }
        ERRO = erro(X,OLD_X, J_ORDER);
        printf("%d\t\t%lf\n", k, ERRO);
    }
    
    printf("Numero de Interacoes: %d\n",k);
    double rowtest = 0;
    for (int i = 0; i<J_ORDER; ++i)
    {
        rowtest+= ROW_TEST[i]*X[i];
    }
    printf("RowTest: %d => [%lf] =? %lf\n", J_ROW_TEST, rowtest ,ROW_TEST[J_ORDER]);

    printf("tempo de execucao: %lf\n",double(clock() - start)/CLOCKS_PER_SEC);
    
    for(int i = 0; i < J_ORDER ; ++i)
    {
        printf("X[%d] = %lf\n", i, X[i]);
    }
    /* Encerramento do programa - Liberação de memória */
    for(int i = 0; i<J_ORDER; ++i)
    {
        free(MA[i]);
    }
    
    free(MA);
    free(MB);
    free(X);
    free(OLD_X);
    free(ROW_TEST);
    return 0;
}