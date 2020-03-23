#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <string>
#include <time.h>

//Usaremos uma biblioteca do windowns para medir o tempo precisamente
#include <windows.h>


using namespace std;

//Estrutura de dados para armazenar os dados do treino
//Composta por uma matriz com os dados, e com o númeo de linhas da matriz = número de linhas do arquivo

typedef struct matrizes{
	
	float ** matriz;
	int numeroDeLinhas;
	
}MatrizDados;


//Para saber o número de elementos de uma série, eu armazenei ele no PRIMEIRO VALOR da "matrizTreino" para cada linha.
// Exemplo, se variavel matrizTreino[2][0]  for igual a 10, quer dizer que o vetor da linha 2 tem 10 elementos, ou
// que a serie da linha 2 apresenta 9 elementos.
// Rodar o programa para entender o que eu escreve acima, percebe que o primeiro valor de cada linha é o número de elementos daquela linha.
// A main esta rodando o txt ola.txt que é um teste , pode editar ele


// Funçõs -Header
void KselectionSort(const int k, float vetor[], int tam , int vetorAuxiliar[],MatrizDados * Dados);
MatrizDados *  ColetarDadosTreino(char nomeArquivo[]);
float distanciaEuclidiana(float a, float b);
float DTW(float serie1[],float serie2[]);
float Minimo(float a,float b, float c);
int KNN (const int k, float serieTemporal[], MatrizDados * DadosTreino);

//Classificação dos movimentos 
/*
1 direita
2 esquerda
3 quadrado
4 tenis
5 Z
6 baixo
7 cima
8 circulo
9 diagonalbaixo2
10 diagonalcima2
11 diagonal1baixo
12 diagonal1cima   
*/



int main(){
	
	srand(time(NULL));
	
 	MatrizDados * MatrizTreino = ColetarDadosTreino("treino.txt"); // Coleta os dados
 	
 	MatrizDados * MatrizTeste = ColetarDadosTreino("teste.txt");
 	
	 	
	float ** matrizTreino = MatrizTreino->matriz;
		
	float ** matrizTeste = MatrizTeste->matriz;
	
	//da biblioteca windowns.h 
	LARGE_INTEGER frequencia;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    
    QueryPerformanceFrequency(&frequencia);//Mede a frequencia do processador
    	
	int vetorK[] = {1,2,3,4,5,6,7,8,9,10,12,14,16,18,20,25,30,35,40,50,60,70,80,90,100,120,140,160,180,200};
	int x,k,t;
	int resultado;
	int falhas = 0, sucessos = 0;
	
	// Roda o algorimo 5 vezes, uma para cada K. Conta o número de sucessos e falhas em cada K, e printa o resultado
	for (t = 0 ; t < 30; t++ ){
		sucessos = 0;
		falhas = 0;
		k = vetorK[t];
		
		//QueryPerformanceCounter(&start);// Começa a contar o número de clocks
		
		for(x = 0; x < MatrizTeste->numeroDeLinhas; x++){	
			
			//Chama o KNN, que usa o DTW para classificar a serie
			resultado =	KNN(k,matrizTeste[x],MatrizTreino);
			
			// como matrizTeste[x][0] armazena o temanho da serie, a segunda posição contem a classificação da serie
			if(resultado == matrizTeste[x][1] ){
				sucessos++;
			}else{
				falhas++;
			}
				
		}
		
		//QueryPerformanceCounter(&end);// Pega o numero de clocks deposi
	
		//cout << endl << " Tempo para esse K :" <<(double) (end.QuadPart - start.QuadPart) / frequencia.QuadPart<< endl;
		cout <<  k ;
		//cout  << " sucessos: "<< sucessos << endl;
		//cout  << " falhas: " << falhas << endl;
		cout << " " << (float) (sucessos/(float)MatrizTeste->numeroDeLinhas) * 100.0f << endl;;
	}
	
	return 0;
}



// Função para coletar os dados de treino- Essa função cria e preenche uma estrutura de dados dinamicamente.
MatrizDados * ColetarDadosTreino(char nomeArquivo[]){
	
	int numeroDeLinhas = 0;
	
	float ** Matriz = NULL;
	
	// Abre o arquivo com os dados de treino no modo de leitura
	FILE * treino = fopen(nomeArquivo,"r");
	
	//Verifica se o arquivo foi aberto
	if(treino == NULL){
		
		cout << endl << "Arquivo treino não encontrado" << endl;
		return NULL;	
	}

	char auxChar; // Variavel Char Auxiliar
	
	// Contar quantas linhas tem o arquivo	
	while(fscanf(treino, "%c",&auxChar) != EOF){
		
		if(auxChar == '\n'){
			numeroDeLinhas++;
		}				
	}
	
	numeroDeLinhas++; // Para uma maior garantia colocar uma linha a mais
	
	//Agora podemos declarar um vetor com um espaço para cada linha.
	// Porém cada espaço desse vetor representa uma serie temporal (outro vetor), ou seja é um vetor de vetores.
	Matriz = (float **) malloc((numeroDeLinhas) * sizeof(float*));
	
	rewind(treino);// Volta a posição para o começo do arquivo
	
	int numeroDeElementos = 0;//Variavel auxiliar para contar o número de elementos em uma serie temporal(linha)
	int aux, y = 0;
	
	char auxPassado = 'a'; //Essa variavel ajuda a reconhecer quantos elementos tem uma serie temporal
	
	//agora iremos ver qual o tamanho de cada serie temporal, depois alocar um vetor para cada com o tamanho certo da serie temporal.
	while(fscanf(treino, "%c",&auxChar) != EOF){
		
		if(auxChar == '\n'){
			
			//Alocação do vetor com o numero de elemetos correto para cada linha
			Matriz[y] = (float *) malloc((numeroDeElementos+3)*sizeof(float));
			
			//O primeiro elemento de cada vetor é o número de elementos da serie temporal
			Matriz[y][0] = numeroDeElementos+2;
			
			numeroDeElementos  = 0;
			y++;
			auxPassado = 'a';
			continue;
		}
		
		//Condição para contar um elemento
		if((auxChar != ' ') && (auxPassado == ' ')){		
			numeroDeElementos++;
		}
	
		auxPassado = auxChar;
			
	}
	
	numeroDeLinhas = y;	//Atualizar para o número preciso de linhas preenchidas, para nao ocorre problemas futuros
	
	rewind(treino);
	int x;

	// Agora finalmente iremos coletar os dados Float em si.
	// Essa operação se torna simples agora que temos a estrutura pronta	
	for(x = 0; x < numeroDeLinhas; x++){	
		for(y = 1; y < Matriz[x][0]; y++){
		
			fscanf(treino,"%f",&Matriz[x][y]);
		}	
	}
	
	cout << endl << endl;
	
	cout << "NUMERO DE LINHAS: "<<numeroDeLinhas<< endl << endl;
	
	fclose(treino); // Fecha o arquivo
	
	//Criar e preencher a estrutura de dados
	MatrizDados * Dados = (MatrizDados *) malloc(sizeof(MatrizDados));
	
	Dados->matriz = Matriz;
	
	Dados->numeroDeLinhas = numeroDeLinhas;
		
	return Dados;
}


//Algoritmo k-nearest neighbors 


int KNN (const int k, float serieTemporal[], MatrizDados * DadosTreino){
	
	int x,y,m;
	
	int vencedores[500]; // Vetor para os k primeiros vencedores, +30 para evitar bugs;
	
	int numeroDeLinhas = DadosTreino->numeroDeLinhas;//pega o número de series do treino
	
	float ** matrizTreino = DadosTreino->matriz;
	
	float resultados[numeroDeLinhas+1]; // Cria um vetor para armazenar o DTW de cada Serie do treino
	
	for(x = 0; x< numeroDeLinhas; x++){
		
		resultados[x] = DTW(serieTemporal, matrizTreino[x]);// Coleta o DTW de cada serie do treino			
	}
	
	int votos[13];// Vetor que armazena os votos
	//A posição no vetor votos reprezenta a classificação da serie
	//Exemplo: votos[9]- vai armezenar quantos votos tem a classificação "9" 
	
	for(x = 0; x < 13; x++){
		votos[x] = 0;
	}
	
	//Ordena e armazena os k primeira series treino no vetor Vencedores
	// No vetor vencedores so vai a classificação da serie
	KselectionSort(k,resultados,numeroDeLinhas,vencedores,DadosTreino);
		
	//Contar os k primeiros;
	
	for(x = 0; x < k; x++){
		
		votos[vencedores[x]]++;	//Contabiliza os k votos	
	}
		
	int vencedor = 0;
	int maior = 0;

	// Vai pegar a posição com mais votos, que representa a classe vencedora	
	for (y = 0; y < 2; y++){
		for(x = 0; x < 13; x++){
			
			if(votos[x] > maior){
				
				maior = votos[x];		
				vencedor = x;
				
				//Caso ocorra algum empate
			}else if(votos[x] == maior){
				
				/*
				Se ocorrer algum empate, o programa ira pegar os 3 primeiro vencedores
				Ele prioriza o voto que tem um "representante" da classe dele no top 3
				Caso realmente não tenha nenhum dele no top 3 , ele escolhe um aleatoriamente.
				*/
				for(m = 0; m < 3; m++){
					
					if(vencedores[m] == x){
						maior = votos[x];
						vencedor = x;
						break;
					}	
				}
				
				if(rand()%2){
					maior = votos[x];
					vencedor = x;
				}
					
			}		
			
		}
	}
	
	return vencedor;
	
}


/* O algoritmo de ordenação que será usado no KNN é o Selection Sort.
Esse algoritmo é ideal porque não precisamos ordenar todos as instâncias do vetor,
precisamos somente dos primeiros K menores. Assim, o Selection Sort pode ser facilmente
adaptado para realizar essa tarefa, ordenando somente os K primeiros velores do vetor.
Podemos simplismente rodar o algorimo normalmente, e parar o algoritmo depois de K iterações
do Loop externo.*/
// K representa o número de valores a serem ordenados, tam é o tamanho total do vertor, e num é o vetor em si.
void KselectionSort(const int k, float num[], int tam,int vetorAuxiliar[], MatrizDados * Dados){	
	//Selection Sort Padrão, porém so ordena os K primeiro elementos do vetor	
	int i, j,min;
	
	float aux;
	
	float ** matrizTreino = Dados->matriz;
	
	for (i = 0; i < k; i++){
     min = i;
     for (j = (i+1); j < tam; j++) {
     	
       if(num[j] < num[min]) 
         min = j;
     }
     if (num[i] != num[min]) {
    	
		vetorAuxiliar[i] = matrizTreino[min][1];
		
       aux = num[i];
       num[i] = num[min];
       num[min] = aux;
       
     }
  }
	
}


//Distancia Euclidiana
float distanciaEuclidiana(float a, float b){
	
	return abs(a - b);	
}



//Implementação não recursiva do DTW;

float DTW(float serie1[],float serie2[]){
	
	//Primeiramente precisamos criar uma matriz com o tamanho das series;
	int x,y,tamanhoX,tamanhoY;
	
	tamanhoX = serie1[0];
	tamanhoY = serie2[0];
	
	float ** MatrizCusto = (float **) malloc(tamanhoX * sizeof(float*));
	
	for(x = 0; x < tamanhoX; x++){
		
		MatrizCusto[x] = (float*) malloc(tamanhoY * sizeof(float));
	}
	
	//Agora iremos colocar o valor infinito na segunda linha e na primeira coluna da matriz. 
	// O matriz ira começar de verdade no ponto (2,2) e não no (0,0) 
	
	// Zerar a matriz - APAGAR DEPOSI
	
	for (x = 0; x < tamanhoX; x++){
		for(y = 0; y < tamanhoY; y++){
			
			MatrizCusto[x][y] = 0;
		}		
	}
	
	//coloca infinito nas bordas
	for(x = 0; x < tamanhoX; x++){
		
		MatrizCusto[x][1] = INFINITY;
		
	}
	
		//coloca infinito nas bordas
	for(x = 0; x < tamanhoY; x++){
		
		MatrizCusto[1][x] = INFINITY;
	}
	
	MatrizCusto[1][1] = 0;//Seta o começo da matriz
	
	
	// Calcula a função custo
	for (x = 2; x < tamanhoX; x++){
		for(y = 2; y < tamanhoY; y++){
			
			MatrizCusto[x][y] = distanciaEuclidiana(serie1[x],serie2[y]) + 
												Minimo(MatrizCusto[x-1][y-1],MatrizCusto[x][y-1],MatrizCusto[x-1][y]);
			
		}
	}
	
	// Pega o resultado	
	float Resultado = MatrizCusto[tamanhoX-1][tamanhoY-1];
	
	for(x = 0; x < tamanhoX; x++){
		
		free(MatrizCusto[x]);	
	}
	
	free(MatrizCusto);	
	return Resultado;
	
}

//Retorna o minimo entre os floats a,b,c
float Minimo(float a,float b, float c){

	if(a <= b && a <= c){
		return a;
	}
	
	if(b <= a && b <= c){	
		return b;
	}
	if(c <= a && c <= b){	
		return c;
		
	}
}









