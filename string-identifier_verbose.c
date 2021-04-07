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
	/* Altera o padrão para a localidade do SO */
	setlocale(LC_ALL,"");
	
	/* Aloca memória, e checa se realmente foi alocado */
	char *str = malloc(MAX_STRING_SZ);
	if (str == NULL) {
		printf("No memory\n");
		return 1;
	}
	
	desenhaTitulo();
	/* Inicia um loop de entrada de String até que o usuário defina que não quer continuar */
	do {
		leTeclado("Digite a cadeia a ser validada: ", str);

		printf("Entrada: %s\n", str);
		
		if(strlen(str)==7){
			if(ePlaca(str)){
				printf("É uma placa de veículo.\n\n");
			}else{
				printf("Não foi possível identificar.\n\n");
			}
		}else if(strlen(str)==11){
			if(eCPF(str)){
				printf("\nÉ um CPF %s", (cpfValido(str)) ? "Válido.\n\n" : "Inválido.\n\n");
			}else{
				printf("\nNão foi possível identificar.\n\n");
			}
		}else{
			if(eEmail(str)){
				printf("\nÉ um endereço de e-mail.\n\n");
			}else{
				printf("\nNão foi possível identificar.\n\n");
			}
		}
		
		do {
			leTeclado("Deseja continuar?(S/N) ", str);
		} while(strcmp(strlwr (str), "s") && strcmp(strlwr (str), "n"));
		printf("__________________________________\n\n");
	} while(!strcmp(strlwr (str), "s"));

	/* Libera a memória e sai. */
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
	printf("Verbose mode: ON\n\n");
}

int ePlaca(char *str){
	int retorno = 0;
	int saoLetras = 1;
	int saoNumeros = 1;
	
	/* Verifica se os três primeiros caracteres são letras */
	printf("\n");
	for (int i = 0; i < 3; i++){
		saoLetras = (saoLetras&&isalpha(str[i]));
			if(isalpha(str[i])){
				printf("Caractere %c em %s é alfabético\n", str[i], str);
			}else{
				printf("Caractere %c em %s não é alfabético\n", str[i], str);
			}
	}
	
	if (saoLetras){
		printf("Os 3 primeiros dígitos são letras do alfabeto.\n\n");
	}else{
		printf("Um ou mais dos 3 primeiros dígitos não são letras do alfabeto.\n\n");
		return 0;
	} 
	
	/* Verifica se os quatro últimos caracteres são numerais decimasis */
	for (int i = 3; i < strlen(str); i++){
		saoNumeros = (saoNumeros&&isdigit(str[i]));
		if(isdigit(str[i])){
			printf("Caractere %c em %s é decimal\n", str[i], str);
		}else{
			printf("Caractere %c em %s não é decimal\n", str[i], str);
		}
	}
	
	if (saoNumeros){
		printf("Os 4 últimos dígitos são numeros.\n\n");
	}else{
		printf("Um ou mais dos 4 últimos dígitos não são numeros.\n\n");
	}
	
	retorno = saoLetras&&saoNumeros;
	
	return retorno;
}

int eCPF(char *str){
	int retorno = 1;
	
	/* Verifica se todos os caracteres são numerais decimais */
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
	
	printf("\n");
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
	printf("Primeiro dígito %d é válido: %d\n\n", primeiroDigitoVerificador, primeiroDigitoValido);
	
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
	printf("Segundo dígito %d é válido: %d\n", segundoDigitoVerificador, segundoDigitoValido);
	
	retorno = (primeiroDigitoValido&&segundoDigitoValido);
	return retorno;
}

void *leTeclado(char *saida, char *entrada){
	/* Imprime a saída, e lê a entrada respeitando o tamanho definido*/
	printf(saida);
	fgets(entrada, MAX_STRING_SZ, stdin);
	
	/* Remove a quebra de linha não intencional, caso exista */
	if ((strlen(entrada) > 0) && (entrada[strlen (entrada) - 1] == '\n')) entrada[strlen (entrada) - 1] = '\0';
}

int eEmail(char *str){
	char *dominio;
	char *categoriaDeDominio;
	
	/* Procura o caractere '@' na String, e retorna o resto da string a partir dele */
	dominio = strchr(str, '@');
	/* Procura o caractere '.' na Substring, e retorna o resto da substring a partir dele */
	categoriaDeDominio = strchr(str, '.');
	
	/* Verifica se foi possível achar o '@', e se o domínio é válido */
	if ((dominio != NULL) && (categoriaDeDominio != NULL)){
		if(strlen(categoriaDeDominio)>=3){
			printf("\nDomínio do e-mail: %s\n", dominio);
			printf("Categoria de domínio: %s\n", categoriaDeDominio);
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
