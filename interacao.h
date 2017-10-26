#ifndef INTERACAO_H_INCLUDED
#define INTERACAO_H_INCLUDED

void apresenta_programa (char *msg);
void msg_despedida(char *msg);
void limpa_tela(void);
void limpa_buffer(void);
int le_opcao(int menor_valor, int maior_valor);
void apresenta_menu(int n_itens, int menor_opcao,...);
char* le_string(void);

#endif // INTERACAO_H_INCLUDED