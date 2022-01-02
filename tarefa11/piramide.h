/*---------arvore----------*/
typedef struct prmd {
    struct prmd *esq, *dir;
    struct prmd *pai;
    double valor;
    int h;       // h = altura
    char nome[21];
} prmd;
typedef struct prmd * p_prmd;
/*---------arvore----------*/

/*----------fila-----------*/
typedef struct Fila {
    struct prmd *prmd;
    struct Fila *prox;
} Fila;
typedef struct Fila * p_fila;

typedef struct ini {
    p_fila ini, fim;
} ini;
typedef ini * p_ini;
/*----------fila-----------*/

p_prmd cria_arvore(char nome[], double valor);

/*função recursiva que encontra o recrutador, adiciona e 
retorna o recrutado*/
p_prmd adiciona_elemento(p_prmd piramide, char recrutador[], char recrutado[], double valor_ini, int altura);

/*Dá os 10% para o recrutado e se necessario também da a 
porcentagem de cada recrutador*/
p_prmd arruma_valores(p_prmd recrutador);

/*volta para a raiz*/
p_prmd raiz(p_prmd elemento);

void printa_arvore(p_prmd arvore);

p_ini cria_fila();

/*encontra os elemento por nivel para enfileira-los*/
void enfileirar(p_ini fila, p_prmd arvore); 

/*insere os elementos encontrados na fila*/
p_fila insere(p_ini fila, p_prmd elemento);

void destroi_fila(p_ini fila);

void destroi_arvore(p_prmd arvore);