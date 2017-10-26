	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <assert.h>
	#include <string.h>
	#include "questoes.h"
	#include "interacao.h"
	#define pai(i) (((i)-1)/2)
	#define esq(i) (2*(i)+1)
	#define dir(i) (2*(i)+2)


	#define N 20

	struct heap{
		int n; // Número de elementos na lista, utilizado para se alcançar seus índices
		int nmax; // Total de elementos máximos no vetor
		struct question** v;
	};


	struct question{
		int correct;
		int priori;
		char p[10000];
		char a[1000],b[1000],c[1000],d[1000],e[1000];
	};

	Heap* heap_cria(int nmax){
		Heap* h = (Heap*)malloc(nmax*sizeof(Heap));
		int i;

		if(h == NULL){
			printf("Erro de alocacao");
			exit (1);
		}

		h->n = 0;
		h->nmax = nmax;
		h->v = (Question**)malloc(N*sizeof(Question*));

		if(h->v == NULL){
			printf("erro de alocacao");
			exit (1);
		}


		for(i = 0; i < N; i++){
			//h->v[i] = NULL; // Inicializará com NULL para economizar memória
			h->v[i] = (Question*)malloc(sizeof(Question));
		}

		return h;
	}

	void heap_libera(Heap* h){
		free(h->v);
		free(h);
	}

	static void troca(Heap* h, int i, int j){
		Question* tmp = h->v[i];
		h->v[i] = h->v[j];
		h->v[j] = tmp;
	}

	static void sobe(Heap* h, int i){
		while(i > 0){
			int p = pai(i);
			if(h->v[p]->priori > h->v[i]->priori)
				break;
			troca(h,p,i);
			i = p;
		}
	}

	static void desce(Heap *h, int i){
		int c = esq(i);
		while(c < h->n){		/*enquanto filho for valido*/
			int c2 = dir(i);
			if(c2 < h->n &&			/*filho da direita nao pode existir*/
				(h->v[c2]->priori > h->v[c]->priori))	/*se existir testa se é maior*/
				c = c2;
			if(h->v[c]->priori < h->v[i]->priori)
				break;
		}
		troca(h,i,c);
		i = c;
		c = esq(i);
	}

	void heap_insere(Heap* h){ // cria uma questão!!!!
		char cha[1000];
		Question* novo = (Question*)malloc(sizeof(Question));
		if(novo == NULL){
			printf("Erro de alocacao\n");
		exit(1);
		}
		
		printf("\nDigite o corpo da pergunta: ");
			strcpy(novo->p, le_string());
		printf("\nDigite a alternativa a) ");
			strcpy(novo->a, le_string());
		printf("\nDigite a alternativa b) ");
			strcpy(novo->b, le_string());
		printf("\nDigite a alternativa c) ");
			strcpy(novo->c, le_string());
		printf("\nDigite a alternativa d) ");
			strcpy(novo->d, le_string());
		printf("\nDigite a alternativa e) ");
			strcpy(novo->e, le_string());
		printf("\nAlternativa correta: [1]A - [2]b - [3]C - [4]D - [5]E\n");
			scanf("%d", &novo->correct);
		printf("\nNivel de priorirdade de 1 a 5");
			scanf("%d",&novo->priori);

		h->v[h->n++] = novo;
		sobe(h,h->n-1);
	}

	/*
	int heap_verifica(Heap* h){
	int i;
		for(i=0; i<h->n/2; i++){
			int l = esq(i);
			int r = dir(i);
		if(h->v[l] > h->v[i])
			return 0;
		if(r < h->n && h->v[r] > h->v[i])
			return 0;
		}
	return 1;
	}
	*/

	Heap* heap_constroi(int n, Question** v){
		int i;
		Heap* h = (Heap*)malloc(sizeof(Heap));
		h->n = n;
		h->nmax = n;
		h->v = (Question**)malloc(h->nmax*sizeof(Question*));
		memcpy(h->v,v,n*sizeof(int));

		/*for(i=n/2-1; i>=0; --i)
			desce(h,i);*/
		
		return h;
	}


	int imprime_questao(Question* q){
		int resposta;
		int pontuacao_user = 0;

		if(q == NULL){
			exit(1);
		}
		
		printf("\n[Questão]: %s", q->p);
		printf("\n[1-a]%s", q->a);
		printf("\n[2-b]%s", q->b);
		printf("\n[3-c]%s", q->c);
		printf("\n[4-d]%s", q->d);
		printf("\n[5-e]%s", q->e);
		printf("\n>>Digite a resposta correta: ");
		scanf("%d", &resposta);

		if(q->correct == resposta) 
			pontuacao_user = 10;

		return pontuacao_user;
	}

	Heap* heap_carrega(FILE* fp)
	{	
		char linha[1000], alt_a[1000], alt_b[1000], alt_c[1000], alt_d[1000], alt_e[1000];
		int correta;
		
		Heap* heap_questoes = heap_cria(N);
		int i = 0;//heap_questoes->n;
		FILE* arqv = fp;
		
		if(arqv != NULL){
//			while(fscanf(arqv,"%*s",linha)!=EOF){
				while(fgets(linha, 1000, arqv)){
					//printf("Linha: %s\n", linha);
					/*fscanf(arqv,"%*s: %s",alt_a);
					fscanf(arqv,"%*s: %s",alt_b);
					fscanf(arqv,"%*s: %s",alt_c);
					fscanf(arqv,"%*s: %s",alt_d);
					fscanf(arqv,"%*s: %s",alt_e);
					fscanf(arqv,"%*s: %d",correta);*/
					fgets(alt_a, 1000, arqv);
					fgets(alt_b, 1000, arqv);
					fgets(alt_c, 1000, arqv);
					fgets(alt_d, 1000, arqv);
					fgets(alt_e, 1000, arqv);

					/*printf("%s\n",alt_a);
					printf("%s\n",alt_b);
					printf("%s\n",alt_c);
					printf("%s\n",alt_d);
					printf("%s\n",alt_e);
					printf("	%d\n",correta);*/

					strcpy(heap_questoes->v[i]->p,linha);
					strcpy(heap_questoes->v[i]->a,alt_a);
					strcpy(heap_questoes->v[i]->b,alt_b);
					strcpy(heap_questoes->v[i]->c,alt_c);
					strcpy(heap_questoes->v[i]->d,alt_d);
					strcpy(heap_questoes->v[i]->e,alt_e);
					heap_questoes->v[i]->correct = correta;
					i++;
				}
			
			heap_questoes->n = i;
			heap_constroi(i,heap_questoes->v);
		}

		return heap_questoes;
	}


	void questoes_salva(FILE* fp,Heap* fila){
		int i;
		Question** aux = fila->v;

		for(i = 0; i < fila->n; i++){
			/*fprintf(stdout,"\n[QUESTÃO]: %s",aux[i]->p);
			fprintf(stdout,"\n[1-A]: %s",aux[i]->a);
			fprintf(stdout,"\n[2-B]: %s",aux[i]->b);
			fprintf(stdout,"\n[3-C]: %s",aux[i]->c);
			fprintf(stdout,"\n[4-]: %s",aux[i]->d);
			fprintf(stdout,"\n[alternativa E]: %s",aux[i]->e);
			fprintf(stdout,"\n[alternativa correta]: %d\n",aux[i]->correct);*/

			fprintf(fp,"\n[QUESTÃO]: %s",aux[i]->p);
			fprintf(fp,"\n[1-A]: %s",aux[i]->a);
			fprintf(fp,"\n[2-B]: %s",aux[i]->b);
			fprintf(fp,"\n[3-C]: %s",aux[i]->c);
			fprintf(fp,"\n[4-]: %s",aux[i]->d);
			fprintf(fp,"\n[alternativa E]: %s",aux[i]->e);
			fprintf(fp,"\n[alternativa correta]: %d\n",aux[i]->correct);
    }
	}

	int heap_size(Heap* h)
	{
		return h->n;
	}

	int heap_cheia(Heap* h)
	{
		return h->nmax == h->n;
	}

	Question* heap_pos(int i)
	{

		return NULL;  // !!!! FALTA IMPLEMENTAR ISSO !!!!
	}


/* criar funcoes - carrega e salva  -  */
		/*Heap* cadastro_carrega(void){
		FILE* arqv = fopen("usuarios.txt", "a+t");
		int pont = (int) malloc(sizeof(int));
		int per =(int)malloc(sizeof(int));
		char* nome = (char*)malloc(121*sizeof(char));
		char* log = (char*)malloc(11*sizeof(char));
		char* sen = (char*)malloc(9*sizeof(char));

		if(arqv == NULL){
		    printf("\nFALHA AO ABRIR ARQUIVO\n");
		    exit(1);
		}

		if(qst == NULL){
		    printf("\nFALHA NA MEMORIA\n");
		    exit(1);
		}

		Hash* h = hash_cria();
		
    while(fscanf(arqv,"%*s: %[^\n]s\n",nome) != EOF){
        fscanf(arqv, "%*s : %s\n"
        			 "%*s : %s\n"
        			 "%*s : %d\n"
        			 "%*s : %d\n",nome,log,sen,pont,per);
        			 
        	/* cria uma estrutura User para passar pra hash_insere	*/
	/*
        	
        	User* aux = (User*)malloc(sizeof(User));
        	strcpy(aux->nome,nome);
        	strcpy(aux->login,log);
        	strcpy(aux->senha,sen);
        	aux->pontuacao = pont;
        	aux->perfil = per;
        	       
			h = hash_insere(h,aux);
		}

		fclose(arqv);

	return h;
	}
	
	void cadastro_salva(FILE* fp,Hash hash){
		int i;
		for(i = 0; i < hash->n; i++){
			fprintf(fp,"Nome : %s\n"
        			 "Login : %s\n"
        			 "Senha : %s\n"
        			 "Pontuação : %d\n"
        			 "Perfil : %d\n",hash->v[i]->nome,hash->v[i]->login,hash->v[i]->senha,hash->v[i]->pontuacao,hash->v[i]->perfil);
        }
	}






	int main(void){

	Heap* h;
	int i;
	float v[N];
	for(i=0; i<N; ++i)
	v[i] = (float)((double)rand()/RAND_MAX);
	h = heap_constroi(N,v);
	assert(heap_verifica(h));

	printf("Digite uma pergunta\n");
	scanf(" %s",h->questions[0]);
	printf()

	imprime(h);
	heap_libera(h);

	return 0;
	}
	**/
