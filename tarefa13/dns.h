enum Cor {VERMELHO, PRETO};

typedef struct abb {
    char dominio[101], servidor[16];
    enum Cor cor;
    struct abb *esq, *dir;
} abb;
typedef struct abb * p_abb;

typedef struct user {
    char servidor[16];
    int buscas;
    enum Cor cor;
    struct user *esq, *dir;
} user;
typedef struct user * p_user;

/*---------------------------------------------------------------*/

p_abb cria_avr();

/*confere se o nó é vermelho*/
int vermelho_abb(p_abb elemento);

/*confere se o nó é preto*/
int preto_abb(p_abb elemento); 

/*insere elemento na arvore de dominios*/
p_abb inserir_abb(p_abb arvore, char dominio[], char servidor[]);

/*mantem raiz da arvore na cor preta*/
p_abb mantem_preto_abb(p_abb arvore);

p_abb roda_esquerda_abb(p_abb arvore);

p_abb roda_direita_abb(p_abb arvore);

void sobe_vermelho_abb(p_abb arvore); 

void destroi_arvore(p_abb arvore);

/*---------------------------------------------------------------*/

p_user cria_users();

/*confere se o nó é vermelho*/
int vermelho_user(p_user elemento);

/*confere se o nó é preto*/
int preto_user(p_user elemento);

/*insere elemento na arvore de usuarios*/
p_user inserir_user(p_user arvore, char servidor[], int buscas);

/*mantem raiz da arvore na cor preta*/
p_user mantem_preto_user(p_user arvore); 

p_user roda_esquerda_user(p_user arvore); 

p_user roda_direita_user(p_user arvore);

void sobe_vermelho_user(p_user arvore); 

void destroi_usuarios(p_user usuario);
/*--------------------------------------------------------------*/

/*procura e retorna o nó do user na arvore de usuarios
e caso ele ainda não esteja contido, retorna NULL */
p_user acha_user(p_user arvore, char servidor[]);

/*busca dominio pedido do usuario na arvore de dominios*/
void busca(p_abb avr_dominios, p_user usuario, char dominio[]);