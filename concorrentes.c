#include <stdio.h>
#include <stdlib.h>
#include <JR.h>

int menuConcorrente(){
	int n_threads;
	printf("\n\n\n");
	printf("Digite o numero de threads que deseja utilizar no programa: ");
	scanf("%d",n_threads);
	return n_threads;
}

void menu(){
	int opcao;
	printf("V1.0-----Concorrentes-----\n");
	printf("Eduardo Brunaldi dos Santos & Igor de Souza Baliza\n");	
	printf("\n\n\n");
	do{
		printf("Menu Principal:\n");
		printf("	1- Executar sequencial\n");
		printf("	2- Executar concorrente\n");
		printf("	0- Sair\n");
		printf("Digite uma das opcoes: ");
		scanf("%d",&opcao);

		switch (opcao){
			case 0:
				printf("Fechando  o programa!\n");
				break;
			case 1:
				sequencial();
				break;
			case 2:
				int n_threads = menuConcorrente();
				concorrente(n_threads);
				break;
			default:
				printf("Opcao invalida, selecione outra opcao.\n");
		}
	}while(opcao !=0);
}

void sequencial(){
	incializa_variaveis();
}

void concorrente(){
	incializa_variaveis();
}

int int main(int argc, char const *argv[])
{
	menu();
	return 0;
}