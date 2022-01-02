#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "busca.h"

int main() {
    int i, qtd, cod, ok;
    float valor, valor_base;    
    char loja[16];
    p_prod produtos;
    p_prc valores;

    produtos = cria_arvore_produtos();

    scanf("%d", &qtd);    
    for(i=0; i<qtd; i++) { 
        scanf("%s %d %f", loja, &cod, &valor);
        produtos = adiciona_produto(produtos, loja, cod, valor);
    }
    scanf("%d", &qtd);
    for(i=0; i<qtd; i++) {
        ok=0;
        scanf("%d %f", &cod, &valor_base);
        printf("OFERTAS para %d:\n", cod);
        valores = acha_produto(produtos, cod);
        if(valores != NULL)
            mostra_valores(valores, cod, valor_base, &ok);
        if(ok==0 || valores == NULL)
            printf("nenhuma boa oferta foi encontrada\n");
        else
            printf("\n");
    }
    destroi_produtos(produtos);

    return 0;
}

/* fazer arvore com as produto 
ordenadas e apontando para outra
arvore que é das lojas e valores */

p_prod cria_arvore_produtos() {      
    return NULL;
}

p_prod adiciona_produto(p_prod prod, char loja[], int cod, float valor) {
    if(prod == NULL) {
        p_prod novo;
        novo = malloc(sizeof(avr_prc));
        novo->cod = cod;
        novo->esq = novo->dir = NULL;
        novo->prc = NULL;
        novo->prc = adiciona_valores(novo->prc, loja, valor);
        return novo;
    } else {
        if(prod->cod > cod) {
            prod->esq = adiciona_produto(prod->esq, loja, cod, valor);
            return prod;
        } else if(prod->cod < cod) {
            prod->dir = adiciona_produto(prod->dir, loja, cod, valor);
            return prod;
        } else {
            prod->prc = adiciona_valores(prod->prc, loja, valor);
            return prod;
        }
    }
}

p_prc adiciona_valores(p_prc precos, char loja[], float valor) {
    if(precos == NULL) {
        p_prc novo;
        novo = malloc(sizeof(avr_prc));
        novo->esq = novo->dir = NULL;
        novo->valor = valor;
        strcpy(novo->loja, loja);
        return novo; 
    } else {
        if(strcmp(precos->loja, loja) > 0) {
            precos->esq = adiciona_valores(precos->esq, loja, valor);
            return precos;
        } else {
            precos->dir = adiciona_valores(precos->dir, loja, valor);
            return precos;
        }
    }
}

p_prc acha_produto(p_prod prod, int cod) {
    if(prod == NULL) {
        return NULL;
    } else if(prod->cod == cod) {
        return prod->prc;
    } else {
        if(prod->cod > cod)
            return acha_produto(prod->esq, cod);
        else    
            return acha_produto(prod->dir, cod); 
    }
}

void mostra_valores(p_prc precos, int cod, float valor_base, int *ok) {
    if(precos->esq != NULL)
        mostra_valores(precos->esq, cod, valor_base, ok);
    if(precos->valor <= valor_base + (valor_base * 0.1) && precos->valor >= valor_base/2) {
        printf("%s %d %.2f\n", precos->loja, cod, precos ->valor);
        *ok += 1;
    }
    if(precos->dir != NULL)
        mostra_valores(precos->dir, cod, valor_base, ok); 
}

void destroi_produtos(p_prod prod) { 
    if(prod->esq != NULL)
        destroi_produtos(prod->esq);   
    if(prod->dir != NULL)
        destroi_produtos(prod->dir);
    destroi_precos(prod->prc);
    free(prod);
}

void destroi_precos(p_prc precos) {
    if(precos->esq != NULL)
        destroi_precos(precos->esq);   
    if(precos->dir != NULL)
        destroi_precos(precos->dir);
    free(precos);
}