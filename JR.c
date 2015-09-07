#include  "JR.h"

/*
	Inicializa todas as varizaveis necessarias
*/
MATRIZES * inicializaVariaveis(int id_matriz,int n_threads){
	int i,j;
	FILE *arq_matriz=NULL;

	MATRIZES *matrizes = (MATRIZES *) malloc(sizeof(MATRIZES));

	switch(id_matriz){
		case 1:
			if( (arq_matriz = fopen("matrizes/matriz250.txt","r"))==NULL){
				fprintf(stderr, "Error open file\n");
                return NULL;
			}
			matrizes->number_matriz = 250;
			break;
		case 2:
			if( (arq_matriz = fopen("matrizes/matriz500.txt","r"))==NULL){
				fprintf(stderr, "Error open file\n");
                return NULL;
			}
			matrizes->number_matriz = 500;
			break;
		case 3:
			if( (arq_matriz = fopen("matrizes/matriz1000.txt","r")) ==NULL){
				fprintf(stderr, "Error open file\n");
                return NULL;
			}
			matrizes->number_matriz = 1000;
			break;
		case 4:
			if( (arq_matriz = fopen("matrizes/matriz1500.txt","r"))==NULL){
				fprintf(stderr, "Error open file\n");
                return NULL;
			}
			matrizes->number_matriz = 1500;
			break;
		case 5:
			if( (arq_matriz = fopen("matrizes/matriz2000.txt","r"))==NULL){
				fprintf(stderr, "Error open file\n");
                return NULL;
			}
			matrizes->number_matriz = 2000;
			break;
		case 6:
			if( (arq_matriz = fopen("matrizes/matriz3000.txt","r"))==NULL){
				fprintf(stderr, "Error open file\n");
                return NULL;
			}
			matrizes->number_matriz = 3000;
			break;
		case 7:
			if( (arq_matriz = fopen("matrizes/matriz4000.txt","r"))==NULL){
				fprintf(stderr, "Error open file\n");
                return NULL;
			}
			matrizes->number_matriz = 4000;
			break;
	}


	fscanf (arq_matriz,"%d %d %lf %d", &(matrizes->J_ORDER), &(matrizes->J_ROW_TEST),
							 &(matrizes->J_ERROR), &(matrizes->J_ITE_MAX));

	matrizes->MA = (double **) malloc (sizeof(double *)*matrizes->J_ORDER);
    matrizes->MB = (double *) malloc (sizeof(double )*matrizes->J_ORDER);
    matrizes->X = (double *) malloc (sizeof(double )*matrizes->J_ORDER);
    matrizes->OLD_X = (double *) malloc (sizeof(double )*matrizes->J_ORDER);
    matrizes->ROW_TEST = (double *) malloc (sizeof(double )* (matrizes->J_ORDER+1));
    matrizes->n_threads = n_threads;
    if(n_threads > 0){
    	matrizes->interval_thread = (int **) malloc(sizeof(int *)* matrizes->n_threads);
    	matrizes->array_threads = (pthread_t *) malloc(sizeof(pthread_t)* matrizes->n_threads);

    	for(i = 0; i < matrizes->n_threads; ++i)
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
	        //printf("thread[%d]: %d - %d\n",i,matrizes->interval_thread[i][0],matrizes->interval_thread[i][1]);
	    }
    }

    /* Alocação da matrizes A*/
    for(i = 0; i<matrizes->J_ORDER; ++i)
    {
        matrizes->MA[i] = (double *) malloc (sizeof(double)*matrizes->J_ORDER);
    }

    for(i = 0; i< matrizes->J_ORDER; ++i)
    {
        for (j = 0; j<matrizes->J_ORDER ; ++j)
        {
            fscanf (arq_matriz,"%lf", &(matrizes->MA[i][j]) );
        }
    }

    /* Leitura dos valores de B*/
    for(i = 0; i<matrizes->J_ORDER; ++i)
    {
        fscanf (arq_matriz,"%lf", &(matrizes->MB[i]) );
    }
    fclose(arq_matriz);

    return matrizes;
}


double erro (MATRIZES *matrizes, int init_interaction)
{
    double ERRO = 0;
    double diferenca;
    double divisor = 0;
    double X_aux;
    int i;
    for ( i = 0 ; i < matrizes->J_ORDER; ++i)
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


void inicializaMetodo(MATRIZES *matrizes){
	int i,j;	
    matrizes->ROW_TEST[matrizes->J_ORDER]=matrizes->MB[matrizes->J_ROW_TEST];
    for(i = 0; i<matrizes->J_ORDER; ++i)
        matrizes->ROW_TEST[i] = matrizes->MA[matrizes->J_ROW_TEST][i]; /*salva a linha de teste*/
    
    /* Encontra as matrizes L*, I, R* de dentro da matrix MA */
    for(i = 0; i< matrizes->J_ORDER; ++i)
    {
        for (j = 0; j<matrizes->J_ORDER ; ++j)
        {
            if(i!=j) matrizes->MA[i][j]/= matrizes->MA[i][i];
        }
        matrizes->MB[i]/= matrizes->MA[i][i]; /* X é inicializado com o valor de MB* */
        matrizes->MA[i][i] = 0; /*zera a diagonal principal */
        matrizes->X[i] = matrizes->MB[i];
    }
}

double rowTest(MATRIZES *matrizes){
	double rowtest = 0;
	int i;
    for (i = 0; i<matrizes->J_ORDER; ++i)
    {
        rowtest+= matrizes->ROW_TEST[i]*matrizes->X[i];
    }
    
    return rowtest;
}

void writeEndX(MATRIZES *matrizes,FILE *arq_save){
	int i;
	for(i = 0; i < matrizes->J_ORDER ; ++i)
    {
        fprintf(arq_save,"X[%d] = %lf\n", i, matrizes->X[i]);
    }
}

int inicioInteracaoSequencial(MATRIZES *matrizes,FILE *arq_save){
	double ERRO = erro(matrizes,0);
    int k,i,j;

    for ( k = 0; ERRO > matrizes->J_ERROR && k < matrizes->J_ITE_MAX ; ++k)
    {
    	for(i = 0 ; i < matrizes->J_ORDER; ++i)
        {
            matrizes->OLD_X[i] = matrizes->X[i];
        }

        for(i = 0; i < matrizes->J_ORDER; ++i)
		{
			matrizes->X[i] = matrizes->MB[i];
			for(j=0; j<matrizes->J_ORDER; ++j)
			{
				matrizes->X[i]-=(matrizes->OLD_X[j]*matrizes->MA[i][j]);
			}
		}
		ERRO = erro(matrizes,1);
		fprintf(arq_save,"%d\t\t%lf\n", k, ERRO);
	}
	return k;
}

void *interacaoConcorrente(void *args){

    MATRIZES *matrizes = (MATRIZES *) args;

    pthread_t self = pthread_self();
    int j,k,l=0;

    /*Descubro qual a thread que estou*/
    for(l=0; l < matrizes->n_threads; ++l)
    {
        if(matrizes->array_threads[l]==self)
            break;
    }
    for(j=matrizes->interval_thread[l][0]; j <= matrizes->interval_thread[l][1]; ++j)
    {
        matrizes->X[j] = matrizes->MB[j];
        for(k=0; k < matrizes->J_ORDER; ++k)
        {
            matrizes->X[j] -= (matrizes->OLD_X[k] * matrizes->MA[j][k]);
        }
    }

    return NULL;

}

int inicioInteracaoConcorrente(MATRIZES *matrizes,FILE *arq_save){
	double ERRO = erro(matrizes,0);
    int k,i;
	/* Iterações até atingir o critério de parada */
    for ( k = 0; ERRO > matrizes->J_ERROR && k < matrizes->J_ITE_MAX ; ++k)
    {
		for( i = 0 ; i < matrizes->J_ORDER; ++i)
        {
           matrizes->OLD_X[i] = matrizes->X[i];
        }
        for(i=0 ; i < matrizes->n_threads ; ++i){
            if(pthread_create(&(matrizes->array_threads[i]), NULL, interacaoConcorrente, (void*)matrizes)) {
                fprintf(stderr, "Error creating thread\n");
                return 1;
            }       
        }
        for(i = 0; i < matrizes->n_threads ; ++i)
        {
            pthread_join(matrizes->array_threads[i],NULL);
        } 
        
        ERRO = erro(matrizes, 1);

        fprintf(arq_save,"%d\t\t%lf\n", k, ERRO);
    }	
    return k;
}


void sequencial(int id_matriz){
	struct timeval start,end;
	int i=0;
	//MATRIZES *matrizes = inicializaVariaveis(id_matriz,0);
	MATRIZES *matrizes = NULL;
	char name_arq[37];
	double tempo = 0;
	double tempo_aux=0;
	int n_interacoes=-1;
	double rowtest =0.0;
	for(i = 0 ; i < 10 ; ++i){
		 matrizes = inicializaVariaveis(id_matriz,0);
		sprintf(name_arq,"out/%d/seq/%d_seqOp%d.txt",matrizes->number_matriz,
						matrizes->number_matriz,i);

		FILE *arq_save = fopen(name_arq,"w");

		gettimeofday(&start,NULL);
		inicializaMetodo(matrizes);
		n_interacoes = inicioInteracaoSequencial(matrizes,arq_save);

	    rowtest = rowTest(matrizes);

	    printf("%d %lf\n", n_interacoes,rowtest);

		gettimeofday(&end,NULL);
		tempo_aux =( ((double) ( ((end.tv_sec * 1000000 + end.tv_usec)
		  						- (start.tv_sec * 1000000 + start.tv_usec))))/1000000);
		tempo +=tempo_aux;
		writeEndX(matrizes,arq_save);
		fprintf(arq_save, "Numero de Interacoes: %d\n",n_interacoes );
		fprintf(arq_save, "RowTest: %d => [%lf] =? %lf\n", matrizes->J_ROW_TEST, rowtest ,
													matrizes->ROW_TEST[matrizes->J_ORDER]);
		fprintf(arq_save, "Tempo de Execucao: %lf\n",tempo_aux );
		fclose(arq_save);
		if(i != 9)
			freeAll(&matrizes);
	}
	printf("---------------------------------------------------------\n");
	printf("Iterations: %d\n", n_interacoes);
	printf("RowTest: %d => [%lf] =? %lf\n", matrizes->J_ROW_TEST, rowtest ,
													matrizes->ROW_TEST[matrizes->J_ORDER]);
	printf("Tempo medio: %lf",tempo/10);
	printf("-------------------------------------------------------\n");
	freeAll(&matrizes);
}

void concorrente(int id_matriz,int n_threads){
	struct timeval start,end;
	MATRIZES *matrizes = NULL;
	int i;
	char name_arq[37];
	double tempo = 0;
	double tempo_aux=0;
	int n_interacoes;
	double rowtest =0.0;
	for(i = 0 ; i < 10 ; ++i){
		matrizes = inicializaVariaveis(id_matriz,n_threads);
		sprintf(name_arq,"out/%d/conc%d/%d_conc%dOp%d.txt",matrizes->number_matriz,
						matrizes->n_threads,matrizes->number_matriz,matrizes->n_threads,i);
		FILE *arq_save = fopen(name_arq,"w");

		gettimeofday(&start,NULL);
		inicializaMetodo(matrizes);
		n_interacoes = inicioInteracaoConcorrente(matrizes,arq_save);
		rowtest = rowTest(matrizes);
		gettimeofday(&end,NULL);
		tempo_aux =( ((double) ( ((end.tv_sec * 1000000 + end.tv_usec)
		  						- (start.tv_sec * 1000000 + start.tv_usec))))/1000000);
		tempo +=tempo_aux;
		writeEndX(matrizes,arq_save);
		fprintf(arq_save, "Numero de Interacoes: %d\n", n_interacoes );
		fprintf(arq_save, "RowTest: %d => [%lf] =? %lf\n", matrizes->J_ROW_TEST, rowtest ,
													matrizes->ROW_TEST[matrizes->J_ORDER]);
		fprintf(arq_save, "Tempo de Execucao: %lf\n",tempo_aux );
		fclose(arq_save);
		if(i !=9)
			freeAll(&matrizes);
	}
	printf("---------------------------------------------------------\n");
	printf("Iterations: %d\n",n_interacoes );
	printf("RowTest: %d => [%lf] =? %lf\n", matrizes->J_ROW_TEST, rowtest ,
													matrizes->ROW_TEST[matrizes->J_ORDER]);
	printf("Tempo medio: %lf\n",tempo/10);
	printf("-------------------------------------------------------\n\n");
	freeAll(&matrizes);
}

void freeAll(MATRIZES **matrizes){
	int i;
	for(i = 0; i< (*matrizes)->J_ORDER; ++i)
    {
        free((*matrizes)->MA[i]);
    }
    for(i =0; i< (*matrizes)->n_threads; ++i)
    {
        free( (*matrizes)->interval_thread[i]);
    }
    
    free((*matrizes)->MA);
    free((*matrizes)->MB);
    free((*matrizes)->X);
    free((*matrizes)->OLD_X);
    free((*matrizes)->ROW_TEST);
    if((*matrizes)->n_threads > 0 ){
    	free((*matrizes)->interval_thread);
	    free((*matrizes)->array_threads);
	}
    free(*matrizes);
}