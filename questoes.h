#ifndef QUESTOES_H_INCLUDED
#define QUESTOES_H_INCLUDED

typedef struct heap Heap;
typedef struct question Question;

Heap* heap_cria(int nmax);
void heap_libera(Heap* h);
int heap_vazia(Heap* h);
Heap* heap_carrega(FILE* fp);
void heap_insere(Heap* h);
int heap_verifica(Heap* h);
Heap* heap_constroi(int n, Question** v);
int imprime_questao(Question* q);
void questoes_salva(FILE* fp,Heap* fila);

int heap_size(Heap* h);
int heap_cheia(Heap* h);
Question* heap_pos(int i);

#endif 