typedef struct Navios {
    struct Navios *prox;   
    char nome[21], objetivo[11], carga[21];
    int quant_max, quant_atual;
} Navios;
typedef struct Navios * p_nv; 

/*Ponteiro que ponta para o inicio e fim da fila*/
typedef struct {
    p_nv ini, fim;
} Fila;
typedef Fila * p_fila;

typedef struct Doca {
    struct Doca *prox;
    char carga[21];
} Doca;
typedef struct Doca * p_doca; 

/*Ponteiro que ponta para o topo e fim da pilha*/
typedef struct {
    p_doca topo, fim;
    int qtd_max, qtd_atual; 
} Pilha;
typedef Pilha * p_pilha;

p_fila cria_fila();

/*monsta lista-ligada de navios*/
void monta_fila(p_fila fila, char nome[], char objetivo[], char carga[], int quant);

/*liga cada ponta da lista para formar uma cicular*/
p_fila liga_circular(p_fila fila);

/*remove uma navio da lista*/
void remove_fila(p_fila fila, p_nv navio);

/*adiciona cada elemento na pilha da doca correspondente*/
p_pilha adiciona_doca(p_pilha pilha, char carga[]);

/*remove elemento do topo da pilha*/
p_pilha remove_doca(p_pilha pilha);

/*manda navio para o fim da fila*/
p_fila manda_para_o_fim(p_fila fila);

/*tira elemento da pilha da doca e coloca no navio*/
p_pilha carrega_navio(p_nv navio, p_pilha pilha, int n_doca);

/*tira elemento do navio e coloca na pilha da doca*/
p_pilha descarrega_navio(p_nv navio, p_pilha pilha, int n_doca);

/*redireciona para as funçoes que conferem a capacidade e demanda das docas*/
int casca_confere(p_fila fila_navios, int num_navios, p_pilha fila_docas[], int num_docas);

/*confere se tem espaço nas docas e se tem algum navio para carregar ainda*/
int confere_capacidade(p_fila navios, p_pilha docas[], int qtd_docas);

/*confere se tem alguma doca com a carga de algum navio e se ainda há navios para descarregar*/
int confere_demanda(p_fila navios, int qtd_navios, p_pilha lista_docas[], int qtd_docas);

void destroi_docas(p_pilha docas[], int qtd_docas);

void destroi_navios(p_fila navios);