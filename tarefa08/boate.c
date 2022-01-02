#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boate.h"

void acha_lanterna(p_no pessoa) {
    p_no aux=pessoa;
    
    while(aux->ltn == 0 && aux->prox != NULL){
        aux = aux->prox; 
    }
    aux->ltn = 0;
}

p_no adiciona_na_lanterna(p_no pessoa, int rgt, char pfs[], char vcn[]) {
    p_no p_comum, aux=pessoa, aux2=pessoa;       // p_comum = pessoa comum
    p_comum = malloc(sizeof(No));

    if(pessoa == NULL) {
        p_comum->rgt = rgt;
        strcpy(p_comum->pfs, pfs);
        strcpy(p_comum->vcn, vcn);
        p_comum->ltn = 1;
        p_comum->prox = NULL;
        return p_comum;

    } else {
        p_comum->rgt = rgt;
        strcpy(p_comum->pfs, pfs);
        strcpy(p_comum->vcn, vcn);

        while(aux->ltn == 0) {
            aux = aux->prox;
            aux2 = aux2->prox;
        }
        aux2 = aux2->prox;

        aux->prox = p_comum;            // meu auxiliar aponta para o elemento que esta sendo inserido na fila
        
        acha_lanterna(pessoa);          // retiro a laterna da pessoa que estava com ela até então
        p_comum->ltn = 1;               // para passar para o que esta entrando agora
        
        p_comum->prox = aux2;     // faço a pessoa que entrou agora apontar para p proximo
        
        return pessoa; 
    } 
}

p_no adiciona_comeco(p_no pessoa, int rgt, char pfs[], char vcn[]) {
    p_no privilegiado;
    privilegiado = malloc(sizeof(No));

    if(pessoa != NULL) {
        acha_lanterna(pessoa);
    }

    privilegiado->rgt = rgt;
    strcpy(privilegiado->pfs, pfs);
    strcpy(privilegiado->vcn, vcn);
    privilegiado->ltn = 1;
    privilegiado->prox = pessoa;

    return privilegiado;
}

p_no adiciona_fim(p_no pessoa, int rgt, char pfs[], char vcn[]) {
    p_no funcionario, aux=pessoa;
    funcionario = malloc(sizeof(No));

    if(pessoa == NULL) {
        funcionario->rgt = rgt;
        strcpy(funcionario->pfs, pfs);
        strcpy(funcionario->vcn, vcn);
        funcionario->ltn = 1;
        funcionario->prox = NULL;
        return funcionario;
    } else {
        acha_lanterna(pessoa);
        while(aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = funcionario;

        funcionario->rgt = rgt;
        strcpy(funcionario->pfs, pfs);
        strcpy(funcionario->vcn, vcn);
        funcionario->ltn = 1;
        funcionario->prox = NULL;
        return pessoa;
    }
}

void remove_pessoa(p_no pessoa) {
    p_no aux=pessoa;
     
    while(aux->prox != NULL) {
        if(strcmp(aux->pfs, "fiscal") == 0) {
            aux = aux->prox;
            while(strcmp(aux->vcn, "nao-vacinado") == 0) {
                aux->rgt = 0;
                if(aux->prox != NULL) {
                    aux = aux->prox; 
                } else {
                    break;
                }
            }
            break;
        }
        aux = aux->prox;
    }
}

void remove_pessoa_final(p_no pessoa) {
    p_no aux=pessoa, aux2=pessoa;
     
    while(aux->prox != NULL) {
        if(strcmp(aux->pfs, "fiscal") == 0 && aux->rgt != 0) {
            aux = aux->prox;
            aux2 = aux;
            while(strcmp(aux2->vcn, "nao-vacinado") == 0) {
                aux2->rgt = 0;
                if(aux2->prox != NULL) {
                    aux2 = aux2->prox; 
                } else {
                    break;
                } 
            }
        }
        aux = aux->prox;
    }
}

void imprime(p_no pessoa){          
    p_no aux=pessoa;

    printf("\n");
    while(aux != NULL) {
        if (aux->rgt != 0) {
            printf("%d %s %s\n", aux->rgt, aux->pfs, aux->vcn);
        }
        aux = aux->prox;
    }
}

void destroi(p_no pessoa) {
    if (pessoa->prox != NULL) {
        destroi(pessoa->prox); 
    }
    free(pessoa);
}


p_no cria_lista() {
    return NULL;
}

int main() {
    int registro;
    char profissao[26], vacina[13];
    p_no pessoa;

    pessoa = cria_lista();

    while (scanf("%d %s %s", &registro, profissao, vacina) != EOF) {
        
        if(strcmp(profissao, "funcionario") == 0) {  
            pessoa = adiciona_fim(pessoa, registro, profissao, vacina);
         
        } else if (strcmp(profissao, "fiscal") == 0) {
            pessoa = adiciona_na_lanterna(pessoa, registro, profissao, vacina);
            remove_pessoa(pessoa);

        } else if (strcmp(profissao, "youtuber-financas") == 0 || strcmp(profissao, "herdeiro") == 0 || 
        strcmp(profissao, "filho-politico") == 0 || strcmp(profissao, "ex-bbb") == 0 || strcmp(profissao, "coach") == 0) { 
            pessoa = adiciona_comeco(pessoa, registro, profissao, vacina);  

        } else {
            pessoa = adiciona_na_lanterna(pessoa, registro, profissao, vacina);
        }
    }

    remove_pessoa_final(pessoa);
    imprime(pessoa);
    destroi(pessoa);

    return 0;
}
