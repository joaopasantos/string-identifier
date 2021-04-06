#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_STRING_SZ 256

int ePlaca(char *str);
int eCPF(char *str);
int cpfValido(char *str);
int eEmail(char *str);
int charToInt(char caractere);

int main(int argC, char *argV[]) {
	setlocale(LC_ALL,"");
	
	char *str = malloc(MAX_STRING_SZ);
	
	if (str == NULL) {
		printf("No memory\n");
		return 1;
	}

	do {
		printf("Digite a string: ");
		fgets(str, MAX_STRING_SZ, stdin);

		if ((strlen(str) > 0) && (str[strlen (str) - 1] == '\n')) str[strlen (str) - 1] = '\0';

		printf("String: %s\n", str);
		
		if(strlen(str)==7){
			if(ePlaca(str)){
				printf("� uma placa de ve�culo.\n\n");
			}else{
				printf("N�o foi poss�vel identificar.\n\n");
			}
		}else if(strlen(str)==11){
			if(eCPF(str)){
				printf("� um CPF.\n\n");
				printf((cpfValido(str)) ? "V�lido\n\n" : "Inv�lido\n\n");
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
			printf("Deseja continuar?(S/N) ");
			fgets(str, MAX_STRING_SZ, stdin);

			if ((strlen(str) > 0) && (str[strlen (str) - 1] == '\n')) str[strlen (str) - 1] = '\0';
		} while(strcmp(strlwr (str), "s") && strcmp(strlwr (str), "n"));
		
	} while(!strcmp(strlwr (str), "s"));

	/* Libera a mem�ria e fecha. */
	free(str);
	return 0;
}

int ePlaca(char *str){
	int retorno = 0;
	int saoLetras = 1;
	int saoNumeros = 1;
	
	for (int i = 0; i < 3; i++){
		saoLetras = (saoLetras&&isalpha(str[i]));
			/*
			printf("S�o letras: %d | ", saoLetras);
			if(isalpha(str[i])){
				printf("Character %c in %s is alphabetic\n", str[i], str);
			}else{
				printf("Character %c in %s is not alphabetic\n", str[i], str);
			}
			*/
	}
	
	
	/*
	if (saoLetras){
		printf("Os 3 primeiros d�gitos s�o letras.\n");
	}else{
		printf("Um ou mais dos 3 primeiros d�gitos n�o s�o letras.\n");
	} 
	*/
	
	for (int i = 3; i < strlen(str); i++){
		saoNumeros = (saoNumeros&&isdigit(str[i]));
		/*printf("Sao numeros: %d | ", saoNumeros);
		if(isdigit(str[i])){
			printf("Character %c in %s is decimal\n", str[i], str);
		}else{
			printf("Character %c in %s is not decimal\n", str[i], str);
		}*/
	}
	
	/*if (saoNumeros){
		printf("Os 4 ultimos d�gitos s�o numeros.\n");
	}else{
		printf("Um ou mais dos 4 ultimos d�gitos n�o s�o numeros.\n");
	}*/
	
	retorno = saoLetras&&saoNumeros;
	
	return retorno;
}

int eCPF(char *str){
	int retorno = 1;
	
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
		printf("Soma: %d | D�gito: %d | Multiplicador: %d\n", somaPrimeiroDigito, charToInt(str[i]), multiplicador);
		somaPrimeiroDigito += charToInt(str[i])*multiplicador;
		multiplicador--;
	}
	printf("Soma do primeiro d�gito: %d\n", somaPrimeiroDigito);
	/* O pr�ximo passo da verifica��o tamb�m � simples, basta multiplicarmos esse resultado por 10 e dividirmos por 11. */
	/*O resultado que nos interessa na verdade � o RESTO da divis�o. 
	Se ele for igual ao primeiro d�gito verificador (primeiro d�gito depois do '-'), a primeira parte da valida��o est� correta.*/
	int primeiroDigitoVerificador = (somaPrimeiroDigito*10)%11;
	
	/* Observa��o Importante: Se o resto da divis�o for igual a 10, n�s o consideramos como 0. */
	if (primeiroDigitoVerificador == 10) {
		(primeiroDigitoVerificador = 0);
	} 
	
	/* Verifica validade do primeiro d�gito */
	primeiroDigitoValido = (primeiroDigitoVerificador == charToInt(str[9]));
	printf("Primeiro d�gito %d � v�lido: %d\n", primeiroDigitoVerificador, primeiroDigitoValido);
	
	/* Valida��o do segundo d�gito */
	/*A valida��o do segundo d�gito � semelhante � primeira. */ 
	/* Por�m vamos considerar os 9 primeiros d�gitos, mais o primeiro d�gito verificador, e vamos multiplicar esses 10 n�meros pela sequencia decrescente de 11 a 2.*/
	multiplicador = 11;
	int somaSegundoDigito = 0;
	for (int i = 0; i < 10; i++){
		printf("Soma: %d | D�gito: %d | Multiplicador: %d\n", somaSegundoDigito, charToInt(str[i]), multiplicador);
		somaSegundoDigito += charToInt(str[i])*multiplicador;
		multiplicador--;
	}
	printf("Soma do segundo d�gito: %d\n", somaSegundoDigito);
	int segundoDigitoVerificador = (somaSegundoDigito*10)%11;
	if (segundoDigitoVerificador == 10) {
		segundoDigitoVerificador = 0;	
	} 
	/* Verifica validade do segundo d�gito */
	segundoDigitoValido = (segundoDigitoVerificador == charToInt(str[10]));
	printf("Segundo d�gito %d  � v�lido: %d\n", segundoDigitoVerificador, segundoDigitoValido);
	
	retorno = (primeiroDigitoValido&&segundoDigitoValido);
	return retorno;
}

int eEmail(char *str){
	char *dominio;
	char *categoriaDeDominio;
	
	dominio = strchr(str, '@');
	categoriaDeDominio = strchr(str, '.');
	if ((dominio != NULL) && (strlen(categoriaDeDominio)>=3)){
		printf("Dom�nio do e-mail: %s\n", dominio);
		printf("Categoria de dom�nio: %s\n", categoriaDeDominio);
		return 1;
	} else {
		return 0;
	}	
}

int charToInt(char caractere){
	int retorno = caractere - '0';
		
	return retorno;
}
