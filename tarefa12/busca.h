typedef struct avr_prc {    //arvore preço (dentro de cada elemento da arvore produto)
    struct avr_prc *esq, *dir;
    char loja[16];
    float valor;
} avr_prc;
typedef struct avr_prc * p_prc;

typedef struct avr_prod {   //arvore produto
    struct avr_prod *esq, *dir;
    avr_prc *prc;
    int cod;
} avr_prod;
typedef struct avr_prod * p_prod;

p_prod cria_arvore_produtos();

p_prod adiciona_produto(p_prod prod, char loja[], int cod, float valor);

/*ordena arvore pelo nome da loja*/
p_prc adiciona_valores(p_prc precos, char loja[], float valor);

/*acha produto e devolve a arvore com os valores dele*/
p_prc acha_produto(p_prod prod, int cod);

/*printa somente se satisfazer as condições de valor*/
void mostra_valores(p_prc precos, int cod, float valor_base, int *ok);

void destroi_produtos(p_prod prod);

void destroi_precos(p_prc precos);
