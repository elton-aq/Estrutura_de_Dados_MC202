typedef struct Cdd {    // cdd = cidade
    char nome[51];
    int ppc;            // população
    double fator_c;
} Cdd;
typedef struct Cdd * p_cdd;

typedef struct Grafo {
    double **adj;
    int n;
} Grafo;
typedef struct Grafo * p_grafo;

p_grafo cria_grafo(int n);

int acha_indice(char nome[], Cdd lista[], int tmn); 

double calcula_fator(p_grafo grafo, Cdd cidades[],int indice, int ppc_total);

Cdd* add_ordenado(Cdd cidade, Cdd lista[], int tmn_vetor);

void printa_lista(Cdd lista[], int tmn);

void fw(p_grafo grafo, p_grafo dist);

void destroi_grafos(p_grafo grafo1, p_grafo grafo2);