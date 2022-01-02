/*----------------- struct -----------------*/

typedef struct item {
    int id, prio, inc;
} item;

typedef struct FilaPrio {
    item *v;
    int tmn, n;
} FilaPrio;
typedef FilaPrio * p_fila;

/*------------------ defs ------------------*/

#define PAI(i) ((i-1)/2)

#define F_ESQ(i) (2*i+1) /*Filho esquerdo de i*/

#define F_DIR(i) (2*i+2) /*Filho direito de i*/

/*----------------- funções -----------------*/

p_fila cria_fila(int tam);

void insere(p_fila fila, int id, int prio, int inc);

void troca(item *a, item *b);

void sobe_no_heap(p_fila fila, int k);

void desce_no_heap(p_fila fila, int k);

void extrai_maximo(p_fila fila);

p_fila atualiza_prioridades(p_fila fila);

void destroi_fila(p_fila fila);