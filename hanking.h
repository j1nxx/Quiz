#ifndef HANKING_H_INCLUDED
#define HANKING_H_INCLUDED

	typedef struct arv Arv;
	typedef struct arvno ArvNo;

	Arv* hanking_cria(ArvNo* r);
	ArvNo* hanking_criano(char* nome, int pont, ArvNo* esq, ArvNo* dir);
	void hanking_insere(Arv* a, char* nome, int pont);
	void hanking_imprime(Arv* a);
	void hanking_salva(FILE* fp, Arv* arv);
	Arv* hanking_carrega(FILE* arqv);
	
#endif 
