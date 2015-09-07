#include "JR.h"

int menuConcorrente(){
	int n_threads;
	do{
		printf("\n\n\n");
		printf("Digite o numero de threads que deseja utilizar no programa: \n");
		printf(" 2 - Cria 2 threads\n");
		printf(" 3 - Cria 3 threads\n");
		printf(" 4 - Cria 4 threads\n");
		printf("> ");
		scanf("%d", &n_threads);
	}while(n_threads < 2 || n_threads > 4);
	return n_threads;
}

int subMenu(){
	int opcao;
	do{
		printf("Submenu:\n");
		printf(" 	1- Matriz 250\n");
		printf(" 	2- Matriz 500\n");
		printf(" 	3- Matriz 1000\n");
		printf(" 	4- Matriz 1500\n");
		printf(" 	5- Matriz 2000\n");
		printf(" 	6- Matriz 3000\n");
		printf(" 	7- Matriz 4000\n");
		printf("> ");
		scanf("%d",&opcao);
	}while(opcao<1 || opcao > 7);

	return opcao;
}
void menu(){
	int opcao;
	int id_matriz;
	int n_threads;
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
				 id_matriz = subMenu();
				sequencial(id_matriz);
				break;
			case 2:
				id_matriz = subMenu();
				n_threads = menuConcorrente();
				concorrente(id_matriz,n_threads);
				break;
			default:
				printf("Opcao invalida, selecione outra opcao.\n");
		}
	}while(opcao !=0);
}

int main(int argc, char const *argv[])
{
	menu();
	return 0;
}