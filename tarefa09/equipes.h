typedef struct No {
    struct No *prox;
    struct No *ant;
    int alt;
    int inicio;         // 1 = True; 0 = False 
} No;
typedef struct No * p_no;

/*Adiciona elementos a uma lista duplamente ligada inicialmente*/
p_no adiciona(p_no lista, int alt);

/*Liga cada ponta da lista que foi montada anteriormente*/
p_no arrumar_circular(p_no lista);

/*Vai na lista circular e roda da esquerda para a direita
até encontrar o elemento desejado*/
p_no acha_elemento_time1(p_no lista, int dado, p_no time1);

/*Vai na lista circular e roda da direitra para a esquerda
até encontrar o elemento desejado*/
p_no acha_elemento_time2(p_no lista, int dado, p_no time2);

/*Adiciona o elemente numa lista duplamente correspondente 
ao time de forma ordenada*/
p_no adiciona_time(p_no lista, int alt);

/*Remove da lista circular o elemento que foi redirecionado 
para a lista de time */
p_no remove_elemento(p_no lista, p_no elemento);

void destroi(p_no lista);

void imprime_time(p_no time);

p_no cria_lista();