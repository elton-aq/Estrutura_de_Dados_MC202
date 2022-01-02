typedef struct Cela {
    int atb[6]; // atributos
    char nome[31];
} Cela;
typedef struct Cela * p_cela;

typedef struct Grafo {
    int **adj;
    int n;
} Grafo;
typedef struct Grafo * p_grafo;

p_grafo cria_grafo(int tmn);

/* Busca na lista de celas o indice correspondente ao 
personagem da vez (esta sera a cela inicial do personagem) */
int acha_indice(Cela celas[], int tmn, Cela psng);

/* Função que procura possiveis caminhos de tamanho 2 
partindo da cela inicial do personagem */
void monta_adjacencias(Cela celas[], p_grafo grafo, Cela personagem, int indice, int contagem, int i_personagem);

/* confere se a cela atual (cela1) 
pode ir para a outra (cela2) */
int pode_ir(Cela cela1, Cela cela2, int nivel);

/* A função percorre as linhas de cada coluna verificando se são 
comuns para todos, nos casos que elas são, é impresso o nome 
da cela dessa posição correspodente na lista de celas */   
void compara_resultados(p_grafo grafo, int *psng, int quant, Cela *celas);

void destroi_grafo(p_grafo grafo);