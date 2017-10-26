#include "interacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>


void apresenta_programa(char *msg){
	printf ("%s\n", msg);
}

void msg_despedida(char *msg){
	printf("%s\n", msg);
}

void limpa_tela(void){
	system("cls || clear");
}

void limpa_buffer(void){
	setbuf(stdin, NULL);//coloca null no buffer do teclado
}

int le_opcao(int menor_valor, int maior_valor){

	int opcao = 0;
	char* op;

	while(1){
		printf("\nInsira a sua opcao: ");
		op = le_string();

	    opcao = atoi(op);

		if(opcao >= menor_valor && opcao <= maior_valor){
			limpa_buffer();
			break;
		}else {
			printf("\nOpcao invalida\n");
		}
	}
	printf("Opcao escolhida foi: %d", opcao);
	return opcao;
}

char* le_string(void){
	char *caracteres = (char*)malloc(86*sizeof(char));

	if(caracteres == NULL){
		printf("Erro\n");
		exit (1);
	}

	fgets(caracteres,85,stdin);
	limpa_buffer();

return caracteres;
}

/**char* le_senha(void){
	int i;

    fflush(stdin);
    for (i=0;i<8;i++) 
    {
        senha[i] = fgets();
        putchar('*');
    }
    printf("\n");
    senha[i]='\0';

    return senha;
}**/

void apresenta_menu(int n_itens, int menor_opcao,...){
	va_list menu;
	int i;

	va_start(menu,menor_opcao);

	for(i=0; i<n_itens; i++){
		printf("\n%d - %s", menor_opcao++, va_arg(menu, char*));
	}

	va_end(menu);
}