#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float erro (float *X, float *OLD_X, int J_ORDER)
{
	float ERRO = 0;
	float diferenca;
	for (int i = 0 ; i < J_ORDER; ++i)
	{
		diferenca = (OLD_X)? X[i] - OLD_X[i] : X[i];
		if(diferenca < 0) diferenca = -diferenca;
		if(diferenca > ERRO) ERRO = diferenca;
	}
	return ERRO;
}


int main ()
{
	clock_t end, start;
	int J_ORDER, J_ROW_TEST, J_ITE_MAX;
	float J_ERROR;
	float **MA, **MLR, *MB, *X, *OLD_X;
	
	/* Inicio do programa - leitura dos valores iniciais */
	start = clock();
	scanf ("%d %d %f %d", &J_ORDER, &J_ROW_TEST, &J_ERROR, &J_ITE_MAX);
	MA = (float **) malloc (sizeof(float *)*J_ORDER);
	MLR = (float **) malloc (sizeof(float *)*J_ORDER);
	MB = (float *) malloc (sizeof(float )*J_ORDER);
	X = (float *) malloc (sizeof(float )*J_ORDER);
	OLD_X = (float *) malloc (sizeof(float )*J_ORDER);
	
	/* Alocação da matrizes A*/
	for(int i = 0; i<J_ORDER; ++i)
	{
		MA[i] = (float *) malloc (sizeof(float)*J_ORDER);
		MLR[i] = (float *) malloc (sizeof(float)*J_ORDER);
	}
	
	/* Leitura dos valores de A*/
	for(int i = 0; i< J_ORDER; ++i)
	{
		for (int j = 0; j<J_ORDER ; ++j)
		{
			scanf ("%f", &MA[i][j]);
		}
	}
	
	/* Leitura dos valores de B*/
	for(int i = 0; i<J_ORDER; ++i)
	{
		scanf ("%f", &MB[i]);
	}
	printf("tempo de leitura: %lf\n",double(clock() - start)/CLOCKS_PER_SEC);
	start = clock();
	/* Encontra as matrizes L*, I, R* de dentro da matrix MA */
	for(int i = 0; i< J_ORDER; ++i)
	{
		for (int j = 0; j<J_ORDER ; ++j)
		{
			if(i!=j) MLR[i][j]=MA[i][j]/MA[i][i];
		}
		X[i]=MB[i]/MA[i][i]; /* X é inicializado com o valor de MB* */
		MLR[i][i] = 0; /*zera a diagonal principal */
	}
	
	/* Processo iterativo do método Jacobi-Richardson
	
	Iteração inicial  */
	printf("Iteracao\t\tErro\n");
	float ERRO = erro(X,NULL, J_ORDER);
	printf("0\t%f\n", ERRO);
	int k;
	for ( k = 1; k < J_ITE_MAX && ERRO > J_ERROR; ++k)
	{
		printf("%d\t%f\n", k, ERRO);
		// for(int i =0; i<J_ORDER; ++i)
		// {
			 //printf("%f ",X[i]);
		// }
		// printf("\n");
		for(int i = 0; i < J_ORDER; ++i)
		{
			OLD_X[i] = X[i];
			X[i] = MB[i]/MA[i][i];
			for(int j=0; j<J_ORDER; ++j)
			{
				X[i]-=(X[j]*MLR[i][j]);
			}
		}
		ERRO = erro(X,OLD_X, J_ORDER);
	}
	for(int i =0; i<J_ORDER; ++i)
		{
			//printf("%f ",X[i]);
		}

	printf("Numero de Interacoes: %d\n",k);
	float rowtest = 0;
	for (int i = 0; i<J_ORDER; ++i)
	{
		rowtest+= MA[J_ROW_TEST][i]*X[i];
	}
	printf("RowTest: %d => [%f] =? %f\n", J_ROW_TEST, rowtest ,MB[J_ROW_TEST]);

	printf("tempo de execucao: %lf\n",double(clock() - start)/CLOCKS_PER_SEC);

	/* Encerramento do programa - Liberação de memória */
	for(int i = 0; i<J_ORDER; ++i)
	{
		free(MA[i]);
	}
	free(MA);
	free(MB);
	free(X);
	free(OLD_X);

  
	return 0;
}