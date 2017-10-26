#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

typedef struct user User;
typedef struct userhash UserHash;

	UserHash* usuario_hash_cria(void);
	void usuario_hash_libera(UserHash* tab);
	User* usuario_hash_busca(UserHash* tab, char* login);
	User* usuario_hash_insere(UserHash* tab, User* usuario);
	UserHash* usuario_cadastro_carrega(FILE* arqv);
	void usuario_cadastro_salva(FILE* fp, UserHash* hash);
    User* usuario_valida_cadastro(UserHash* tab,char* lg, char* key);
    int usuario_ler_login(UserHash* tab,char* lg);
    User* usuario_cadastro_cria(UserHash* tab, char* lg);

    char* usuario_nome(User* user);
    int usuario_perfil(User* user);
    int usuario_pontuacao(User* user);
    void usuario_pontuacao_set(User* user, int pontuacao);

#endif // USUARIO_H_INCLUDED
