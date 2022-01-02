#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "piramide.h"

int main() {
    p_prmd piramide;
    p_prmd recrutado;
    double valor;
    char funcao[8], nome1[21], nome2[21];
      
    scanf("%s %s %lf", funcao, nome1, &valor);
    
    piramide = cria_arvore(nome1, valor);
    
    while(scanf("%s %s %s %lf", nome1, funcao, nome2, &valor) != EOF) {
        recrutado = adiciona_elemento(piramide, nome1, nome2, valor, 2);
        piramide = arruma_valores(recrutado->pai);
        printa_arvore(piramide);
    }

    destroi_arvore(piramide);
    return 0;
}

p_prmd cria_arvore(char nome[], double valor) {
    p_prmd topo;
    topo = malloc(sizeof(prmd));
    strcpy(topo->nome, nome);
    topo->valor = valor;
    topo->h = 1;
    topo->dir = topo->esq = topo->pai = NULL;
    printf("Nivel 1: [%s %.2f]\n\n", nome, valor);
    return topo;
}

p_prmd adiciona_elemento(p_prmd piramide, char recrutador[], char recrutado[], double valor_ini, int altura) {
    p_prmd aux;

    if(strcmp(piramide->nome, recrutador) == 0) {
        p_prmd novo;    
        novo = malloc(sizeof(prmd));
        strcpy(novo->nome, recrutado);
        novo->valor = valor_ini;
        novo->h = altura;
        novo->dir = novo->esq = NULL; 
        novo->pai = piramide;
        if (piramide->esq == NULL) {
            piramide->esq = novo;
        } else {
            piramide->dir = novo;
        }
        return novo; 
    }
    if(piramide->esq != NULL) {
        aux = adiciona_elemento(piramide->esq, recrutador, recrutado, valor_ini, altura+1);
        if(aux != NULL)
            return aux;
    } 
    if(piramide->dir != NULL) {
        aux = adiciona_elemento(piramide->dir, recrutador, recrutado, valor_ini, altura+1);
        if(aux != NULL)
            return aux;
    } else {
        return NULL;
    }       
    return NULL;
}

p_prmd arruma_valores(p_prmd recrutador) {
    if(recrutador->dir != NULL && recrutador->esq != NULL) {
        char aux[21];
        int i=5;
        double k;

        recrutador->valor -= recrutador->dir->valor * 0.1;                     //subtrai os 10% no valor do pai (recrutador)
        recrutador->dir->valor += recrutador->dir->valor * 0.1;                //soma os 10% no valor do filho    
        
        recrutador->valor += recrutador->esq->valor * 0.06;                    //soma valores para o pai (recrutador)
        recrutador->valor += recrutador->dir->valor * 0.06;

        recrutador->esq->valor -= recrutador->esq->valor * 0.06;                //subtrai os valores dos filhos
        recrutador->dir->valor -= recrutador->dir->valor * 0.06;

        if(recrutador->pai != NULL) {
            do {
                strcpy(aux, recrutador->nome); 
                recrutador = recrutador->pai;  
                k = i * 0.01;

                if(strcmp(recrutador->esq->nome, aux) == 0) {
                    recrutador->valor += recrutador->esq->valor * k;
                    recrutador->esq->valor -= recrutador->esq->valor * k; 
                } else {
                    recrutador->valor += recrutador->dir->valor * k;
                    recrutador->dir->valor -= recrutador->dir->valor * k;
                } 
                i--;
            } while(recrutador->pai != NULL && i>0);
        }
        return raiz(recrutador);
    } else if(recrutador->esq != NULL) {
        recrutador->valor -= recrutador->esq->valor*0.1;                //subtrai os 10% no valor do pai (recrutador)    
        recrutador->esq->valor += recrutador->esq->valor*0.1;           //soma os 10% no valor do filho    
        return raiz(recrutador);                                        //retorna a raiz 
    } else {
        return raiz(recrutador);
    }
}


p_prmd raiz(p_prmd elemento) {
    while(elemento->pai != NULL) {
        elemento = elemento->pai;
    }
    return elemento;
}

void printa_arvore(p_prmd arvore) {
    p_ini fila;
    int i=1;

    fila = cria_fila();
    enfileirar(fila, arvore);
    
    p_fila termo = fila->ini;
    while(termo != NULL) {
        printf("Nivel %d:", termo->prmd->h);
        while(termo->prmd->h == i) {
            printf(" [%s %.2f]", termo->prmd->nome, termo->prmd->valor);
            if(termo->prox != NULL) {
                termo = termo->prox;
            } else {
                termo = termo->prox;
                break;
            }
        }
        printf("\n");
        i++;
    }
    
    destroi_fila(fila);
    printf("\n");
}

p_ini cria_fila() {
    p_ini novo;
    novo = malloc(sizeof(ini));
    novo->ini = novo->fim = NULL;
    return novo; 
}

void enfileirar(p_ini fila, p_prmd arvore) {
    p_fila novo;

    insere(fila, arvore);
    novo = fila->ini;
    while(1) {
        if(novo->prmd->esq != NULL && novo->prmd->dir != NULL) {
            fila->ini = insere(fila, novo->prmd->esq);
            fila->ini = insere(fila, novo->prmd->dir);
            novo = novo->prox;
        } else if(novo->prmd->esq != NULL) {
            fila->ini = insere(fila, novo->prmd->esq);
            novo = novo->prox;
        } else if(novo->prox == NULL) { 
            break;
        } else {
            novo = novo->prox;
        }
    }
}

p_fila insere(p_ini fila, p_prmd elemento) {
    p_fila aux_ini = fila->ini;
    p_fila aux_fim = fila->fim;
    p_fila novo;
    novo = malloc(sizeof(Fila));

    if(aux_ini == NULL) {
        fila->ini = novo;
        fila->fim = novo;
        novo->prmd = elemento;
        novo->prox =  NULL;
        return novo;
    } else {
        aux_fim->prox = novo;
        fila->fim = novo;
        novo->prox = NULL;
        novo->prmd = elemento;
        return fila->ini;
    }
}

void destroi_fila(p_ini fila) {
    p_fila aux;

    while(fila->ini != NULL) {
        aux = fila->ini;
        fila->ini = fila->ini->prox;
        free(aux);
    }
    free(fila);
}

void destroi_arvore(p_prmd arvore) {
    if(arvore->esq == NULL && arvore->dir == NULL) {
        free(arvore);
    } else {
        if(arvore->esq != NULL) {
            destroi_arvore(arvore->esq);
        }
        if(arvore->dir != NULL) {
            destroi_arvore(arvore->dir);        
        }
        free(arvore);
    }
}