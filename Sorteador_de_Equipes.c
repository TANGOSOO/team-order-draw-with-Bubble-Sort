#include <stdio.h>                                  /* Bibliotecas usadas */
#include <stdlib.h>
#include <locale.h>
#include <time.h>

int op;                                            /* Variav�is globais */
FILE *his;

void horario(){                                    /* Fun��o para guardar o hor�rio do sorteio */
	time_t agora;        
	time(&agora);                                   /* Recebe o hor�rio no qual o comando foi executado */
	fprintf(his, "Sorteio realizado em: %s", ctime(&agora));      /* Grava no arquivo do hist�rico o hor�rio do sorteio */
}
void sorteiobolha(int n){                          /* Bubble Sort para a ordena��o dos grupos */

	int mat[2][n], i, j, num_sort, cont;      /* Variaveis usadas para realizar o sorteio */
	his=fopen("Hist�rico.txt", "a");               /* Abre o hist�rico em modo escrita para que o sorteio seja salvo */
	
	for(i=0; i<n; i++){
		mat[0][i]=i+1;                             /* Estabelece o a enumera��o do grupo indo de 1 at� n */
		do{
			cont=0;
			num_sort=rand()%1000;                  /* Gera��o de n�meros aleat�rios do programa at� 999 grupos e verifica��o para caso de n�mero repetido */
			for(j=0; j<i; j++){
				if(num_sort==mat[1][j]){
					cont++;
					break;
				}
			}
		}while(cont!=0);                          /* La�o estabelecido para tirar os n�meros sorteados repetidos */
		mat[1][i]=num_sort;
	}
	
/*	printf("Equipes e seus n�meros:\n");
	for(i=0; i<n; i++){
		printf("%d %d\n", mat[0][i], mat[1][i]);
	}*/
	
	for(i=0; i<n-1; i++){                         /* Parte funcinal do programa, troca os valores de acordo com o sorteio, fazendo assim ficarem em ordem crescente */
		for(j=0; j<n-1; j++){
			if(mat[1][j]>mat[1][j+1]){            /* Caso o valor aleat�rio da posi��o seguinte seja menor que a posi��o atual, inverter� suas posi��es */
				mat[1][j]=mat[1][j]+mat[1][j+1];                   /* Salva o n�mero da equipe e o n�mero aleat�rio atrelado a ela e faz com que ela receba o valor da posi��o seguinte e vice-versa */
				mat[1][j+1]=mat[1][j]-mat[1][j+1];
				mat[1][j]=mat[1][j]-mat[1][j+1];
				mat[0][j]=mat[0][j]+mat[0][j+1];                /* Salva o n�mero da equipe e o n�mero aleat�rio atrelado a ela e faz com que ela receba o valor da posi��o seguinte e vice-versa */
				mat[0][j+1]=mat[0][j]-mat[0][j+1];
				mat[0][j]=mat[0][j]-mat[0][j+1];
			}
		}
	}

	printf("Ordem de apresenta��o:\n");           /* Reproduz a ordem de apresenta��o das equipes de acordo com o numero sorteado */
	horario();
	for(i=0; i<n; i++){
		fprintf(his, "%.2d� a apresentar - equipe %d\n", i+1, mat[0][i]);           /* Grava o sorteio no arquivo de texto */
		printf("%.2d� a apresentar - equipe %d\n", i+1, mat[0][i]);
	}
	fprintf(his, "\n");
	fclose(his);                                  /* Fecha o arquivo hist�rico */
	system("pause");
	system("cls");
}
void novamaquina(){                                /* Cria um novo arquivo de texto para o hist�rico em novas m�quinas */
	his=fopen("Hist�rico.txt", "w");
	fclose(his);
}
void historico(){                                  /* Fun��o para ler o hist�rico */
	char c;
	
	his=fopen("Hist�rico.txt", "r");
	system("cls");
	while((c=fgetc(his))!=EOF){                    /* Printa na tela o arquivo hist�rico at� o sorteio mais recente */
		printf("%c", c);
	}
	fclose(his);
	system("pause");
	system("cls");
	return 0;
}
void menu(){
	
	int n;
	
	his=fopen("Hist�rico.txt", "a+");              /* Testa para ver se a m�quina j� tem o arquivo do hist�rico, caso n�o, cria um */
	if(his==NULL){
		novamaquina();
	}
	fclose(his);
	
	do{
		printf("1-Sortear equipes\n2-Hist�rico\n3-Sair\n");        /* Op��es apresentadas no menu */
		scanf("%d", &op);
		if(op!=1 && op!=2 && op!=3){                               /* Garante que o usu�rio apenas escolha as op��es ofertadas */
			do{
				printf("Op��o invalida, tente novamente\n");       /* Mensagem caso a op��o digitada n�o esteja entre as ofertadas */
				scanf("%d", &op);
			}while(op!=1 && op!=2 && op!=3);
		}
		if(op==1){
			printf("Digite o n�mero de equipes a serem sorteadas\n");     /* Pede o n�mero de equipes a serem sorteadas e chama a fun��o do sorteio */
			scanf("%d", &n);
			if(n<=1){
				do{
					printf("N�mero inv�lido de equipes, tente novamente\n");
					scanf("%d", &n);
				}while(n<=1);
			}
			system("cls");
			sorteiobolha(n);
		}
		if(op==2){
			historico();                                           /* Chama a fun��o hist�rico */
		}
	}while(op!=3);
}
int main(){

	setlocale(LC_ALL, "Portuguese");               /* Deixa o progama em portugu�s*/
	srand(time(NULL));                             /* Ferramenta necess�ria para a gera��o de n�meros aleatorios,pois troca a "semente" pro hor�rio que o programa for executado */
	
	printf("*******  *******  *         *        *           *  *  *     *  ******   *******\n");
	printf("*      * *        **       **         *         *   *  **    *  *     *  *     *\n");
	printf("*      * *        * *     * *          *       *    *  * *   *  *     *  *     *\n");
	printf("*******  *******  *  *   *  * ********* *     *     *  *  *  *  *     *  *     *\n");
	printf("*      * *        *   * *   *            *   *      *  *   * *  *     *  *     *\n");
	printf("*      * *        *    *    *             * *       *  *    **  *     *  *     *\n");
	printf("*******  *******  *    *    *              *        *  *     *  ******   *******\n\n");
	printf("\t\tBem-vindo ao sorteador online\n");
	system("pause");

	menu();                                  /* Chama a fun��o do menu */
		
	system("cls");                           /* Limpa a tela */
	printf("\t\t Fim do Progama\n");         /* Mensagem de fechamento do progama */
	system("pause");
	return 0;
}

