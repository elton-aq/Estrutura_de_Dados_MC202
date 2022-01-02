#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "nuvem.h"

int main() {
    int i, quant_palavras, quant_sw;    /*sw = stop words*/
    char palavra[50];
    p_hash t_sw, t_palavras;    /* t_ = tabela_ */
    ll *lista_ord;

    t_palavras = malloc(sizeof(hash));
    t_sw = malloc(sizeof(hash));

    scanf("%d", &quant_palavras);
    t_palavras->vetor = malloc(quant_palavras * sizeof(p_ll));
    lista_ord = malloc(quant_palavras * sizeof(ll));
    for(i=0; i<quant_palavras; i++) {
        t_palavras->vetor[i] = NULL;
    }

    scanf("%d ", &quant_sw);
    t_sw->vetor = malloc(quant_sw * sizeof(p_ll));
    for(i=0; i<quant_sw; i++) {
        t_sw->vetor[i] = NULL;
    }

    for(i=0; i<quant_sw; i++) {
        scanf("%s", palavra);
        casca(palavra, t_sw, quant_sw);
    }
    
    while(scanf("%s", palavra) != EOF) {
        arruma_string(palavra); 
        if(eh_sw(palavra, t_sw, quant_sw) && strlen(palavra) > 1) { 
                casca(palavra, t_palavras, quant_palavras);
        }
    }
    
    add_na_lista(lista_ord, t_palavras, quant_palavras);
    printa(lista_ord, quant_palavras);

    destroi_hash(t_palavras, quant_palavras);
    destroi_hash(t_sw, quant_sw);
    free(lista_ord);

    return 0;
} 

void casca(char string[], p_hash t_hash, int tmn_vetor) {
    int i;

    i = calcula_indice(string, tmn_vetor); 
    if(t_hash->vetor[i] != NULL)
        t_hash->vetor[i] = adiciona_lista_ligada(t_hash->vetor[i], string);
    else
        t_hash->vetor[i] = cria_lista_ligada(t_hash->vetor[i], string);
}

int calcula_indice(char string[], int tmn_vetor) {
    int i, len, indice = 0, ascii;

    len = strlen(string);
    for(i=0; i<len; i++) {
        ascii = string[i];
        indice = (256 * indice + ascii) % tmn_vetor; 
    }
    return indice;
}

p_ll adiciona_lista_ligada(p_ll inicio, char string[]) {
    p_ll aux = inicio, novo;
    
    while(aux->prox != NULL || strcmp(aux->palavra, string) == 0) {
        if(strcmp(aux->palavra, string) == 0) { 
            break;
        } 
        aux = aux->prox;
    }
    if(strcmp(aux->palavra, string) == 0){
        aux->quant ++;
        return inicio;
    } else { 
        novo = malloc(sizeof(ll));
        aux->prox = novo;
        novo->prox = NULL;
        strcpy(novo->palavra, string);
        novo->quant = 1; 
        return inicio;
    } 
}

p_ll cria_lista_ligada(p_ll inicio, char string[]) {
    inicio = malloc(sizeof(ll));
    strcpy(inicio->palavra, string);
    inicio->quant = 1;
    inicio->prox = NULL;
    return inicio;
}

int eh_sw(char string[], p_hash t_hash, int tmn_sw) {
    int i;
    p_ll aux;

    i = calcula_indice(string, tmn_sw);
    aux = t_hash->vetor[i];
    while(aux != NULL) {
        if(strcmp(aux->palavra, string) != 0)
            aux = aux->prox;
        else 
            return 0;
    }
    return 1;
}


void arruma_string(char string[]) {
    int i, j=0, ascii;
    
    char aux[50];

    for(i=0; i<50; i++) {
        if(string[i] == '\000') {
            aux[j] = '\000';
            break;
        }
        ascii = string[i];
        if(ascii >= 65 && ascii <= 90) {
            ascii = tolower(ascii);
            aux[j] = ascii;
            j++;
        } else if(ascii >= 97 && ascii <= 122) {
            aux[j] = string[i];
            j++;
        }
    }
    strcpy(string, aux);
}

void add_na_lista(ll vetor[], p_hash palavras, int tmn_palavras) {
    int i,tmn_atual=0;
    p_ll aux;

    for(i=0; i<tmn_palavras; i++) {
        aux = palavras->vetor[i];
        while(aux != NULL) {    // redireciona os elementos da lista ligada enquanto existirem
            vetor = insere_ordenado(vetor, *aux, tmn_atual);
            tmn_atual++;
            aux = aux->prox;  
        }       
    }
}

ll* insere_ordenado(ll vetor[], ll elemento, int tmn_vetor) {
    int i;

    if(tmn_vetor == 0) {
        vetor[0] = elemento;
        return vetor;
    } 

    for(i=tmn_vetor-1; i>=0; i--) {                 // Percorre de trás para frente o vetor ordenado
        if(vetor[i].quant > elemento.quant) {       // Procura um elemento no vetor maior que o elemento que sera inserido
            vetor[i+1] = elemento;
            break;
        } else if(vetor[i].quant == elemento.quant) {     
            if(strcmp(vetor[i].palavra, elemento.palavra) > 0) {
                vetor[i+1] = vetor[i];
                if(i == 0)
                    vetor[i] = elemento;
            } else {
                vetor[i+1] = elemento;
                break;
            }     
        } else {                                    // Enquanto não encontrar, manda os outros elementos uma posição para trás 
            if(i == 0) {
                vetor[i+1] = vetor[i];
                vetor[i] = elemento;
            } else {
                vetor[i+1] = vetor[i];
            }
        }
    }
    return vetor;
}

void printa(ll lista[], int tmn) {
    int i;

    for(i=0; i<50; i++) {
        printf("\n%s %d", lista[i].palavra, lista[i].quant);
    }
}

void destroi_hash(p_hash hash, int tmn_hash) {
    int i;
    for(i=0; i<tmn_hash; i++) {
        if(hash->vetor[i] != NULL)
            destroi_ll(hash->vetor[i]);
    }
    free(hash->vetor);
    free(hash);
}

void destroi_ll(p_ll inicio) {
    if(inicio->prox != NULL)
        destroi_ll(inicio->prox);  
    free(inicio);
}