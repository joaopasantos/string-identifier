#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_STRING_SZ 256

int ePlaca(char *str);
int eCPF(char *str);
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

		if ((strlen(str) > 0) && (str[strlen (str) - 1] == '\n'))
			str[strlen (str) - 1] = '\0';

		printf("String: %s\n", str);
		
		if(strlen(str)==7){
			if(ePlaca(str)){
				printf("É uma placa de veículo.\n\n");
			}else{
				printf("Não foi possível identificar.\n\n");
			}
		}else if(strlen(str)==11){
			if(eCPF(str)){
				printf("É uma placa de veículo.\n\n");
			}else{
				printf("Não foi possível identificar.\n\n");
			}
		}else{
			
		}
		
		do {
			printf("Deseja continuar?(S/N) ");
			fgets(str, MAX_STRING_SZ, stdin);

			if ((strlen(str) > 0) && (str[strlen (str) - 1] == '\n'))
				str[strlen (str) - 1] = '\0';
		} while(strcmp(str, "S") && strcmp(str, "N"));
		
	} while(!strcmp(str, "S"));

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
		/* printf("Sao letras: %d | ", saoLetras);
		if(isalpha(str[i])){
			printf("Character %c in %s is alphabetic\n", str[i], str);
		}else{
			printf("Character %c in %s is not alphabetic\n", str[i], str);
		}		*/
	}
	
	/*
	if (saoLetras){
		printf("Os 3 primeiros dígitos são letras.\n");
	}else{
		printf("Um ou mais dos 3 primeiros dígitos não são letras.\n");
	}*/
	
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
	
}

int charToInt(char caractere){
	int retorno = caractere - '0';
	
	return retorno
}
