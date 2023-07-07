#include <stdio.h>                                  /* Bibliotecas usadas */
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int op;                                            /* Variavéis globais */
FILE *his;

void horario(){                                    /* Função para guardar o horário do sorteio */
	time_t agora;        
	time(&agora);                                   /* Recebe o horário no qual o comando foi executado */
	fprintf(his, "Sorteio realizado em: %s", ctime(&agora));      /* Grava no arquivo do histórico o horário do sorteio */
}
void sorteiobolha(int n){                          /* Bubble Sort para a ordenação dos grupos */

	int mat[2][n], i, j, num_sort, cont;      /* Variaveis usadas para realizar o sorteio */
	his=fopen("Histórico.txt", "a");               /* Abre o histórico em modo escrita para que o sorteio seja salvo */
	
	for(i=0; i<n; i++){
		mat[0][i]=i+1;                             /* Estabelece o a enumeração do grupo indo de 1 até n */
		do{
			cont=0;
			num_sort=rand()%1000;                  /* Geração de números aleatórios do programa até 999 grupos e verificação para caso de número repetido */
			for(j=0; j<i; j++){
				if(num_sort==mat[1][j]){
					cont++;
					break;
				}
			}
		}while(cont!=0);                          /* Laço estabelecido para tirar os números sorteados repetidos */
		mat[1][i]=num_sort;
	}
	
/*	printf("Equipes e seus números:\n");
	for(i=0; i<n; i++){
		printf("%d %d\n", mat[0][i], mat[1][i]);
	}*/
	
	for(i=0; i<n-1; i++){                         /* Parte funcinal do programa, troca os valores de acordo com o sorteio, fazendo assim ficarem em ordem crescente */
		for(j=0; j<n-1; j++){
			if(mat[1][j]>mat[1][j+1]){            /* Caso o valor aleatório da posição seguinte seja menor que a posição atual, inverterá suas posições */
				mat[1][j]=mat[1][j]+mat[1][j+1];                   /* Salva o número da equipe e o número aleatório atrelado a ela e faz com que ela receba o valor da posição seguinte e vice-versa */
				mat[1][j+1]=mat[1][j]-mat[1][j+1];
				mat[1][j]=mat[1][j]-mat[1][j+1];
				mat[0][j]=mat[0][j]+mat[0][j+1];                /* Salva o número da equipe e o número aleatório atrelado a ela e faz com que ela receba o valor da posição seguinte e vice-versa */
				mat[0][j+1]=mat[0][j]-mat[0][j+1];
				mat[0][j]=mat[0][j]-mat[0][j+1];
			}
		}
	}

	printf("Ordem de apresentação:\n");           /* Reproduz a ordem de apresentação das equipes de acordo com o numero sorteado */
	horario();
	for(i=0; i<n; i++){
		fprintf(his, "%.2dª a apresentar - equipe %d\n", i+1, mat[0][i]);           /* Grava o sorteio no arquivo de texto */
		printf("%.2dª a apresentar - equipe %d\n", i+1, mat[0][i]);
	}
	fprintf(his, "\n");
	fclose(his);                                  /* Fecha o arquivo histórico */
	system("pause");
	system("cls");
}
void novamaquina(){                                /* Cria um novo arquivo de texto para o histórico em novas máquinas */
	his=fopen("Histórico.txt", "w");
	fclose(his);
}
void historico(){                                  /* Função para ler o histórico */
	char c;
	
	his=fopen("Histórico.txt", "r");
	system("cls");
	while((c=fgetc(his))!=EOF){                    /* Printa na tela o arquivo histórico até o sorteio mais recente */
		printf("%c", c);
	}
	fclose(his);
	system("pause");
	system("cls");
}
void menu(){
	
	int n;
	
	his=fopen("Histórico.txt", "a+");              /* Testa para ver se a máquina já tem o arquivo do histórico, caso não, cria um */
	if(his==NULL){
		novamaquina();
	}
	fclose(his);
	
	do{
		printf("1-Sortear equipes\n2-Histórico\n3-Sair\n");        /* Opções apresentadas no menu */
		scanf("%d", &op);
		if(op!=1 && op!=2 && op!=3){                               /* Garante que o usuário apenas escolha as opções ofertadas */
			do{
				printf("Opção invalida, tente novamente\n");       /* Mensagem caso a opção digitada não esteja entre as ofertadas */
				scanf("%d", &op);
			}while(op!=1 && op!=2 && op!=3);
		}
		if(op==1){
			printf("Digite o número de equipes a serem sorteadas\n");     /* Pede o número de equipes a serem sorteadas e chama a função do sorteio */
			scanf("%d", &n);
			if(n<=1){
				do{
					printf("Número inválido de equipes, tente novamente\n");
					scanf("%d", &n);
				}while(n<=1);
			}
			system("cls");
			sorteiobolha(n);
		}
		if(op==2){
			historico();                                           /* Chama a função histórico */
		}
	}while(op!=3);
}
int main(){

	setlocale(LC_ALL, "Portuguese");               /* Deixa o progama em português*/
	srand(time(NULL));                             /* Ferramenta necessária para a geração de números aleatorios,pois troca a "semente" pro horário que o programa for executado */
	
	printf("*******  *******  *         *        *           *  *  *     *  ******   *******\n");
	printf("*      * *        **       **         *         *   *  **    *  *     *  *     *\n");
	printf("*      * *        * *     * *          *       *    *  * *   *  *     *  *     *\n");
	printf("*******  *******  *  *   *  * ********* *     *     *  *  *  *  *     *  *     *\n");
	printf("*      * *        *   * *   *            *   *      *  *   * *  *     *  *     *\n");
	printf("*      * *        *    *    *             * *       *  *    **  *     *  *     *\n");
	printf("*******  *******  *    *    *              *        *  *     *  ******   *******\n\n");
	printf("\t\tBem-vindo ao sorteador online\n");
	system("pause");

	menu();                                  /* Chama a função do menu */
		
	system("cls");                           /* Limpa a tela */
	printf("\t\t Fim do Progama\n");         /* Mensagem de fechamento do progama */
	system("pause");
	return 0;
}

