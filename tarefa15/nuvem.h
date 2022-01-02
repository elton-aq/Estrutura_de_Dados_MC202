typedef struct ll {        /* ll = lista ligada */
    struct ll *prox;
    char palavra[50];
    int quant;
} ll;
typedef ll * p_ll;

typedef struct hash {
    p_ll *vetor;
} hash;
typedef hash * p_hash;

/* ---------------- funções ---------------- */

/* Manda calcular o indice e adicionar no hash correspondente */
void casca(char string[], p_hash t_hash, int tmn_vetor);

/* Calcula indice do elemento no hash */
int calcula_indice(char string[], int tmn_vetor);

/* Busca palavra na lista ligada da posição i do hash e se 
não encontrar adicona a nova palavra com sua quantidade 
inicial igual a 1, alem disso retorna a lista ligada da 
posição do hash */
p_ll adiciona_lista_ligada(p_ll inicio, char string[]);

/* Caso a posição i do hash ainda não tenha palavras, 
a lista ligada é criada */
p_ll cria_lista_ligada(p_ll inicio, char string[]);

/* Procura palavra no hash das stop words e retorna 
um valor booleano */
int eh_sw(char string[], p_hash t_sw, int tmn_sw);

/* Retira todos os elementos que não são letras e converte 
elas de maiuscula para minuscula se necessario */
void arruma_string(char string[]);

/* Passa por todos os elementos do hash de palavras redirecionando-os 
para a função insere_ordenado */
void add_na_lista(ll lista[], p_hash palavras, int tmn_palavras);

/* Recebe um elemento e insere numa posição já ordenada de um vetor */
ll* insere_ordenado(ll vetor[], ll elemento, int tmn_vetor);

/* printa os 50 elementos do vetor ordenado */
void printa(ll lista[], int tmn);

void destroi_hash(p_hash hash, int tmn_hash);

void destroi_ll(p_ll inicio);