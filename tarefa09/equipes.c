#include <stdio.h>
#include <stdlib.h>
#include "equipes.h"
    
p_no adiciona(p_no lista, int alt) {
    p_no novo;
    novo = malloc(sizeof(No));
    
    if(lista != NULL) { 
        p_no aux = lista;
        novo->inicio = 0;
        novo->alt = alt;
        
        while(aux->prox != NULL) {
            aux = aux->prox;
        }

        aux->prox = novo;
        novo->ant = aux;
        novo->prox = NULL;    
        return lista;
    
    } else {
        novo->inicio = 1;
        novo->alt = alt;
        novo->prox = NULL;
        return novo;
    }
} 

p_no adiciona_time(p_no lista, int alt) {
    p_no novo, aux = lista;
    novo = malloc(sizeof(No));
    
    if(lista != NULL) { 
        novo->inicio = 0;
        novo->alt = alt;
        
        while(aux->ant != NULL) {
            aux = aux->ant;
        }

        while(aux->prox != NULL) {    
            if (aux->alt >= novo->alt) {   
                novo->prox = aux;
                novo->ant = aux->ant;
                if(aux->ant != NULL) {
                    p_no aux2;
                    aux2 = aux->ant; 
                    aux2->prox = novo;
                } 
                aux->ant = novo;
                return novo;
            } else {
                aux = aux->prox;
            }
        }   
        
        if(aux->alt > novo->alt && aux->ant != NULL) {
            p_no aux2;
            aux2 = aux->ant;
            aux->ant = novo;
            aux2->prox = novo;
            novo->prox = aux;
            novo->ant = aux2;
            return aux2;
        } else if(aux->alt > novo->alt && aux->ant == NULL) { 
            novo->ant = NULL;
            novo->prox = aux;
            aux->ant = novo;
            return novo;
        } else {
            novo->ant = aux;
            novo->prox = NULL;
            aux->prox = novo;
            return lista;
        }

    } else {
        novo->inicio = 1;
        novo->alt = alt;
        novo->prox = NULL;
        novo->ant = NULL;
        return novo;
    }
} 

p_no remove_elemento(p_no lista, p_no elemento) {
    p_no aux=elemento, aux2;
    
    if(elemento->prox == elemento && elemento->ant == elemento) {
        free(elemento);
        return NULL;
    }

    aux = elemento->ant;
    aux2 = elemento->prox;
    aux->prox = aux2;
    aux2->ant = aux;

    if (elemento == lista) {
        lista = aux->prox;
    }
    free(elemento);

    return lista;
}

p_no acha_elemento_time1(p_no lista, int dado, p_no time1) {
    int i;
    p_no aux=lista;

    for(i=0; i<dado-1; i++) {
        aux = aux->ant;
    }       
    if(dado == 1){
        aux->prox->inicio = 1;          
    }
    return aux;
}    

p_no acha_elemento_time2(p_no lista, int dado, p_no time2) {
    int i;
    p_no aux=lista;

    for(i=0; i<dado-1; i++) {
        aux = aux->prox;
    };
    if (dado == 1) {
        aux->prox->inicio = 1;
    }
    return aux;
}

void destroi(p_no lista) {
    while(lista->prox != NULL) {
        free(lista->ant);
        lista = lista->prox;
    }
}

void imprime_time(p_no time) {
    p_no aux=time;

    while(aux->ant != NULL) {
        aux = aux->ant;
    }

    while(aux != NULL) {
        printf("%d ", aux->alt);
        aux = aux->prox;
    }
    printf("\n");
}



p_no cria_lista() {
    return NULL;
}

int main() {   
    int i, nmr_amg, altura, dado;
    p_no lista, time1, time2, elemento;

    lista = cria_lista();
    time1 = cria_lista();
    time2 = cria_lista();

    scanf("%d", &nmr_amg);
    for(i=0; i<nmr_amg; i++) {
        scanf("%d", &altura);
        lista = adiciona(lista, altura);
    }

    lista = arrumar_circular(lista);

    for(i=1; i<=nmr_amg; i++) {
        scanf("%d", &dado);
        if(i%2 == 1) {
            elemento = acha_elemento_time1(lista, dado, time1);
            time1 = adiciona_time(time1, elemento->alt);
            lista = remove_elemento(lista, elemento);
        } else {
            elemento = acha_elemento_time2(lista, dado, time2);
            time2 = adiciona_time(time2, elemento->alt);
            lista = remove_elemento(lista, elemento);
        }
    }

    imprime_time(time1);
    imprime_time(time2);

    destroi(time1);
    destroi(time2);

    return 0;
}

p_no arrumar_circular(p_no lista) {
    p_no aux=lista;

    while(aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = lista;
    lista->ant = aux;
    
    return lista;
}