#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STRING_SZ 256

int main(int argC, char *argV[]) {
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
			
		}else if(strlen(str)==11){
			
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
