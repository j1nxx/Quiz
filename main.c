#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "usuario.h"
#include "interacao.h"
#include "questoes.h"
#include "hanking.h"
#define OP1 "Login"
#define OP2 "Novo cadastro"
#define OP3 "Hanking"
#define OP4 "Sair do programa"
#define APRESENTACAO "\n\nBem-vind@ ao quiz virtual.\nAuthor: Déborah Assuncao e Eliomar Rabelo\nDate: 23/10/2017"
#define DESPEDIDA "\n\t\tObrigad@ e boa sorte!\n\n"

int main(void){

	setlocale(LC_ALL,"");

    FILE* fp_questoes = fopen("bd_de_questoes.txt","rt");
    FILE* fp_usuarios = fopen("bd_de_usuarios.txt","rt");
    FILE* fp_hanking = fopen("bd_de_hanking.txt","rt+");

	Heap* fila_questoes = heap_carrega(fp_questoes);//questoes que estao armazenada num arquivo, como banco de dados de questoes.*/
	UserHash* tab_user = usuario_cadastro_carrega(fp_usuarios);//banco de dados de usuarios, arquivo com todos os usuarios previamente cadastrados.
	Arv* tab_hanking =  hanking_carrega(fp_hanking); //banco de dados de hanking, arquivo com as pontuações de cada usuario que efetuou por completo o quiz.


	int opcao;
	char* login;
    char* senha;
    char test;
	User *usuario_logado;

	if(fp_usuarios==NULL || fp_hanking==NULL){
		printf("Erro de arq\n");
	}


	apresenta_programa(APRESENTACAO);
	do
    {
		apresenta_menu(4, 1, OP1, OP2, OP3, OP4);
        //printf("\n\nOpcao: ");
        opcao = le_opcao(1, 4);

        switch(opcao){


        	case 1:
        	printf("\n\nEfetuando login...\n\n");
        	do{
        		printf("\nLogin: ");
        		login = le_string();
        		printf("\nSenha: ");
        		senha = le_string();
                /*for (i=0;i<4;i++) 
                {
                    senha[i] = le_string();
                    putchar('*');
                }
                printf("\n");
                senha[i]='\0';
                system("pause");
                } */
        	    usuario_logado = usuario_valida_cadastro(tab_user,login,senha);// rettorna 0 para aluno || retorna 1 para professor
            if(usuario_logado == NULL){
            	limpa_tela();limpa_buffer();
                printf("\n\nUsuário não cadastrado... tente novamente!\n");
            	apresenta_menu(2, 1,OP1, OP4);
            	opcao = le_opcao(1, 2);
            	if(opcao == 2){
            		break;
            	}
            }

            }while(usuario_logado == NULL);// se retornou null, então o cadastro nao existe
            
      
        	if(usuario_perfil(usuario_logado) == 0){//ALUNO
        		printf("\n..........Acesso básico.........\n");
        		printf("\n..........Iniciando QUIZ........\n");
        		limpa_tela();

                int size = heap_size(fila_questoes);
        		int pont_atual = 0;
                int i;

        		for(i = 0 ; i<size; i++){
        			printf("\n[%2d] Questão: ", i);
        			pont_atual += imprime_questao(heap_pos(i)); // essa funçao irá retornar 10(se o usuario acertar a questão)
       				limpa_tela();									   // ou 0(se errar a questão)									
        		}
        		usuario_pontuacao_set(usuario_logado, pont_atual);
        		hanking_insere(tab_hanking,usuario_nome(usuario_logado),pont_atual);//insere no hanking

        		printf("\n..........Fim do Quiz..........\n");
        		printf("Iniciando processamento de respostas...\n");
        		printf("Calculando pontuação...\n");
        		printf("pontuação obtida no teste: %2d%%\n",usuario_pontuacao(usuario_logado));
        		printf("\n\n..........Encerrando QUIZ..........\n\n");
        	}
        	else if(usuario_perfil(usuario_logado) == 1){//PROFESSOR
        		printf("\n..........Acesso avançado.........................\n");
        		printf("\n..........Iniciando cadastro de questões..........\n");

        		do{
        			if(heap_cheia(fila_questoes) == 0){//verifica se ainda tem espaço para dicionar questoes 
        				heap_insere(fila_questoes);
        				limpa_tela();
        				printf("Deseja inserir mais questões? [S/N]: \n");
        					test = le_string()[0];
        			}
        			else{
        				printf("Numero maximo de questões atingido!\n");
        					break;
        			}
        		}while(test == 's' || test == 'S');
        	}

        	break;



        	case 2:
        		printf("\n..........Efetuar cadastro..........\n");
        		printf("Insira um login:. ");
        			login = le_string();
        		usuario_logado = usuario_cadastro_cria(tab_user,login);// para ter acesso ao usuario que foi criado agora
        		if(usuario_logado != NULL){
        			printf("Cadastro criado com sucesso!\n");
        			usuario_hash_insere(tab_user,usuario_logado);
        		}

        	/*	Ususario ja cadastrado, agora tem acesso ao sistema [ aluno ou professor]	*/

        	if(usuario_perfil(usuario_logado) == 0){//ALUNO
        		printf("\n..........Acesso básico.........\n");
        		printf("\n..........Iniciando QUIZ........\n");
        		//limpa_tela();

                int size = heap_size(fila_questoes);
        		int pont_atual = 0;
                int i;

        		for(i = 0 ; i<size; i++){
        			printf("\n[%2d] Questão: ",i);
        			pont_atual += imprime_questao(heap_pos(i)); // essa funçao irá retornar 10(se o usuario acertar a questão)
       				//limpa_tela();									   // ou 0(se errar a questão)									
        		}
        		usuario_pontuacao_set(usuario_logado, pont_atual);
        		hanking_insere(tab_hanking,usuario_nome(usuario_logado),pont_atual);//insere no hanking

        		printf("\n..........Fim do Quiz..........\n");
        		printf("Iniciando processamento de respostas...\n");
        		printf("Calculando pontuação...\n");
        		printf("pontuação obtida no teste: %2d%%\n",usuario_pontuacao(usuario_logado));
        		printf("\n\n..........Encerrando QUIZ..........\n\n");
        	}
        	else if(usuario_perfil(usuario_logado) == 1){//PROFESSOR
        		printf("\n..........Acesso avançado.........................\n");
        		printf("\n..........Iniciando cadastro de questões..........\n");

        		do{
        			if(heap_cheia(fila_questoes) == 0){
        				heap_insere(fila_questoes);
        				limpa_tela();
        				printf("Deseja inserir mais questões? [S/N]: \n");
        					test = le_string()[0];
        			}
        			else{
        				printf("Numero maximo de questões atingido!\n");
        					break;
        			}
        		}while(test == 's' || test == 'S');
        	}
        	break;




        	case 3:
        		printf("\n..........Hanking..........\n");
        		hanking_imprime(tab_hanking);
        		break;



        	case 4:
        		usuario_cadastro_salva(fp_usuarios,tab_user);
						printf("1\n");
        		hanking_salva(fp_hanking,tab_hanking);
						printf("2\n");
        		questoes_salva(fp_questoes,fila_questoes);
						printf("3\n");
        		printf("\n..........Encerrando sistema..........\n");
        		msg_despedida(DESPEDIDA);
        		exit(1);
                break;
        }

	}while(opcao != 4);


	fclose(fp_questoes);
	fclose(fp_usuarios);
	fclose(fp_hanking);


    return 0;
}
