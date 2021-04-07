#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_STRING_SZ 256

void desenhaTitulo();
int ePlaca(char *str);
int eCPF(char *str);
int cpfValido(char *str);
int eEmail(char *str);
void *leTeclado(char *saida, char *entrada);
int charToInt(char caractere);

int main(int argC, char *argV[]) {
	/* Altera o padr�o para a localidade do SO */
	setlocale(LC_ALL,"");
	
	/* Aloca mem�ria, e checa se realmente foi alocado */
	char *str = malloc(MAX_STRING_SZ);
	if (str == NULL) {
		printf("No memory\n");
		return 1;
	}
	
	desenhaTitulo();
	/* Inicia um loop de entrada de String at� que o usu�rio defina que n�o quer continuar */
	do {
		leTeclado("Digite a cadeia a ser validada: ", str);

		printf("Entrada: %s\n", str);
		
		if(strlen(str)==7){
			if(ePlaca(str)){
				printf("� uma placa de ve�culo.\n\n");
			}else{
				printf("N�o foi poss�vel identificar.\n\n");
			}
		}else if(strlen(str)==11){
			if(eCPF(str)){
				printf("� um CPF %s.\n\n",(cpfValido(str)) ? "V�lido" : "Inv�lido");
			}else{
				printf("N�o foi poss�vel identificar.\n\n");
			}
		}else{
			if(eEmail(str)){
				printf("� um endere�o de e-mail.\n\n");
			}else{
				printf("N�o foi poss�vel identificar.\n\n");
			}
		}
		
		do {
			leTeclado("Deseja continuar?(S/N) ", str);
		} while(strcmp(strlwr (str), "s") && strcmp(strlwr (str), "n"));
		printf("__________________________________\n\n");
	} while(!strcmp(strlwr (str), "s"));

	/* Libera a mem�ria e sai. */
	free(str);
	return 0;
}

void desenhaTitulo(){
	printf("\n");
	printf(" _____ _       _                   _   _         _   _ ___ _        \n");
	printf("|   __| |_ ___|_|___ ___    ___   |_|_| |___ ___| |_|_|  _|_|___ ___ \n");
	printf("|__   |  _|  _| |   | . |  |___|  | | . | -_|   |  _| |  _| | -_|  _|\n");
	printf("|_____|_| |_| |_|_|_|_  |         |_|___|___|_|_|_| |_|_| |_|___|_|  \n");
	printf("                    |___|                                            \n");
	printf("\n");
}

int ePlaca(char *str){
	int retorno = 0;
	int saoLetras = 1;
	int saoNumeros = 1;
	
	/* Verifica se os tr�s primeiros caracteres s�o letras */
	for (int i = 0; i < 3; i++){
		saoLetras = (saoLetras&&isalpha(str[i]));
	}
	
	if(!saoLetras){
		return 0;
	}
	
	/* Verifica se os quatro �ltimos caracteres s�o numerais decimasis */
	for (int i = 3; i < strlen(str); i++){
		saoNumeros = (saoNumeros&&isdigit(str[i]));
	}

	retorno = saoLetras&&saoNumeros;
	
	return retorno;
}

int eCPF(char *str){
	int retorno = 1;
	
	/* Verifica se todos os caracteres s�o numerais decimais */
	for (int i = 0; i < strlen(str); i++){
		retorno = (retorno&&isdigit(str[i]));
	}
	
	return retorno;
}

int cpfValido(char *str){
	/* A verifica��o do CPF acontece utilizando os 9 primeiros d�gitos e, com um c�lculo simples, verificando se o resultado corresponde aos dois �ltimos d�gitos (depois do sinal "-"). */
	int retorno = 1;
	int primeiroDigitoValido = 1;
	int segundoDigitoValido = 1;
	
	/* Valida��o do primeiro d�gito */
	/* Primeiramente multiplica-se os 9 primeiros d�gitos pela sequ�ncia decrescente de n�meros de 10 � 2 e soma os resultados. */
	int multiplicador = 10;
	int somaPrimeiroDigito = 0;
	for (int i = 0; i < 9; i++){
		somaPrimeiroDigito += charToInt(str[i])*multiplicador;
		multiplicador--;
	}
	
	/* O pr�ximo passo da verifica��o tamb�m � simples, basta multiplicarmos esse resultado por 10 e dividirmos por 11. */
	int primeiroDigitoVerificador = (somaPrimeiroDigito*10)%11;
	
	/* Observa��o Importante: Se o resto da divis�o for igual a 10, n�s o consideramos como 0. */
	if (primeiroDigitoVerificador == 10) {
		(primeiroDigitoVerificador = 0);
	} 
	
	/* Verifica validade do primeiro d�gito */
	primeiroDigitoValido = (primeiroDigitoVerificador == charToInt(str[9]));
	
	/* Valida��o do segundo d�gito */
	/*A valida��o do segundo d�gito � semelhante � primeira. */ 
	/* Por�m vamos considerar os 9 primeiros d�gitos, mais o primeiro d�gito verificador, e vamos multiplicar esses 10 n�meros pela sequencia decrescente de 11 a 2.*/
	multiplicador = 11;
	int somaSegundoDigito = 0;
	for (int i = 0; i < 10; i++){
		somaSegundoDigito += charToInt(str[i])*multiplicador;
		multiplicador--;
	}
	
	int segundoDigitoVerificador = (somaSegundoDigito*10)%11;
	if (segundoDigitoVerificador == 10) {
		segundoDigitoVerificador = 0;	
	} 
	
	/* Verifica validade do segundo d�gito */
	segundoDigitoValido = (segundoDigitoVerificador == charToInt(str[10]));
	
	retorno = (primeiroDigitoValido&&segundoDigitoValido);
	return retorno;
}

void *leTeclado(char *saida, char *entrada){
	/* Imprime a sa�da, e l� a entrada respeitando o tamanho definido*/
	printf(saida);
	fgets(entrada, MAX_STRING_SZ, stdin);
	
	/* Remove a quebra de linha n�o intencional, caso exista */
	if ((strlen(entrada) > 0) && (entrada[strlen (entrada) - 1] == '\n')) entrada[strlen (entrada) - 1] = '\0';
}

int eEmail(char *str){
	char *dominio;
	char *categoriaDeDominio;
	
	/* Procura o caractere '@' na String, e retorna o resto da string a partir dele */
	dominio = strchr(str, '@');
	/* Procura o caractere '.' na Substring, e retorna o resto da substring a partir dele */
	categoriaDeDominio = strchr(str, '.');
	
	/* Verifica se foi poss�vel achar o '@', e se o dom�nio � v�lido */
	if ((dominio != NULL) && (categoriaDeDominio != NULL)){
		if(strlen(categoriaDeDominio)>=3){
			return 1;
		}
		return 0;
	} else {
		return 0;
	}
}

int charToInt(char caractere){
	int retorno = caractere - '0';
		
	return retorno;
}
