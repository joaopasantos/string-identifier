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
				printf("É uma placa de veículo.\n\n");
			}else{
				printf("Não foi possível identificar.\n\n");
			}
		}else if(strlen(str)==11){
			if(eCPF(str)){
				printf("É um CPF.\n\n");
				printf((cpfValido(str)) ? "Válido\n\n" : "Inválido\n\n");
			}else{
				printf("Não foi possível identificar.\n\n");
			}
		}else{
			if(eEmail(str)){
				printf("É um endereço de e-mail.\n\n");
			}else{
				printf("Não foi possível identificar.\n\n");
			}
		}
		
		do {
			printf("Deseja continuar?(S/N) ");
			fgets(str, MAX_STRING_SZ, stdin);

			if ((strlen(str) > 0) && (str[strlen (str) - 1] == '\n')) str[strlen (str) - 1] = '\0';
		} while(strcmp(strlwr (str), "s") && strcmp(strlwr (str), "n"));
		
	} while(!strcmp(strlwr (str), "s"));

	/* Libera a memória e fecha. */
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
			printf("São letras: %d | ", saoLetras);
			if(isalpha(str[i])){
				printf("Character %c in %s is alphabetic\n", str[i], str);
			}else{
				printf("Character %c in %s is not alphabetic\n", str[i], str);
			}
			*/
	}
	
	
	/*
	if (saoLetras){
		printf("Os 3 primeiros dígitos são letras.\n");
	}else{
		printf("Um ou mais dos 3 primeiros dígitos não são letras.\n");
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
		printf("Os 4 ultimos dígitos são numeros.\n");
	}else{
		printf("Um ou mais dos 4 ultimos dígitos não são numeros.\n");
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
	/* A verificação do CPF acontece utilizando os 9 primeiros dígitos e, com um cálculo simples, verificando se o resultado corresponde aos dois últimos dígitos (depois do sinal "-"). */
	int retorno = 1;
	int primeiroDigitoValido = 1;
	int segundoDigitoValido = 1;
	
	/* Validação do primeiro dígito */
	/* Primeiramente multiplica-se os 9 primeiros dígitos pela sequência decrescente de números de 10 à 2 e soma os resultados. */
	int multiplicador = 10;
	int somaPrimeiroDigito = 0;
	for (int i = 0; i < 9; i++){
		printf("Soma: %d | Dígito: %d | Multiplicador: %d\n", somaPrimeiroDigito, charToInt(str[i]), multiplicador);
		somaPrimeiroDigito += charToInt(str[i])*multiplicador;
		multiplicador--;
	}
	printf("Soma do primeiro dígito: %d\n", somaPrimeiroDigito);
	/* O próximo passo da verificação também é simples, basta multiplicarmos esse resultado por 10 e dividirmos por 11. */
	/*O resultado que nos interessa na verdade é o RESTO da divisão. 
	Se ele for igual ao primeiro dígito verificador (primeiro dígito depois do '-'), a primeira parte da validação está correta.*/
	int primeiroDigitoVerificador = (somaPrimeiroDigito*10)%11;
	
	/* Observação Importante: Se o resto da divisão for igual a 10, nós o consideramos como 0. */
	if (primeiroDigitoVerificador == 10) {
		(primeiroDigitoVerificador = 0);
	} 
	
	/* Verifica validade do primeiro dígito */
	primeiroDigitoValido = (primeiroDigitoVerificador == charToInt(str[9]));
	printf("Primeiro dígito %d é válido: %d\n", primeiroDigitoVerificador, primeiroDigitoValido);
	
	/* Validação do segundo dígito */
	/*A validação do segundo dígito é semelhante à primeira. */ 
	/* Porém vamos considerar os 9 primeiros dígitos, mais o primeiro dígito verificador, e vamos multiplicar esses 10 números pela sequencia decrescente de 11 a 2.*/
	multiplicador = 11;
	int somaSegundoDigito = 0;
	for (int i = 0; i < 10; i++){
		printf("Soma: %d | Dígito: %d | Multiplicador: %d\n", somaSegundoDigito, charToInt(str[i]), multiplicador);
		somaSegundoDigito += charToInt(str[i])*multiplicador;
		multiplicador--;
	}
	printf("Soma do segundo dígito: %d\n", somaSegundoDigito);
	int segundoDigitoVerificador = (somaSegundoDigito*10)%11;
	if (segundoDigitoVerificador == 10) {
		segundoDigitoVerificador = 0;	
	} 
	/* Verifica validade do segundo dígito */
	segundoDigitoValido = (segundoDigitoVerificador == charToInt(str[10]));
	printf("Segundo dígito %d  é válido: %d\n", segundoDigitoVerificador, segundoDigitoValido);
	
	retorno = (primeiroDigitoValido&&segundoDigitoValido);
	return retorno;
}

int eEmail(char *str){
	char *dominio;
	char *categoriaDeDominio;
	
	dominio = strchr(str, '@');
	categoriaDeDominio = strchr(str, '.');
	if ((dominio != NULL) && (strlen(categoriaDeDominio)>=3)){
		printf("Domínio do e-mail: %s\n", dominio);
		printf("Categoria de domínio: %s\n", categoriaDeDominio);
		return 1;
	} else {
		return 0;
	}	
}

int charToInt(char caractere){
	int retorno = caractere - '0';
		
	return retorno;
}
