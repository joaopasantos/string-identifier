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
				printf("É um CPF %s.\n\n",(cpfValido(str)) ? "Válido" : "Inválido");
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
}

int ePlaca(char *str){
	int retorno = 0;
	int saoLetras = 1;
	int saoNumeros = 1;
	
	/* Verifica se os três primeiros caracteres são letras */
	for (int i = 0; i < 3; i++){
		saoLetras = (saoLetras&&isalpha(str[i]));
	}
	
	if(!saoLetras){
		return 0;
	}
	
	/* Verifica se os quatro últimos caracteres são numerais decimasis */
	for (int i = 3; i < strlen(str); i++){
		saoNumeros = (saoNumeros&&isdigit(str[i]));
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
	int retorno = 1;
	int primeiroDigitoValido = 1;
	int segundoDigitoValido = 1;
	
	/* Verifica se todos os dígitos são iguais (CPF inválido) */
	int saoIguais = 1;
	for (int i = 1; i < strlen(str); i++){
		if(str[i-1]!=str[i]){
			saoIguais = 0;
		}
	}
	if (saoIguais){
		return 0;
	}
	
	printf("\n");
	/* Validação do primeiro dígito */
	/* Primeiramente multiplica-se os 9 primeiros dígitos pela sequência decrescente de números de 10 à 2 e soma-se os resultados. */
	int multiplicador = 10;
	int somaPrimeiroDigito = 0;
	int primeiroDigitoVerificador;
	for (int i = 0; i < 9; i++){
		somaPrimeiroDigito += charToInt(str[i])*multiplicador;
		multiplicador--;
	}
	
	/* O resultado obtido será divido por 11. 
	Considere como quociente apenas o valor inteiro, o resto da divisão será responsável pelo cálculo do primeiro dígito verificador. */
	/* Caso o resto da divisão seja menor que 2, o nosso primeiro dígito verificador se torna 0 (zero), 
	caso contrário subtrai-se o valor obtido de 11 */
	int resto = somaPrimeiroDigito%11;
	
	if (resto < 2) {
		primeiroDigitoVerificador = 0;
	} else {
		primeiroDigitoVerificador = 11 - resto;	
	}
	
	/* Verifica validade do primeiro dígito */
	primeiroDigitoValido = (primeiroDigitoVerificador == charToInt(str[9]));
	
	/* Validação do segundo dígito */
	/*A validação do segundo dígito é semelhante à primeira. */ 
	/* Porém vamos considerar os 9 primeiros dígitos, mais o primeiro dígito verificador, e vamos multiplicar esses 10 números pela sequencia decrescente de 11 a 2.*/
	multiplicador = 11;
	int somaSegundoDigito = 0;
	int segundoDigitoVerificador;
	for (int i = 0; i < 10; i++){
		somaSegundoDigito += charToInt(str[i])*multiplicador;
		multiplicador--;
	}
	
	resto = somaSegundoDigito%11;
	if (resto < 2) {
		segundoDigitoVerificador = 0;
	} else {
		segundoDigitoVerificador = 11 - resto;	
	}
	
	/* Verifica validade do segundo dígito */
	segundoDigitoValido = (segundoDigitoVerificador == charToInt(str[10]));
	
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
