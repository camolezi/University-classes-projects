#include <stdio.h>
#include <unistd.h>
//Projeto final, monitoria.

#define tamanhoTabuleiro 10
#define JogadorUm 0
#define JogadorDois 1



void iniciarTabuleiro(char * tabuleiro);
void printTabuleiro(char * tabuleiro);
void moverPedra(int pos, char * tabuleiro);
int fazerJogada(int pos,int jogador, char * tabuleiro);
int verificarJogada(int pos,int jogador, char * tabuleiro);

int arvorePossibilidades2(char * tabuleiroAtual, int player);
int arvorePossibilidades(char * tabuleiroAtual, int player);
int moduloIA(char * tabuleiro, int player);

//Variavel global da versão inicial
int melhorJogada = 100;
int playerIA = JogadorDois;


int main(){
	
	int jogador;
	char tabuleiro[tamanhoTabuleiro];
	
	iniciarTabuleiro(tabuleiro);
	printTabuleiro(tabuleiro);
	
	jogador = JogadorUm;
	int pos;
	while(1){
		if(jogador == JogadorUm){	
			if(verificarFim(tabuleiro,jogador) == 1){
				printf("\nJogador dois venceu");
				return 0;
			}
			
		///	moduloIA(tabuleiro, JogadorUm);
			
			do{
				printf("\nJogador um realize sua jogada \n");	
				scanf("%d",&pos);	
			}while(fazerJogada(pos, JogadorUm, tabuleiro) == 0);
		
		//	if(fazerJogada(melhorJogada, JogadorUm, tabuleiro) == 0){
		//		printf("\nFalha na IA");
		//	}
			
			jogador = JogadorDois;
			
		}else{
			
			if(verificarFim(tabuleiro,jogador) == 1){
				printf("\nJogador um venceu");
				return 0;
			}
			moduloIA(tabuleiro, JogadorDois);
			//do{
			//	printf("\nJogador dois realize sua jogada \n");	
			//	scanf("%d",&pos);	
			//}while(fazerJogada(pos, JogadorDois, tabuleiro) == 0);
				if(fazerJogada(melhorJogada, JogadorDois, tabuleiro) == 0){
				printf("\nFalha na IA");
			}
			
			jogador = JogadorUm;
		}
	}	
	
	return 0;	
}

//BOT PLAYER 2
/*
int main(){
	
	int jogador;
	char tabuleiro[tamanhoTabuleiro];
	
	iniciarTabuleiro(tabuleiro);
	printTabuleiro(tabuleiro);
	
	jogador = JogadorUm;
	int pos;
	while(1){
		if(jogador == JogadorUm){	
			if(verificarFim(tabuleiro,jogador) == 1){
				printf("\nJogador dois venceu");
				return 0;
			}
			
			do{
				printf("\nJogador um realize sua jogada \n");	
				scanf("%d",&pos);	
			}while(fazerJogada(pos, JogadorUm, tabuleiro) == 0);
			
			jogador = JogadorDois;
			
		}else{
			
			if(verificarFim(tabuleiro,jogador) == 1){
				printf("\nJogador um venceu");
				return 0;
			}
			
			moduloIA(tabuleiro,JogadorDois);
			
		//	do{
				//printf("\nJogador dois realize sua jogada \n");	
				//scanf("%d",&pos);	
		//	}while(fazerJogada(melhorJogada, JogadorDois, tabuleiro) == 0);
			
			if(fazerJogada(melhorJogada, JogadorDois, tabuleiro) == 0){
				printf("\nFalha na IA");
			}
			jogador = JogadorUm;
		}
	}	
	
	return 0;	
}
*/
int fazerJogada(int pos,int jogador, char * tabuleiro){
	if(verificarJogada(pos,jogador,tabuleiro) == 1){
		moverPedra(pos,tabuleiro);
		printTabuleiro(tabuleiro);
		return 1;
	}else{
		return 0;
	}
}

//Retorna 1 se for o fim do jogo na vez do jogador
int verificarFim(char * tabuleiro, int jogador){
	int x;
	int contador = 0;
	
	for(x = 0; x < tamanhoTabuleiro; x++){
		contador = contador + verificarJogada(x,jogador,tabuleiro);
	}
	if(contador == 0){
		return 1;
	}else{
		return 0;
	}
}

int verificarJogada(int pos,int jogador, char * tabuleiro){
	if(jogador == JogadorUm){
		if(tabuleiro[pos] == 'X'){
			if(pos < tamanhoTabuleiro-2 && tabuleiro[pos+1] == 'O'){
				if(tabuleiro[pos+2] == '.'){	
					return 1;
				}
			}else if(pos < tamanhoTabuleiro-1 && tabuleiro[pos+1] == '.'){
				return 1;
			}
		}	
	}else if(jogador == JogadorDois){
		if(tabuleiro[pos] == 'O'){
			if(pos > 1 && tabuleiro[pos-1] == 'X'){
				if(tabuleiro[pos-2] == '.'){
					return 1;	
				}
			}else if(pos > 0 && tabuleiro[pos-1] == '.'){
				return 1;
			}
		}
	}else{
		printf("\n Jogador invalido");
	}
//	printf("\n Jogada invalida");
	return 0;
}

//Função para mover a pedra depois de descobrir se a jogada é valida
void moverPedra(int pos, char * tabuleiro){
	
	if(tabuleiro[pos] == 'X'){
		if(tabuleiro[pos+1] == '.'){
			tabuleiro[pos+1] = 'X';	
		}else if(tabuleiro[pos+1] == 'O'){
			tabuleiro[pos+2] = 'X';
		}
	}else if(tabuleiro[pos] == 'O'){
		if(tabuleiro[pos-1] == '.'){
			tabuleiro[pos-1] = 'O';	
		}else if(tabuleiro[pos-1] == 'X'){
			tabuleiro[pos-2] = 'O';
		}
	}
	tabuleiro[pos] = '.';
	return;
}

//Configura o tabuleiro, colocando as peças no lugar inicial
void iniciarTabuleiro(char * tabuleiro){
	int x;
	for(x = 0; x < 4; x++){
		tabuleiro[x] = 'X';
	}
	
	for(x = 4; x < 6; x++){
		tabuleiro[x] = '.';
	}
	
	for(x = 6; x < tamanhoTabuleiro; x++){
		tabuleiro[x] = 'O';
	}
	
}

//Printa o tabuleiro
void printTabuleiro(char * tabuleiro){
	
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	int x;
	printf("\n");
	for (x = 0; x < tamanhoTabuleiro; x++){
		printf("%c  ", tabuleiro[x]);	
	}
		printf("\n");
	for (x = 0; x < tamanhoTabuleiro; x++){
		printf("%d  ", x);	
	}
	printf("\n");
	sleep(2);
}


int moduloIA(char * tabuleiro, int player){
	//Fazer uma arvore de possibilidades 
	arvorePossibilidades2(tabuleiro, player);
//	printf("\nJogada da IA : %d \n \n" ,melhorJogada);
	return 0;
}




int menorFilho(int * filhos){
	int x;
	int menor = 30000;
	
	for(x = 0; x < 10;x++){
	//	printf("\n %d",filhos[x]);
	}

	melhorJogada = -1;
	for(x = 0; x < 10;x++){
		if(filhos[x] < menor && filhos[x] != -1){
			menor = filhos[x];
			melhorJogada = x;
		}
	}
//	printf("\n %d", menor);
	return menor;
}

void copiarTabuleiro(char * newTabuleiro, char * tabuleiroAtual){
	int x;
	for(x= 0; x < tamanhoTabuleiro; x++){
		newTabuleiro[x] = tabuleiroAtual[x];
	}
	return;
}

char * moverTabuleiro(int pos, char * tabuleiroAtual){
	char * newTabuleiro = (char *) malloc(sizeof(char) * tamanhoTabuleiro);
	copiarTabuleiro(newTabuleiro,tabuleiroAtual);
	moverPedra(pos,newTabuleiro);
	return newTabuleiro;
}

int arvorePossibilidades(char * tabuleiroAtual, int player){
	//printf("entrou");
	//Condição de parada
	if(verificarFim(tabuleiroAtual, player) == 1){
	//	printf("AHHAHAHAHAHAHHA");
		if(player == playerIA){
			//IA perdeu 
			return 10000;
		}else{
			return 1;
		}
	}
	
	int x;
	char simb;
	int valoresFilhos[10];
	
	for(x = 0; x < tamanhoTabuleiro; x++){
		valoresFilhos[x] = -1;	
	}
	
	if(player == JogadorUm){
		simb = 'X';
	}
	if(player == JogadorDois){
		simb = 'O';
	}
	
	for(x = 0; x < tamanhoTabuleiro; x++){
		if(tabuleiroAtual[x] == simb){
			if(verificarJogada(x,player,tabuleiroAtual) == 1){
			//	printf("entrou2 %d",x);
				char * newTabuleiro = moverTabuleiro(x,tabuleiroAtual);	
				valoresFilhos[x] = arvorePossibilidades(newTabuleiro,!player); 	
				free(newTabuleiro);
			}
		}	
	}
	
//	printf("entrou3");
//	printf("\n " ,menorFilho(valoresFilhos));
	//Pega o caminho mais rapido para a vitoria
	//Precisa repensar essa estrategia.
	return menorFilho(valoresFilhos) + 1;
}




int somaFilhos(int * filhos){
	int x;
	int soma = 0;
	
	for(x = 0; x < 10;x++){
	//	printf("\n %d",filhos[x]);
	}

	
	for(x = 0; x < 10;x++){
		if(filhos[x] != -1){
			soma = filhos[x] + soma;
		}
	}
	int maior = -10000;
	melhorJogada = -1;
	for(x = 0; x < 10;x++){
		if(filhos[x] > maior && filhos[x] != -1){
			maior = filhos[x];
			melhorJogada = x;
		}
	}
	
	//printf("\n %d", menor);
	return soma;
}

int arvorePossibilidades2(char * tabuleiroAtual, int player){
	//printf("entrou");
	//Condição de parada
	if(verificarFim(tabuleiroAtual, player) == 1){
	//	printf("AHHAHAHAHAHAHHA");
		if(player == playerIA){
			//IA perdeu 
			return -2;
		}else{
			//Contabiliza uma vitoria
			return 2;
		}
	}
	
	int x;
	char simb;
	int valoresFilhos[10];
	
	for(x = 0; x < tamanhoTabuleiro; x++){
		valoresFilhos[x] = -1;	
	}
	
	if(player == JogadorUm){
		simb = 'X';
	}
	if(player == JogadorDois){
		simb = 'O';
	}
	
	for(x = 0; x < tamanhoTabuleiro; x++){
		if(tabuleiroAtual[x] == simb){
			if(verificarJogada(x,player,tabuleiroAtual) == 1){
			//	printf("entrou2 %d",x);
				char * newTabuleiro = moverTabuleiro(x,tabuleiroAtual);	
				valoresFilhos[x] = arvorePossibilidades2(newTabuleiro,!player); 	
				free(newTabuleiro);
			}
		}	
	}
	
//	printf("entrou3");
//	printf("\n " ,menorFilho(valoresFilhos));
	//Pega o caminho mais rapido para a vitoria
	//Precisa repensar essa estrategia.
	return somaFilhos(valoresFilhos);
}




