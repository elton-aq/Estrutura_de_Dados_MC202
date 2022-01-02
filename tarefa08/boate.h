typedef struct No {
    struct No *prox;
    int rgt, ltn;           // se esta com a lanterna ltn = 1, se não ltn = 0
    char pfs[26], vcn[13];     
} No;

typedef struct No * p_no;

p_no cria_lista();

/* Adiciona a pessoas que podem entrar no começo da fila */
p_no adiciona_comeco(p_no pessoa, int rgt, char pfs[], char vcn[]);

/* Adiciona funcionarios */
p_no adiciona_fim(p_no pessoa, int rgt, char pfs[], char vcn[]);

/* Adiciona pessoas comuns que entram com a lanterna */
p_no adiciona_na_lanterna(p_no pessoa, int rgt, char pfs[], char vcn[]);

/* Remove pessoas não vacinadas quando o fiscal entra */
void remove_pessoa(p_no pessoa);

/* garante que todas as pessoas não vacinadas depois do 
fiscal estejam fora da fila*/
void remove_pessoa_final(p_no pessoa);

/* Acha lanterna e zera */  
void acha_lanterna(p_no pessoa);

void imprime(p_no pessoa);

void destroi(p_no pessoa);