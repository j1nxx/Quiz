#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "interacao.h"
#include "usuario.h"
#define N 101

#ifndef TAMANHO_MAXIMO_LINHA
#define TAMANHO_MAXIMO_LINHA 256
#endif 

	/* usuario = PROF */

	/*    USUARIO   */

		struct user{
			int pontuacao;
			int perfil; // 1- para aluno  0- para professor
			char nome[121];
			char login[11];
			char senha[9]; 
			
		};
		
		struct userhash {
		    int n;
		    int dim;
			User** v;  /* vetor de ponteiros para a info armazenada */
		};
		
	/*  HASH    */	
		
	static void redimensiona(UserHash* tab){
		int max_ant = tab->dim;
		User** ant = tab->v;
		tab->n = 0;
		tab->dim *= 1.947;
		tab->v = (User**)malloc(tab->dim*sizeof(User*));
		int i;
		for(i = 0;i < tab->dim; i++)
			tab->v[i] = NULL;
		for(i = 0; i < max_ant; i++){
		    if(ant[i]){
		        usuario_hash_insere(tab,ant[i]);    
		    }
		}
		free(ant);
    }

	static int usuario_hash(char* sen){
		int aux = atoi(sen); // converte char em int, para calcular o hash.
		return(aux % N);		/* retorna a chave, que serve de indice para o vetor */ 
	}	

	static char* removeNewLine(char* str)
	{
		size_t len = strlen(str);
		if (len > 0 && str[len-1] == '\n') 
			str[--len] = '\0';
		return str;
	}

	int usuario_perfil(User* user)
	{
		return user->perfil;
	}

	int usuario_pontuacao(User* user)
	{
		return user->pontuacao;
	}

	char* usuario_nome(User* user)
	{
		return user->nome;	
	}

	void usuario_pontuacao_set(User* user, int pontuacao)
	{
		user->pontuacao = pontuacao;
	}


	UserHash* usuario_hash_cria(void){
		UserHash* tab = (UserHash*)malloc(sizeof(UserHash));
		tab->n = 0;
		tab->dim = N;
		tab->v = (User**)malloc(N*sizeof(User*));
		int i;
		for(i = 0; i < N; i++ )
			tab->v[i] = NULL;
		return tab;
	}
	
	void usuario_hash_libera(UserHash* tab){
		int i;
		for(i = tab->dim; i < N; i++ )
			free(tab->v[i]);
		free(tab->v);
		free(tab);
	}
	
	
	User* usuario_hash_busca(UserHash* tab, char* login){
		int h = usuario_hash(login);
		char *aux = (char*)malloc(11*sizeof(char));
		aux = login;
		while(tab->v[h] != NULL) {
			if(strcmp(tab->v[h]->login,aux) == 0)
				return tab->v[h];
			h = (h+1) % N; /* incremento circular [tratamento de colisão] */
		}
		return NULL;
	}
	
	User* usuario_hash_insere(UserHash* tab, User* usuario){
		
		if(tab->n > 0.75*tab->dim)
			redimensiona(tab);// caso o limite de 75% seja atingido
			
		int h = usuario_hash(usuario->login); // calcula a posição a ser inserido(indice)
		while(tab->v[h] != NULL) 
			h = (h+1)%tab->dim;
		
		tab->v[h] = usuario;
		tab->n++;
		printf("inseriu");
		return usuario;	
	}
    

	/*	LOGIN	*/

	User* usuario_valida_cadastro(UserHash* tab, char* lg, char* key){		// retorna (Usuario) se achar o usuario buscado  ou  NULL se não encontrar o usuario.
		User* p = usuario_hash_busca(tab,lg);						// se não encontrar o usuario com os dados passados*/
			if(p != NULL) {
				if(p->senha == key)
					return p;
				else {
					printf("nao buscou\n");
					return NULL;
				}
			}
	}


	int usuario_ler_login(UserHash* tab,char* lg){   // retorna 1 se existir um login igual ao passado ou 0 senão.
		User** p = tab->v;
		int i;
		for(i = 0; i < tab->n; i++){
			if(strcmp(lg,p[i]->login) == 0)
				return 1;
		}
		return 0;
	}


	User* usuario_cadastro_cria(UserHash* tab, char* lg){
		int chave;  /* variavel para receber o valor (1 ou 0) de confirmação de login */
		User* novo = (User*)malloc(sizeof(User));
		chave = usuario_ler_login(tab,lg);

		if(chave == 1)
		{
			printf("\nLogin ja existente.\n");// se o login ja existe, solicita um novo
			do{	
				printf("\nInsira um login valido:. ");
				lg = le_string();
				chave = usuario_ler_login(tab,lg);//verifica se o login iserido é valido
				limpa_tela();
			}while(chave!=1);// enquanto a cheve for 0(login ja existe) o laço não será desfeito
		}
		else
		{
	        strcpy(novo->login, lg);
			printf("Nome: ");
				strcpy(novo->nome, le_string());
			printf("Senha: ");
				strcpy(novo->senha, le_string());
			printf("[0] Aluno / [1] Professor\n");
				scanf("%d",&novo->perfil);
	        novo->pontuacao = 0; //inicia a pontuacao do hanking com 0
		}
		return usuario_hash_insere(tab,novo);
	}
	
	UserHash* usuario_cadastro_carrega(FILE* arqv){
		int pontuacao = 0;
		int perfil = 0;
		char nome[121];
		char login[11];
		char senha[9];
		char linha_completa[TAMANHO_MAXIMO_LINHA];

		UserHash* h = usuario_hash_cria();

		if(arqv == NULL){
		    return h; // se arquivo nao encontrado cria vazio pra depois salvar
		}

		while( fgets(linha_completa, TAMANHO_MAXIMO_LINHA, arqv) != NULL)
		{
			if(strcmp(linha_completa,"[USUARIO_NO]\n") == 0)
			{
				fgets(linha_completa, TAMANHO_MAXIMO_LINHA, arqv); // ler nome
				sscanf(linha_completa, "Nome: %[^\n]", nome);

				fgets(linha_completa, TAMANHO_MAXIMO_LINHA, arqv); // ler login
				sscanf(linha_completa, "Login: %[^\n]", login);

				fgets(linha_completa, TAMANHO_MAXIMO_LINHA, arqv); // ler senha
				sscanf(linha_completa, "Senha: %[^\n]", senha);

				fgets(linha_completa, TAMANHO_MAXIMO_LINHA, arqv); // ler pontuacao
				sscanf(linha_completa, "Pontuação: %d", &pontuacao);

				fgets(linha_completa, TAMANHO_MAXIMO_LINHA, arqv); // ler perfil
				sscanf(linha_completa, "Perfil: %d", &perfil);

				/* cria uma estrutura User para passar pra hash_insere	*/

				User* aux = (User*)malloc(sizeof(User));
	        	strcpy(aux->nome,removeNewLine(nome));
	        	strcpy(aux->login,removeNewLine(login));
	        	strcpy(aux->senha,removeNewLine(senha));
	        	aux->pontuacao = pontuacao;
	        	aux->perfil = perfil;
	        	       
				usuario_hash_insere(h, aux);
			}
		}

		fclose(arqv);

		return h;
	}
	
	void usuario_cadastro_salva(FILE* fp, UserHash* hash){
		if(fp != NULL && hash != NULL) {
			int i;
			for(i = 0; i < hash->n; i++){
				fprintf(fp,"\n[USUARIO_NO]\n");
				fprintf(fp,"Nome: %s\n", removeNewLine(hash->v[i]->nome));
				fprintf(fp,"Login: %s\n", removeNewLine(hash->v[i]->login));
	        	fprintf(fp,"Senha: %s\n", removeNewLine(hash->v[i]->senha));
	        	fprintf(fp,"Pontuação: %d\n", hash->v[i]->pontuacao);
	        	fprintf(fp,"Perfil: %d\n",hash->v[i]->perfil);
	        }
	    }
	}


		