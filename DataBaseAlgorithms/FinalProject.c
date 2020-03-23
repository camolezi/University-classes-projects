/*

Membros do Grupo

Lucas Nascimento Camolezi  10276932
Matheus Victal Cerqueira  10276661
Felipe Barbosa de Oliveira  10276928
Afonso Henrique Piacentini Garcia  9795272

*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//estrutura de dados que representa um registro
typedef struct registro{
	//campo1
	int numHabitantes;
	
	//Campo2
	char nomeCidade[30];
	
	//Campo3
	char nomePais[20];
	
	//Campo4
	char dataFundacao[10];
	
}registro;

//Enum que representa os campos
enum Campos{
	Campo1, 
	Campo2,
	Campo3,
	Campo4
};

#define tamPaginaDisco 16000
#define tamBuffer 4

//func�es
void removerFimDeLinha(char * palavraAux, int tamanho);
int numeroDeLinhasArquivo(FILE * arquivo);
int numeroDeRegistros(char * nome);
void gerarBD(char * nomeArquivo, int n);
registro * lerArquivo(char * nome);
void escreverArquivo(registro * vetorRegistros, char * nomeArquivo, int tamanhoArquivo);
void printarArquivo(char * nome);
void gerarDataFundacao(char * str);
void ordenacaoInterna(char * nomeInicial, char * nomeFinal);
void mergeSort(registro * arr, int l, int r);
void trueMerge(registro * vetor, int tamanho);
void merging(char *arquivo1, char *arquivo2, char * nomeFinal);
int quebrarArquivo(char * nome);
void sortMergeExterno(char * nome, char * nomeFinal);
void matching(char *arquivo1, char *arquivo2, char * nomeFinal);



int main(int argc, char **argv){
	
	//Seed para gera��es aleatorias 
	srand(time(NULL));
	
	switch(argv[1][0]){
		
		case '1':
			//Gera��o do banco de dados
			gerarBD(argv[2],atoi(argv[3]));
			break;
		case '2':
			//Printar o arquivo
			printarArquivo(argv[2]);	
			break;
		case '3':
			//Ordena��o Interna
			ordenacaoInterna(argv[2], argv[3]);
			break;
		case '4':
			//Meging 
			merging(argv[2],argv[3],argv[4]);
			break;
		case '5':
			//Matching 
			matching(argv[2],argv[3],argv[4]);
			break;
		case '6':
			
			break;
		case '7':
			//sortMergeExterno
			sortMergeExterno(argv[2],argv[3]);
			break;
		default:
			printf("Comando n�o reconhecido");
			break;
	}
	
	return 0;
}
	

//Fun��o auxiliar para o mergeSort
void merge(registro * arr, int l, int m, int r, int campo){ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 
  
    //Vetores temporarios
    registro L[n1], R[n2]; 
  
    //Copia os valores
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 
  
 
    i = 0; 
    j = 0; 
    k = l; 
	
    while (i < n1 && j < n2){ 
    
    	int aprovado = 0;
    	//Sele��o de campo para a ordena��o a partir do parametro recebido
    	switch(campo){
    		
    		case Campo1:    			
    			if (L[i].numHabitantes <= R[j].numHabitantes) { 
			        aprovado = 1;
			    }
 		   		break;
	
    		case Campo2:	
				if ( strcmp(L[i].nomeCidade, R[j].nomeCidade) <= 0) { 
            		aprovado = 1; 
        		}
    			break;
    			
    		case Campo3:
    			if ( strcmp(L[i].nomePais, R[j].nomePais) <= 0) { 
            		aprovado = 1; 
        		}
    			break;
    			
    		case Campo4:
    			if ( strcmp(L[i].dataFundacao, R[j].dataFundacao) <= 0) { 
            		aprovado = 1; 
        		}
    			break;
    			
    		default:
    			printf("\n ERRO");
    			break;
			    		
		}
        if (aprovado == 1) { 
            arr[k] = L[i]; 
            i++; 
        } 
        else{ 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  	//Copia os elementos restantes , caso tenha sobrado
    while (i < n1){ 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  
   //Copia os elementos restantes , caso tenha sobrado
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 

//Merge Sort padr�o muito bem documentado na literatura, com a diferen�a de uma variavel auxiliar para escolher qual campo ser� ordenado 
void mergeSort(registro * arr, int l, int r, int campo) { 
	int m;
    if (l < r){
		m =  l+(r-l)/2; 
        mergeSort(arr, l, m, campo); 
        mergeSort(arr, m+1, r, campo); 
        merge(arr, l, m, r, campo); 
    } 
} 

//Fun��o que ordena um vetor, considerando primeiramente o campo 1, e campo 2, campo 3 e campo 4 como crit�rios de desempates
void trueMerge(registro * vetor, int tamanho){
	/*
	Como mergeSort � um algoritmo de ordena��o est�vel, uma maneira r�pida 
	de ordenar o vetor da forma pedida � come�ar a ordenar pelo Campo 4.
	Depois ordena-se o Campo 3 por cima, Por�m os registros do campo 3 que forem iguais
	continuar�o ordenados a partir do campo 4. A mesma coisa acontece quando ordenamos pelo campo 2
	e finalmente pelo campo 1. Essa l�gico s� funciona para algorimos de ordena��o est�veis
	
	*/
	
	//� usada uma enum como parametro para o mergesort saber qual campo ordenar
	mergeSort(vetor,0,tamanho-1, Campo4);
	mergeSort(vetor,0,tamanho-1, Campo3);
	mergeSort(vetor,0,tamanho-1, Campo2);
	mergeSort(vetor,0,tamanho-1, Campo1);
	return;
}

//Fun��o que ordena um arquivo internamente 
void ordenacaoInterna(char * nomeInicial, char * nomeFinal){

	if(nomeInicial == NULL || nomeFinal == NULL){
		printf("\nFalha no processamento");
		return;
	}
	
	//Numero de registros do arquivo
	int numRegistros =  numeroDeRegistros(nomeInicial);
	
	//Le o arquivo e recebe um vetor com todos os registros
	registro * vetor = lerArquivo(nomeInicial);
	
	//Chama a fun��o trueMerge, que ordena o vetor
	trueMerge(vetor, numRegistros);
	
	//Escreve no novo arquivo o resultado da ordena��o
	escreverArquivo(vetor,nomeFinal, numRegistros);	
	
	printf("\nArquivo Gerado");
	return;
}

//Fun��o que gera uma data de funda��o
void gerarDataFundacao(char * str){
	
	if(str == NULL){
		return;
	}
	
	int x= 0;
	char numero;
	
	//Sortei 10 numeros aleatorios para a data
	for(x = 0; x < 10; x++){
		numero = (char) (48 + (rand() % 10));
		str[x] = numero;
	}
	//Seta os chars que s�o fixos
	str[2] = '/';
	str[5] = '/';
	str[10] = '\0';
}

//Fun��o de printa um arquivo de forma organizada na sa�da padr�o
void printarArquivo(char * nome){
	
	//Condi��o inicial
	if(nome == NULL){
		printf("\nFalha no processamento");
		return;
	}
	
	//Recebe o arquivo j� na ram da fun��o LerArquivo
	registro * teste = lerArquivo(nome);
	
	//PEga o numero de registros do arquivo
	int tamanho = numeroDeRegistros(nome);

	int x,y;
	
	//Printa a estrutura de dados
	for(x = 0; x < tamanho; x++){
		printf("\n");
		printf("\n%d", teste[x].numHabitantes);
		printf(" ");

		printf("%s",teste[x].nomeCidade);	
		printf(" ");
	
		printf("%s",teste[x].nomePais);
		printf(" ");
		for(y = 0; y < 10; y++){
			printf("%c", teste[x].dataFundacao[y]);	
		}	
	}
	
	//Da free na memoria e retorna
	free(teste);
	return;
}

//Fun��o que retora o numero de registros de um arquivo	
int numeroDeRegistros(char * nome){
	
	FILE * arquivo  = fopen(nome,"rb");
	
	if(arquivo == NULL){
		return 0;
	}
	
	fseek(arquivo,0,SEEK_END);
	long int tamanhoArquivo = ftell(arquivo) - sizeof(char); //Tira o tamanho do status
	rewind(arquivo);
	
	//Encontrar o numero de registros
	int numRegistros = tamanhoArquivo / sizeof(registro);
		
	fclose(arquivo);
	return numRegistros;
}


//Fun��o auxiliar que le um arquivo inteiro e o coloca na RAM, retornando um vetor de registros
registro * lerArquivo(char * nome){
	
	//Codi��o inicial
	if(nome == NULL){
		printf("\nFalha no processamento");
		return NULL;
	}
	
	int numRegistros = numeroDeRegistros(nome);
	
	//Caso o numero de registros � 0
	if(numRegistros == 0){
		printf("\nArquivo Vazio");
		return NULL;
	}
	//abra o arquivo
	FILE * arquivo = fopen(nome,"rb");
	
	if(arquivo == NULL){
		printf("\nFalha no processamento");
		return NULL;
	}
	
	char status = '0';
	
	//Ler o byte do status e verifica q integridade do arquivo
	fread(&status,sizeof(char), 1, arquivo);
	if(status == '0'){
		printf("\nArquivo de leitura esta comprometido...\n");
	}
	
	//Cria o vetor de registros
	registro * vetorReg = (registro *) malloc(sizeof(registro) * numRegistros);
	
	//Le o arquivo e coloca no vetor de struct 
	int x;
	for(x = 0; x < numRegistros; x++){
		fread( &(vetorReg[x].numHabitantes) ,4,1,arquivo);
		fread( &(vetorReg[x].nomeCidade) ,1,30,arquivo);
		fread( &(vetorReg[x].nomePais) ,1,20,arquivo);
		fread( &(vetorReg[x].dataFundacao) ,1,10,arquivo);
	}
	
	//Fecha o arquivo e retorna o vetor
	fclose(arquivo);
	return vetorReg;
}

//Escreve um arquivo recebendo como parametro um vetor de registros
void escreverArquivo(registro * vetorRegistros, char * nomeArquivo, int tamanhoArquivo){
	
	FILE * newArquivo = fopen(nomeArquivo, "wb+");
	
	if(newArquivo == NULL || vetorRegistros == NULL){
		printf("\nFalha no processamento");
		return;
	}
		
	//Escreve status;
	char status = '1';
	fwrite(&status, sizeof(char), 1, newArquivo);
	
	int x;
	for(x = 0; x < tamanhoArquivo; x++){
		//Escreve primeiro campo
		fwrite(&vetorRegistros[x].numHabitantes, sizeof(int), 1, newArquivo);
				//Escreve segundo campo
		fwrite(&vetorRegistros[x].nomeCidade,sizeof(char), 30, newArquivo);	
			//esccreve o terceiro campo
		fwrite(&vetorRegistros[x].nomePais,sizeof(char),20, newArquivo);
		//quartoCampo
		fwrite(&vetorRegistros[x].dataFundacao, sizeof(char), 10, newArquivo);		
	}
	
	free(vetorRegistros);
	fclose(newArquivo);
	return;
}


//Fun��o que gera um arquivo de banco de dados no formato especificado aleatoriamente
void gerarBD(char * nomeArquivo, int n){
	
	if(nomeArquivo == NULL){
		return;
		printf("\nFalha no processamento\n");
	}
	
	//Cria o arquivo para escrita binaria
	FILE * newArquivo = fopen(nomeArquivo, "wb+");
	
	//abrir o bd 
	FILE * bd = NULL;
	bd = fopen("BD2.txt","r");
	if(bd == NULL){
		printf("\nFalha no processamento\n");
		return;
	}
	
	//Pega o n�mero de linhas do BD
	int numLinhasBD = numeroDeLinhasArquivo(bd);
	
	//Coloca as linhas do BD na RAM para facilitar o sorteio e manipula��o
	int x; 
	char ** arquivoBD = (char **) malloc(sizeof(char *) * numLinhasBD);
	for(x = 0; x < numLinhasBD ; x++){
		arquivoBD[x] = (char*) malloc(sizeof(char) * 15);
		fgets(arquivoBD[x],15,bd);	
	}
	
	//Escreve o status no novo arquivo
	char status = '1';
	fwrite(&status, sizeof(char), 1, newArquivo);
	
	//Cria as variasveis de sorteio, por linhas no BD
	int linhaSorteio1 = rand() % numLinhasBD;
	int linhaSorteio2 = rand() % numLinhasBD;
	int numHabitantes = (rand() * rand()) % 30000;
	int linhaSorteio3 = rand() % numLinhasBD;
	int	linhaSorteio4 = rand() % numLinhasBD;
	
	//palavra auxiliar
	char palavraAux[31];
	


	for(x = 0; x < n; x++){
		//Escreve o primeiro campo= int 4 bytes
		//Sorteia os valores a serem escritos, so sorteia em multiplos de 3 para ficarem valores repetidos	
		if((x % 3) > 0){
			numHabitantes = (rand() * rand()) % 50000;
		}
		fwrite(&numHabitantes, sizeof(int), 1, newArquivo);
		
		//Segundo campo � uma combina��o entre as duas linhas de sorteio, so sorteia em multiplos de 4
		if(x % 4){
			linhaSorteio1 = rand() % numLinhasBD;
			linhaSorteio2 = rand() % numLinhasBD;
		}
			
		strcpy(palavraAux,arquivoBD[linhaSorteio1]);
		strcat(palavraAux,arquivoBD[linhaSorteio2]);
		removerFimDeLinha(palavraAux,30);
		
		//Escreve segundo campo
		fwrite(palavraAux,sizeof(char), 30, newArquivo);
		
		
		//O terceiro campo tamb�m � uma combina��o de 2 linhas
		//S� sorteia novos campos em m�ltiplos de 5 para ocorrerem repeti��es
		if(x % 5){
			linhaSorteio3 = rand() % numLinhasBD;
			linhaSorteio4 = rand() % numLinhasBD;
		}
		
		strcpy(palavraAux,arquivoBD[linhaSorteio3]);
		strcat(palavraAux,arquivoBD[linhaSorteio4]);
		removerFimDeLinha(palavraAux,20);
		//esccreve o terceiro campo
		fwrite(palavraAux,sizeof(char),20, newArquivo);
		
		//Gera o quarto campo
		gerarDataFundacao(palavraAux);
		//quartoCampo
		fwrite(palavraAux, sizeof(char), 10, newArquivo);		
	}
	
	
	//Libera a memoria usada e fecha os arquivos
	for(x = 0; x < numLinhasBD ; x++){
		free(arquivoBD[x]);	
	}
	free(arquivoBD);
	fclose(newArquivo);
	fclose(bd);
	
	printf("\nArquivo Gerado");
}


//Fun�ao que forma uma string, para deixar de acordo com as normas de escrita em um campo
void removerFimDeLinha(char * palavraAux, int tamanho){
	
	//Fun��o que formata uma string corretamente para ser armazenada em um arquivo;	
	if(palavraAux == NULL){
		return;
	}
	
	//Retira os \n e troca por espa�os
	int x, aux = 0;
	for(x = 0; x < tamanho-1; x++){
		if(palavraAux[x] == '\n'){
			palavraAux[x] = ' ';
		}
		if(palavraAux[x] == '\0'){
			aux = 1;
		}
	}
	
	//Em caso da string nao conter um \0, coloca um no final dela;
	if(aux == 0){
		palavraAux[tamanho-1] = '\0';
	}
	return;
}

//Conta o numero de linhas de um arquivo
int numeroDeLinhasArquivo(FILE * arquivo){
	rewind(arquivo);
	int aux = '0';
	int contador = 0;
	
	while(aux != EOF){
		aux = fgetc(arquivo);
		if(aux == '\n'){
			contador++;
		}
	}
	rewind(arquivo);
	return contador;
}

//Escreve um unico registro em um arquivo
void escreveArquivoFinal(registro regUnico, FILE* pArquivo){
	//escreve o valor do primeiro campo no arquivo de sa�da
	fwrite((&regUnico.numHabitantes),sizeof(int),1, pArquivo);
	//escreve o valor do segundo campo no arquivo de sa�da
	fwrite((&regUnico.nomeCidade),sizeof(char),30, pArquivo);
	//escreve o valor do terceiro campo no arquivo de sa�da
	fwrite((&regUnico.nomePais),sizeof(char),20, pArquivo);
	//escreve o valor do quarto campo no arquivo de sa�da
	fwrite((&regUnico.dataFundacao),sizeof(char),10, pArquivo);
}

//fun��o l� o pr�ximo registro no arquivo
void lerRegistro(registro * regUnico, FILE* pArquivo){
	fread( &(regUnico->numHabitantes) ,4,1,pArquivo);
	fread( &(regUnico->nomeCidade) ,1,30,pArquivo);
	fread( &(regUnico->nomePais) ,1,20,pArquivo);
	fread( &(regUnico->dataFundacao) ,1,10,pArquivo);
}

/*A fun��o mergeAux � uma fun��o auxiliar que realiza a compara��o entre os registros caso os valores correspondentes ao campo 1 dos dois sejam 
iguais. Nesse caso ser� realizada a compara��o utilizando-se dos outros campos. Como as compara��es s�o realizadas entre strings, optou-se por
colocar as compara��oes a partir do campo2 em uma mesma fun��o, a qual recebe como par�matros os registros a serem comparados e um ponteiro
para o arquivo final. Tal fun��o devolve um int 0 , 1 ou 2 (recebido pela vari�vel controleAux na fun��o merging): caso seja 0, tem-se que o reg1 
foi visto como o menor e colocado no arquivo final, caso seja 1, tem-se que o reg2 foi visto como menor e colocado no arquivo final e por fim, 
caso seja 2, reg1 e reg2 s�o exatamente iguais. As compara��es s�o realizadas na ordem de prioridade padronizada. A fun��o coloca o registro menor
 no arquivo final. Caso eles sejam exatamente iguais, ela ir�alocar o registro duplicado no arquivo final. A duplica��o n�o ser� tratada como um 
 erro neste projeto.*/

int mergeAux(registro reg1, registro reg2, FILE *pArquivo){
	if(strcmp(reg1.nomeCidade,reg2.nomeCidade) < 0){
		escreveArquivoFinal(reg1, pArquivo);
		//caso o registro 1 seja menor pelo campo 2 e seja colocado no arquivo final, a fun��o retorna 0
		return 0;
	}
	if(strcmp(reg1.nomeCidade,reg2.nomeCidade) > 0){
		escreveArquivoFinal(reg2, pArquivo);
		//caso o registro 2 seja menor pelo campo 2 e seja colocado no arquivo final, a fun��o retorna 1
		return 1;
	}
	else{//empate no campo 2
		if(strcmp(reg1.nomePais,reg2.nomePais) < 0){
		    escreveArquivoFinal(reg1, pArquivo);
		    //caso o registro 1 seja menor pelo campo 3 e seja colocado no arquivo final, a fun��o retorna 0
		    return 0;
	    }
	    if(strcmp(reg1.nomePais,reg2.nomePais) > 0){
		    escreveArquivoFinal(reg2, pArquivo);
		    //caso o registro 2 seja menor pelo campo 3 e seja colocado no arquivo final, a fun��o retorna 1
		    return 1;
	    }
	    else{//empate no campo 3
	    	if(strcmp(reg1.dataFundacao,reg2.dataFundacao) < 0){
		        escreveArquivoFinal(reg1, pArquivo);
		        //caso o registro 1 seja menor pelo campo 4 e seja colocado no arquivo final, a fun��o retorna 0
		        return 0;
	        }
	        if(strcmp(reg1.dataFundacao,reg2.dataFundacao) > 0){
		        escreveArquivoFinal(reg2, pArquivo);
		        //caso o registro 2 seja menor pelo campo 4 e seja colocado no arquivo final, a fun��o retorna 1
		        return 1;
	        }
	        else{//Os registros s�o exatamente iguais, empate no campo 4
	        	//Coloca-se o valor do registro duplicado no arquivo final
	        	escreveArquivoFinal(reg1, pArquivo);
	        	escreveArquivoFinal(reg2, pArquivo);
	        	return 2;
			}
		}
	}
}

/*A fun��o merging ir� receber duas strings correspondentes aos nomes dos arquivos a serem fundidos e o n�mero de registros de cada um (tam1 e tam2). 
Ele ir� comparar os registros utilizando-se da l�gica da fun��o merging, isso �, compara o primeiro regitro do arquivo1 com o primeiro do arquivo2 e aloca
o menor no arquivo que ser� retornado pela fun��o (arquivoFinal). O arquivo de retorno ser� um arquivo de tamanho tam1+tam2 com os valores ordenados de 
cada registro considerando-se primeiramente seu campo 1, depois o campo 2, depois o campo 3 e depois o campo 4, sendo que cada campo s� � comparado se 
o anterior for conflitante.*/

void merging(char *arquivo1, char *arquivo2, char * nomeFinal){
	
	int tam1 = numeroDeRegistros(arquivo1);
	
	int tam2 = numeroDeRegistros(arquivo2);
	
	//2 contadores: um para o primeiro arquivo de entrada (count1) e um para o segundo (count2)
	int count1 = 1, count2 = 1;
	
	//tal vari�vel � respons�vel por receber o resultado da fun��o mergeAux
	int controleAux;
	
	//ponteiros para os arquivos de entrada
	FILE *pArquivo1 = fopen(arquivo1,"rb");
	FILE *pArquivo2 = fopen(arquivo2,"rb");
	
	//declara��o das vari�veis de checagem dos status dos arquivos
	char status1 = '0';
	char status2 = '0';
	
	//verifica a exist�ncia dos arquivos
	if(pArquivo1==NULL || pArquivo2==NULL){
		printf("\nFalha no Processamento");
		return;
	}
	//verifica��o dos status de cada arquivo de entrada
	fread(&status1,sizeof(char), 1, pArquivo1);
	if(status1 == '0'){
		printf("\nArquivo de leitura esta comprometido...\n");//alerta de arquivo corrompido
	}
	
	fread(&status2,sizeof(char), 1, pArquivo2);
	if(status2 == '0'){
		printf("\nArquivo de leitura esta comprometido...\n");//alerta de arquivo corrompido
	}
	
	//declara��o do arquivo de sa�da
	FILE *arquivoFinal = fopen(nomeFinal,"wb+");
	
	//adiciona o registro de status no arquivo final
	char status = '1';
    fwrite(&status, sizeof(char), 1, arquivoFinal);
	
	//structs respons�veis por armazenar os registros que est�o sendo comparados no momento
	registro regUnico1;
	registro regUnico2;
	
	//obt�m o primeiro registro do arquivo1 e coloca suas informa��es no struct regUnico1
	lerRegistro(&regUnico1,pArquivo1);
	
	//obt�m o primeiro registro do arquivo2 e coloca suas informa��es no struct regUnico2
	lerRegistro(&regUnico2,pArquivo2);
	
	//la�o verifica se algum dos arquivos foi completamente acessado, caso cont�rio, os registros continuam sendo comparados
	while(count1<=tam1 && count2<=tam2){
			
		if(regUnico1.numHabitantes < regUnico2.numHabitantes){
			
			//escreve no arquivo final o registro do arquivo1
			escreveArquivoFinal(regUnico1,arquivoFinal);
			
			/*o comando � seguir leem o proximo registro do arquivo1 e o aloca na struct relativa ao armazenamento de registros do arquivo1 
			para compara��o*/
			
			lerRegistro(&regUnico1,pArquivo1);
			
			//incrementa o contador relatico ao arquivo1
			count1++;
		}else
		if(regUnico1.numHabitantes > regUnico2.numHabitantes){
		    //escreve no arquivo final o registro do arquivo1
			escreveArquivoFinal(regUnico2,arquivoFinal);
			
			/*o comando � seguir leem o proximo registro do arquivo1 e o aloca na struct relativa ao armazenamento de registros do arquivo1 
			para compara��o*/
			
			lerRegistro(&regUnico2,pArquivo2);
			
			//incrementa o contador relatico ao arquivo2
			count2++;
		}
		else{//empate no campo 1
			//vari�vel recebe o resultado de mergeAux, que identifica qual registro foi considerado menor ou se eles s�o exatamente iguais
			controleAux = mergeAux(regUnico1, regUnico2, arquivoFinal); 
			
			/*O controleAux � verificado em um switch, que ir� definir qual arquivo ter� seu proximo registro lido. Tal a��o depende de qual dos
			registros comparados foi computado como menor e alocado no arquivo final. O arquivo de origem de tal registro, ter� seu pr�ximo registro
			lido e comparado com o atual do outro arquivo. Os contadores tamb�m ser�o incrementados de acordo com o resultado*/
			switch(controleAux){
				//caso em que o menor registro � o proveniente do arquivo 1
				case 0:
					lerRegistro(&regUnico1, pArquivo1);
					count1++;
				break;	
				//caso em que o menor registro � o proveniente do arquivo 2
				case 1:
					lerRegistro(&regUnico2, pArquivo2);
					count2++;
				break;
				//caso em que os registros provenientes do arquivo 1 e do arquivo 2 s�o exatamente iguais
				case 2:
					//os dois arquivos t�m seus pr�ximos registros lidos
					lerRegistro(&regUnico1, pArquivo1);
				    lerRegistro(&regUnico2, pArquivo2);	
				    //os dois contadores s�o incrementados, indicando prosseguimento de leitura nos 2 arquivos concomitantemente
				    count1++;
				    count2++;
				break;    
				//em caso de erro na fun��o mergeAux e retorno de um valor int n�o correspondente aos casos acima
				default:
				    printf("\nErro na compara��o de arquivos");
			}
		}
    }
		/*ap�s um dos arquivos ter sido completamente lido, ainda � necess�rio colocar os registros faltantes da outro arquivo no arquivo
		final, dessa forma, basta repassar os registros na ordem que aparecem, do arquivo de entrada para o de sa�da.*/
		
		//verifica qual arquivo foi completamene lido
	if(count1 == tam1 + 1){
		while(count2<=tam2){
			//leitura do pr�ximo registro do arquivo faltante
			    
		    lerRegistro(&regUnico2,pArquivo2);
	            
	        //aloca��o de seus registros no arquivo final
	            
	        escreveArquivoFinal(regUnico2,arquivoFinal);
	        
	        //incrementa o contador
	        count2++;
		}
	}
	if(count2 == tam2 + 1){
		while(count1<=tam1){
				
			//leitura do pr�ximo registro do arquivo faltante
			lerRegistro(&regUnico1,pArquivo1);
	            
	        //aloca��o de seus registros no arquivo final
	        escreveArquivoFinal(regUnico1,arquivoFinal);
	        
	        //incrementa o contador
	        count1++;
		}
	}
	
	//fechamento de todos os arquivos utilizados no processo de merging
	fclose(pArquivo1);
	fclose(pArquivo2);
	fclose(arquivoFinal);
	printf("\nArquivo Gerado");
//	printarArquivo(nomeFinal);
}

//A fun��o merging3 � basicamente um merging de 3 arquivos, reliazado o primeiro com o segundo, depois o resultado disso com o terceiro arquivo
void merging3(char * arquivo1, char * arquivo2, char * arquivo3, char * nomeFinal){
	merging(arquivo1,arquivo2,"arquivoAuxx");
	merging("arquivoAuxx",arquivo3, nomeFinal);
	
//	printf("\n 1: %s   2: %s  3: %s",arquivo1,arquivo2,arquivo3);
	return;
}

//Ordena��o externa, fun��o que quebra o arquivo em arquivos menores com tamnho de uma pagina de disco
//Os arquivos menores ja saem ordenados 
int quebrarArquivo(char * nome){	
	if(nome == NULL){
		return 0;
	}
	
	//Numero de registros
	int numRegistrosTotal = numeroDeRegistros(nome);
	//abra o arquivo
	FILE * arquivo = fopen(nome,"rb");
	
	if(arquivo == NULL){
		printf("\nArquivo de leitura n�o encontrado\n");
		return 0;
	}
	
	char status = '0';
	//Encontrar o numero de registros
	
	//Ler o byte do status e verifica q integridade do arquivo
	fread(&status,sizeof(char), 1, arquivo);
	if(status == '0'){
		printf("\nArquivo de leitura esta comprometido...\n");
	}
	
	//Registro auxiliar
	registro aux;	
	//Ira quebrar o arquivo em diversos arquivos com tamanho de uma pagina de disco
	//Descobre quantas registros cada arquivo ter�
	int numRegistrosPorArquivo = tamPaginaDisco / sizeof(registro);
	
 	//Num de arquivos, pode ser quebrado
 	float numArquivoFloat = (float) ( (float)numRegistrosTotal /(float) numRegistrosPorArquivo);
	
	//Numero total de arquivos que ser�o criados INTEIRO
 	int numeroDeArquivosGerados =  ( numRegistrosTotal / numRegistrosPorArquivo);
 	
 	//Teste para ver se o numero � quebrado e precisa de mais um arquivo	
 	if(numArquivoFloat > (int)numArquivoFloat){
 		numeroDeArquivosGerados++;
	}
	//variaveis auxiliares
	int x,y;
	//Nome dos arquivos que ser�o gerados e posteriormente ordenados
	char nomeArquivoGerado[10] = "Sub_a";
	char nomeArquivoOrdenado[10] = "SubOrd_a";
	FILE * arquivoAux;
	//Varivel utilizada para ver se o arquivos esta no fim
	int totalDeRegistrosPercorridos = 0;
	
	for(y = 0; y < numeroDeArquivosGerados; y++){
		
		//Atualiza o nome do arquivo, aumenta uma letra para cada itera��o
		nomeArquivoGerado[4] = (char)(97+y);
		nomeArquivoOrdenado[7] = (char)(97+y);	
		
		//Cria o arquivo com o nome da itera��o e escre o status
		arquivoAux = fopen(nomeArquivoGerado,"wb+");
		status = '1';
		fwrite(&status, sizeof(char), 1, arquivoAux);
		
		//At� completar uma pagina de disco o progama ir� ler e escrever o proximo registro no arquivo
		for(x = 0; x < numRegistrosPorArquivo; x++){
			//Ve se o arquivo terminou j�
			if(totalDeRegistrosPercorridos >= numRegistrosTotal){
				break;
			}
			//Le o proximo registro
			lerRegistro(&aux,arquivo);
			escreveArquivoFinal(aux,arquivoAux);
			totalDeRegistrosPercorridos++;
		}
		
		fclose(arquivoAux);
		//Ordena o arquivo para j� sair com um arquivos pequenos ordenados 
		ordenacaoInterna(nomeArquivoGerado,nomeArquivoOrdenado);
	}
	
	return numeroDeArquivosGerados;
}


/*
A fun��o sort-mergeExterno � respons�vel por ordenar um arquivo externamente, 
ou seja, a ordena��o n�o � realizada na RAM. A ordena��o � realizada usando t�cnicas 
de sort e merging. Dado um arquivo a fun��o primeiramente ir� quebrar esse arquivo em v�rios 
arquivos menores de tamanho de uma p�gina de disco. Esses pequenos arquivos de uma p�gina 
de disco podem ser ordenados individualmente utilizando a ordena��o interna na RAM. Depois 
esses arquivos podem ser juntados dois a dois usando o merging, criando assim, ao 
final do processo, um �nico arquivo ordenado 
*/
void sortMergeExterno(char * nome, char * nomeFinal){
	
	if(nome == NULL || nomeFinal == NULL){
		printf("Falha no Processamento");
		return;
	}
	//Variaveis auxiliares
	int numArquivos,x, impar,y = 0;
	
	//Utiliza a fun��o quebrar arquivos para quebrar o arquivo em n arquivos ordenados de tamanho de uma pagina de disco
	numArquivos = quebrarArquivo(nome);
	
	//Variavies com os nomes que ser�o usadas no manejamento dos arquivos
	char nomeArquivoOrdenado1[30] = "SubOrd_a";
	char nomeArquivoOrdenado2[30] = "SubOrd_a";
	char nomeProximoCiclo[30] = "SubOrd_a";
	
	//Executa o loop enquanto ainda tiver arquivos para dar merge
	//O codigo executa um merge 2 a 2
	while(numArquivos > 1){
		
		//Verifica se o num de arquivos atual � par ou impar
		if(numArquivos % 2 == 0){
			impar = 0;
		}else{
			impar = 1;
		}
		
		//zera o contador
		int counter = 0;
		int z;
		//zera os nomes
		for (z = 0; z < y; z++){
			nomeArquivoOrdenado1[7+z] = (char)(97);
			nomeArquivoOrdenado2[7+z] = (char)(97);
			nomeProximoCiclo[7+z+1] = (char)(97);
		}
		//zera os nomes
		nomeProximoCiclo[7+y+1] = (char)(97 + counter);
		nomeProximoCiclo[7+y+2] = '\0';	
		
		for(x = 1; x < numArquivos; x+=2){
			nomeProximoCiclo[7+y+1] = (char)(97 + counter);
			nomeArquivoOrdenado1[7+y] = (char)(97+x);	
			nomeArquivoOrdenado1[7+y+1] = '\0';
			nomeArquivoOrdenado2[7+y] = (char)(97+x-1);
			nomeArquivoOrdenado2[7+y+1] = '\0';
			
			if(x >= (numArquivos - 2) && impar){	
				char terceiroArquivo[30];
				strcpy(terceiroArquivo,nomeArquivoOrdenado1);
				terceiroArquivo[7+y] = (char)(97+x+1);			
				merging3(nomeArquivoOrdenado1, nomeArquivoOrdenado2,terceiroArquivo,nomeProximoCiclo);
			}else{
				merging(nomeArquivoOrdenado1,nomeArquivoOrdenado2,nomeProximoCiclo);
			}
			counter++;	
		}	
		numArquivos = numArquivos/2;
		y++;
	}
	rename(nomeProximoCiclo,nomeFinal);
	printf("\nArquivo Gerado");
}

int matchingAux(registro reg1, registro reg2, FILE *pArquivo){
	
	printf("\nERROERROERRO\n");
	if(strcmp(reg1.nomeCidade,reg2.nomeCidade) < 0){
		escreveArquivoFinal(reg1, pArquivo);
		//caso o registro 1 seja menor pelo campo 2 e seja colocado no arquivo final, a fun��o retorna 0
		return 0;
	}
	if(strcmp(reg1.nomeCidade,reg2.nomeCidade) > 0){
		escreveArquivoFinal(reg2, pArquivo);
		//caso o registro 2 seja menor pelo campo 2 e seja colocado no arquivo final, a fun��o retorna 1
		return 1;
	}
	else{//empate no campo 2
		if(strcmp(reg1.nomePais,reg2.nomePais) < 0){
		    escreveArquivoFinal(reg1, pArquivo);
		    //caso o registro 1 seja menor pelo campo 3 e seja colocado no arquivo final, a fun��o retorna 0
		    return 0;
	    }
	    if(strcmp(reg1.nomePais,reg2.nomePais) > 0){
		    escreveArquivoFinal(reg2, pArquivo);
		    //caso o registro 2 seja menor pelo campo 3 e seja colocado no arquivo final, a fun��o retorna 1
		    return 1;
	    }
	    else{//empate no campo 3
	    	if(strcmp(reg1.dataFundacao,reg2.dataFundacao) < 0){
		        escreveArquivoFinal(reg1, pArquivo);
		        //caso o registro 1 seja menor pelo campo 4 e seja colocado no arquivo final, a fun��o retorna 0
		        return 0;
	        }
	        if(strcmp(reg1.dataFundacao,reg2.dataFundacao) > 0){
		        escreveArquivoFinal(reg2, pArquivo);
		        //caso o registro 2 seja menor pelo campo 4 e seja colocado no arquivo final, a fun��o retorna 1
		        return 1;
	        }
	        else{//Os registros s�o exatamente iguais, empate no campo 4
	        	//Coloca-se o valor do registro do primeiro arquivo
	        	escreveArquivoFinal(reg1, pArquivo);
	        	return 2;
			}
		}
	}
}

/*A fun��o matching realiza a interse��o de dois arquivos (arquivo1 e arquivo2), isso �, ela encontra os registros em comum entre dois 
arquivos e os coloca em  um novo arquivo. Tal fun��o recebe como par�metros duas strings correspondentes aos nomes dos arquivos a serem analisados
pela fun��o. O matching gera um arquivo (arquivoFinal) que cont�m os registros com o campo 1 em comum nos arquivos 1 e 2 ordenados. Ap�s encontrar
um par de registros com campo 1 em comum, a fun��o usa da prioridade de campos a partir do campo 2 para ordenar os registros*/

void matching(char *arquivo1, char *arquivo2, char * nomeFinal){
	//2 contadores: um para o primeiro arquivo de entrada (count1) e um para o segundo (count2)
	int count1 = 1, count2 = 1;
	
	int tam1 = numeroDeRegistros(arquivo1);
	int tam2 = numeroDeRegistros(arquivo2);
	
	//tal vari�vel � respons�vel por receber o resultado da fun��o mergeAux
	int controleAux;
	
	/*tal vari�vel � respons�vel por receber um valor de controle para tratar de um caso em que dois registros s�o id�ndicos. Nesse caso, � necess�rio
	alocar o registro referente ao arquivo2 no arquivoFinal, j� que na fun��o auxiliar apenas o registro do arquivo um vai para o arquivoFinal*/
	int controlId = 0;
	
	//ponteiros para os arquivos de entrada
	FILE *pArquivo1 = fopen(arquivo1,"rb");
	FILE *pArquivo2 = fopen(arquivo2,"rb");
	
	//declara��o das vari�veis de checagem dos status dos arquivos
	char status1 = '0';
	char status2 = '0';
	
	//verifica a exist�ncia dos arquivos
	if(pArquivo1==NULL || pArquivo2==NULL){
		printf("\nFalha no processamento\n");
		return;
	}
	//verifica��o dos status de cada arquivo de entrada
	fread(&status1,sizeof(char), 1, pArquivo1);
	if(status1 == '0'){
		printf("\nFalha no processamento\n");//alerta de arquivo corrompido
	}
	
	fread(&status2,sizeof(char), 1, pArquivo2);
	if(status2 == '0'){
		printf("\nFalha no processamento\n");//alerta de arquivo corrompido
	}
	
	//declara��o do arquivo de sa�da
	FILE *arquivoFinal = fopen(nomeFinal,"wb+");
	
	//adiciona o registro de status no arquivo final
	char status = '1';
    fwrite(&status, sizeof(char), 1, arquivoFinal);
	
	//structs respons�veis por armazenar os registros que est�o sendo comparados no momento
	registro regUnico1;
	registro regUnico2;
	
	//obt�m o primeiro registro do arquivo1 e coloca suas informa��es no struct regUnico1
	lerRegistro(&regUnico1,pArquivo1);
	
	//obt�m o primeiro registro do arquivo2 e coloca suas informa��es no struct regUnico2
	lerRegistro(&regUnico2,pArquivo2);
	
	//la�o verifica se algum dos arquivos foi completamente acessado, caso cont�rio, os registros continuam sendo comparados
	while(count1<=tam1 && count2<=tam2){
		
		if(regUnico1.numHabitantes < regUnico2.numHabitantes){
			
			/*o comando � seguir l� o proximo registro do arquivo1 e o aloca na struct relativa ao armazenamento de registros do arquivo1 
			para compara��o*/
			
			lerRegistro(&regUnico1,pArquivo1);
			
			//incrementa o contador relativo ao arquivo1
			count1++;
			
			if(controlId == 1){	
				//coloca o valor do regUnico2 no arquivoFinal caso este ainda n�o tenha sido alocado
				escreveArquivoFinal(regUnico2, arquivoFinal);
				//reinicia o valor de controlId, evitando repeti��es n�o existentes no arquivoFinal
			    controlId = 0;
			}
		}else
		if(regUnico1.numHabitantes > regUnico2.numHabitantes){
			
			/*o comando � seguir l� o proximo registro do arquivo1 e o aloca na struct relativa ao armazenamento de registros do arquivo1 
			para compara��o*/
			
			lerRegistro(&regUnico2,pArquivo2);
			
			//incrementa o contador relativo ao arquivo2
			count2++;
			
			if(controlId == 1){	
				//coloca o valor do regUnico2 no arquivoFinal caso este ainda n�o tenha sido alocado
				escreveArquivoFinal(regUnico2, arquivoFinal);
				//reinicia o valor de controlId, evitando repeti��es n�o existentes no arquivoFinal
			    controlId = 0;
			}
		}
		else{
				//vari�vel recebe o resultado de mergeAux, que identifica qual registro foi considerado menor ou se eles s�o exatamente iguais
			controleAux = matchingAux(regUnico1, regUnico2, arquivoFinal); 
			
			/*O controleAux � verificado em um switch, que ir� definir qual arquivo ter� seu proximo registro lido. Tal a��o depende de qual dos
			registros comparados foi computado como menor e alocado no arquivo final. O arquivo de origem de tal registro, ter� seu pr�ximo registro
			lido e comparado com o atual do outro arquivo. Os contadores tamb�m ser�o incrementados de acordo com o resultado*/
			switch(controleAux){
				//caso em que o menor registro � o proveniente do arquivo 1
				case 0:
					lerRegistro(&regUnico1, pArquivo1);
					count1++;
				break;	
				//caso em que o menor registro � o proveniente do arquivo 2
				case 1:
					lerRegistro(&regUnico2, pArquivo2);
					count2++;
				break;
				//caso em que os registros provenientes do arquivo 1 e do arquivo 2 s�o exatamente iguais
				case 2:
					//um dos arquivos tem seu pr�ximo registro lido, o outro mant�m-se para prevenir-se o caso do pr�ximo registro tamb�m ser id�ntico
					lerRegistro(&regUnico1, pArquivo1);
					
					//controlId recebe 1 indicando que o registro vindo do arquivo 2
					controlId = 1;
				    //o contador correspondente � acrescido
				    count1++;
				break;    
				//em caso de erro na fun��o matchingAux e retorno de um valor int n�o correspondente aos casos acima
				default:
				    printf("\nFalha no processamento\n");
		    }
	    }
	}
	
	//fechamento de todos os arquivos utilizados no processo de merging
	fclose(pArquivo1);
	fclose(pArquivo2);
	fclose(arquivoFinal);
	
	printf("\nArquivo gerado\n");	
}

	
