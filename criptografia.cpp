#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#define MAX 2
using namespace std;

//Criando um algoritimo de criptografia e o algoritimo reverso

void cifraDeCesar(char texto[], int tamanho){
	for(int i=0;i<tamanho;i++){
		texto[i] = texto[i]+3;
	}
}
void desfazCifra(char texto[], int tamanho){
	for(int i=0;i<tamanho;i++){
		texto[i] = texto[i]-3;
	}
}
//################################################

//Criando um algoritimo de criptografia e o algoritimo reverso

void cifraDoCesao(char texto[], int tamanho){
	for(int i=0;i<tamanho;i++){
		texto[i] = texto[i]+6;
	}
}
void desfazCifraDoCezao(char texto[], int tamanho){
	for(int i=0;i<tamanho;i++){
		texto[i] = texto[i]-6;
	}
}

//################################################

//###############funcão criptografar##############
void criptografar(int seqFunc[MAX], char texto[1000]){
	printf("\n\n");
	unsigned seed = time(0); // variável de tempo que será utilizada para gerar numeros pseudoaleatórios
	srand(seed);
	for(int i=0; i<MAX; i++){
		seqFunc[i] = rand()%2;
		//cout << "\n" << seqFunc[i];
		
		if(seqFunc[i] == 0)
			cifraDeCesar(texto, strlen(texto));
		else if(seqFunc[i] == 1)
			cifraDoCesao(texto, strlen(texto));
		
	}
	
	FILE *arquivo;
	
	arquivo = fopen("texto.txt", "w");
	
	if(arquivo == NULL){
		printf("Problema ao abrir o arquivo :( \n\n");
		exit(0);
	}
	fprintf(arquivo, texto);
	fclose(arquivo);
	
}
//################################################

//##############funcão descriptografar############
void descriptografar(int seqFunc[MAX], char texto[1000]){
	for(int i=0; i<MAX; i++){
		if(seqFunc[i] == 0)
			desfazCifra(texto, strlen(texto));
		else if(seqFunc[i] == 1)
			desfazCifraDoCezao(texto, strlen(texto));
	}
	FILE *arquivo;
	
	arquivo = fopen("texto.txt", "w");
	
	if(arquivo == NULL){
		printf("Problema ao abrir o arquivo :( \n\n");
		exit(0);
	}
	fprintf(arquivo, texto);
	fclose(arquivo);
	printf("\n\n\n");
}
//################################################

//###################Função menu##################
char Menu(){
	system("cls");
	char opcao;
	/*
	printf("------------Digite a opcao desejada------------ \n");
	printf("1) Criptografar \n");
	printf("2) Descriptografar \n");
	printf("3) Mostrar \n");
	printf("4) Sair \n");
	*/
	printf("+-------------------------------------------+ \n");
	printf("|* * * * * * * * * * Menu* * * * * * * * * *| \n");					    					    
	printf("|-------------------------------------------| \n");				    
	printf("|             (1) Criptografar              | \n");
	printf("|-------------------------------------------| \n");	    
	printf("|             (2) Descriptografar           | \n");
	printf("|-------------------------------------------| \n");		    
	printf("|             (3) Exibir	            | \n");
	printf("|-------------------------------------------| \n");	            
	printf("|             (4) Sair			    | \n");       					    				    
	printf("+-------------------------------------------+ \n");

	scanf("%c", &opcao);
	return opcao;
}
//################################################

//#####################Exibir####################
void exibir(char texto[1000]){
	printf("\n %s \n", texto);
}
//################################################


int main() {
	
/*#########Leitura do que está escrito no arquivo para dentro da variável texto: ###########*/

	FILE *arquivo; //Ponteiro do arquivo
	arquivo = fopen("texto.txt", "r"); //abrindo o arquivo para leitura
	
	if(arquivo == NULL){
		printf("Nao foi possivel abrir o arquivo \n"); //verificaçao se existe arquivo aberto, caso contrario, fim do programa
		getchar();
		exit(0);
	}
	
	char linha[1000]; //variavel que ira copiar as linhas
	char texto[1000]; //variavel que recebera as linhas e ao final será o conteúdo completo
	
	/*Copiando o arquivo para a linha*/
	while(fgets(linha, 1000, arquivo) != NULL){ 
		strcat(texto, linha);
	}
	
	printf("%s", texto); //exibindo o texto antes da criptografia
	fclose(arquivo); // fechando o arquivo

/*##########################################################################################*/
	
	int seqFunc[MAX]; // variavel que ira definir quais funcoes de criptografia serao utilizadas
	char opc;
	int trava = 0;
	
	do{
		opc = Menu();
		switch(opc){
			case '1' : 
				if(trava == 0){
					system("cls");
					criptografar(seqFunc, texto);
					system("pause");
					trava++;
				}else{
					printf(" ______________________________________  \n");
					printf("|                                |     | \n");
					printf("| O arquivo ja foi criptografado | :(  | \n");
					printf("|________________________________|_____| \n");
					system("pause");
				}
				break;
			case '2' : 
				if(trava != 0){
					system("cls");
					descriptografar(seqFunc, texto);
					system("pause");
					trava--;
				}else{
					printf(" __________________________________________  \n");
					printf("|                                    |     | \n");
					printf("| O arquivo nao esta criptografado!! | :(  | \n");
					printf("|____________________________________|_____| \n");
					system("pause");
				}
				break;
			case '3' :
				exibir(texto);
				system("pause");
				break;
			case '4' :
				exit(0);
				break;
		}
	}while(opc != '4');
	
}
