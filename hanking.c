	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "hanking.h"

	#ifndef TAMANHO_MAXIMO_LINHA
	#define TAMANHO_MAXIMO_LINHA 256
	#endif 

	struct arv{
		ArvNo* raiz;
	};

	struct arvno{
		char nome[81];
			int pont;
		struct arvno *esq;
		struct arvno *dir;
	};

	/*Arv* arv_cria(void){
		Arv* nova = (Arv*)malloc(sizeof(Arv));
		nova->raiz = NULL;
		return nova;
	}*/

	ArvNo* hanking_criano(char* nome, int pont, ArvNo* esq, ArvNo* dir){
		ArvNo* p = (ArvNo*)malloc(sizeof(ArvNo));
		p->pont = pont;
		strcpy(p->nome,nome);
		p->esq = esq;
		p->dir = dir;
		return p;
	}

	Arv *hanking_cria(ArvNo* r){
		Arv* a = (Arv*)malloc(sizeof(Arv));
		a->raiz = r;
		return a;
	}

	static ArvNo* insere(ArvNo* r, char* nome, int pont){
		if(r==NULL){
			r = hanking_criano(nome,pont,NULL,NULL);
			/*r->pont = pont;
			strcpy(r->nome,nome);
			r->esq = r->dir = NULL;*/
		}
		else if(pont < r->pont){
			r->esq = insere(r->esq,nome,pont);
		}
		else{
			r->dir = insere(r->dir,nome,pont);
		}
		return r;
	}

	void hanking_insere(Arv* a, char* nome, int pont){
		a->raiz = insere(a->raiz,nome,pont);
	}

	static void imprime(ArvNo* r){
			if(r!=NULL){
				imprime(r->dir);
				printf(" %s: %d\n",r->nome,r->pont);
				imprime(r->esq);
			}
	}

	void hanking_imprime(Arv* a){
		imprime(a->raiz);
	}

	/*ERRO DE SEGMENTAÇÃO */
	Arv* hanking_carrega(FILE* arqv){

		char linha_completa[TAMANHO_MAXIMO_LINHA];
		char nome[121];
		int pont;

		Arv* h = (Arv*)malloc(sizeof(Arv));
		h->raiz = NULL;

		if(arqv == NULL){
			return h; // se arquivo nao encontrado cria vazio pra depois salvar
		}

		while( fgets(linha_completa, TAMANHO_MAXIMO_LINHA, arqv) != NULL)
		{
			sscanf(linha_completa, "[HANKING_NO] %d %[^\n]", &pont, nome);
			hanking_insere(h, nome, pont);
		}

		//fclose(arqv);

		return h;
	}		

	static void salva(FILE* fp, ArvNo* no){

		if(no != NULL) {

			/*fprintf(stdout,"[HANKING_NO] ");
			fprintf(stdout,"%d ", no->pont);
			fprintf(stdout,"%s\n",no->nome);*/
		
			fprintf(fp,"[HANKING_NO] ");
			fprintf(fp,"%d ", no->pont);
			fprintf(fp,"%s\n",no->nome);
		

			salva(fp, no->esq);
			salva(fp, no->dir);
		}
	}
	
	void hanking_salva(FILE* fp,Arv* arv){
		salva(fp, arv->raiz);
		fclose(fp);
	}

