#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "docas.h"

int main() {
    int i, num_docas, cpcd_docas, num_navios, quant_carga, ok=1;
    char nome[21], objetivo[11], carga[21];
    p_pilha *fila_docas; // fila de docas com uma pilha em cada elemento
    p_fila fila_navios;

    scanf("%d", &num_docas); 
    scanf("%d", &cpcd_docas); 
    scanf("%d", &num_navios); 

    fila_docas = malloc(num_docas * sizeof(p_pilha));
    for(i=0; i<num_docas; i++) {
        fila_docas[i] = malloc(sizeof(Pilha));
        fila_docas[i]->topo = NULL;
        fila_docas[i]->fim = NULL;
        fila_docas[i]->qtd_max = cpcd_docas;
        fila_docas[i]->qtd_atual = 0;
    }

    fila_navios = cria_fila();
    for(i=0; i<num_navios; i++) {
        scanf("%s %s %s %d", nome, objetivo, carga, &quant_carga);
        monta_fila(fila_navios, nome, objetivo, carga, quant_carga);
    }

    fila_navios = liga_circular(fila_navios);

    while(fila_navios->ini != NULL) {
        i=0;
        while(i<num_docas) {

            if(strcmp("carrega", fila_navios->ini->objetivo) == 0 && fila_docas[i]->topo != NULL &&
            fila_navios->ini->quant_max > fila_navios->ini->quant_atual) {
            
                if(strcmp(fila_docas[i]->topo->carga, fila_navios->ini->carga) == 0) {
                    
                    fila_docas[i] = carrega_navio(fila_navios->ini, fila_docas[i], i);   
                    if(fila_navios->ini->quant_atual == fila_navios->ini->quant_max) {
                        remove_fila(fila_navios, fila_navios->ini);
                    } else {
                        fila_navios = manda_para_o_fim(fila_navios);
                    }
                    break;
                }
            
            } else if(strcmp("descarrega", fila_navios->ini->objetivo) == 0 && 
            fila_docas[i]->qtd_max > fila_docas[i]->qtd_atual && fila_navios->ini->quant_atual > 0) {
                fila_docas[i] = descarrega_navio(fila_navios->ini, fila_docas[i], i);
                if(fila_navios->ini->quant_atual == 0) {
                    remove_fila(fila_navios, fila_navios->ini);
                } else {
                    fila_navios = manda_para_o_fim(fila_navios);
                }
                break;

            }
            i++;
            if(i == num_docas && fila_navios->ini != NULL) {
                ok = casca_confere(fila_navios, num_navios, fila_docas, num_docas);
                fila_navios = manda_para_o_fim(fila_navios);
            }
        }
        if(!ok) {
            break;
        }
    }

    destroi_docas(fila_docas, num_docas);
    destroi_navios(fila_navios);

    return 0;
}

p_fila cria_fila() {
    p_fila  fila;
    fila = malloc(sizeof(Fila));
    fila->ini = NULL;
    fila->fim = NULL;
    return fila;
}

void monta_fila(p_fila fila, char nome[], char objetivo[], char carga[], int quant) {
    p_nv novo;
    
    novo = malloc(sizeof(Navios));
    strcpy(novo->nome, nome);
    strcpy(novo->objetivo, objetivo);
    strcpy(novo->carga, carga);
    novo->quant_max = quant;
    if(strcmp(objetivo, "descarrega") == 0) {
        novo->quant_atual = quant;
    } else {
        novo->quant_atual = 0;
    }

    if(fila->ini == NULL) {
        fila->ini = novo;
    } else {
        fila->fim->prox = novo;
    }
    fila->fim = novo;
}

p_fila liga_circular(p_fila fila) {
    fila->fim->prox = fila->ini;
    return fila; 
}

void remove_fila(p_fila fila, p_nv navio) { 
    if(fila->ini == fila->fim) {
        fila->ini = NULL;
        fila->fim = NULL;
        free(navio);
    } else {
        fila->ini = fila->ini->prox;
        fila->fim->prox = fila->ini;
        free(navio);
    }
}

p_pilha adiciona_doca(p_pilha pilha, char carga[]) {
    p_doca novo = malloc(sizeof(Doca));
    strcpy(novo->carga, carga);
    novo->prox = pilha->topo;
    pilha->topo = novo;
    return pilha;
}

p_pilha remove_doca(p_pilha pilha) {
    p_doca topo = pilha->topo;
    pilha->topo = pilha->topo->prox;
    free(topo);
    return pilha;
}

p_fila manda_para_o_fim(p_fila fila) {  
    fila->ini = fila->ini->prox;
    fila->fim = fila->fim->prox;

    return fila;
}

p_pilha carrega_navio(p_nv navio, p_pilha pilha, int n_doca) {
    int qnt_inicial = navio->quant_atual;

    while(navio->quant_max > navio->quant_atual && pilha->qtd_atual > 0) {
        if(strcmp(pilha->topo->carga, navio->carga) == 0) {
            navio->quant_atual++;
            pilha->qtd_atual--;
            pilha = remove_doca(pilha);
        } else {
            break;
        }
    }

    printf("%s carrega %s doca: %d conteineres: %d\n", navio->nome, navio->carga, n_doca, (navio->quant_atual-qnt_inicial));
    return pilha;
}

p_pilha descarrega_navio(p_nv navio, p_pilha pilha, int n_doca) {
    int qnt_inicial = pilha->qtd_atual;

    while(pilha->qtd_max > pilha->qtd_atual && navio->quant_atual > 0) {
        navio->quant_atual--;
        pilha->qtd_atual++;
        pilha = adiciona_doca(pilha, navio->carga);
    }
    printf("%s descarrega %s doca: %d conteineres: %d\n", navio->nome, navio->carga, n_doca, (pilha->qtd_atual-qnt_inicial));
    return pilha;
}

int casca_confere(p_fila fila_navios, int num_navios, p_pilha fila_docas[], int num_docas) {
    int restantes;

    restantes = confere_capacidade(fila_navios, fila_docas, num_docas); 
    //confere se tem espaço para carregar as docas
    if(restantes != -1) {
        printf("ALERTA: impossivel esvaziar fila, restam %d navios.", restantes);
        return 0;
    }

    restantes = confere_demanda(fila_navios, num_navios, fila_docas, num_docas);    
    //confere se tem espaço para descarregar as docas
    if(restantes != -1){
        printf("ALERTA: impossivel esvaziar fila, restam %d navios.", restantes);
        return 0;
    }
    return 1;
}

int confere_capacidade(p_fila navios, p_pilha lista_docas[], int qtd_docas) {
    int i, resto=0;
    p_nv navio = navios->ini;
    
    for(i=0; qtd_docas > i; i++) { // confere se ainda tem espaço nas docas
        if(lista_docas[i]->qtd_max > lista_docas[i]->qtd_atual) {
            return -1;
        }
    }

    do {
        if(strcmp(navio->objetivo, "carrega") == 0) {
            return -1;
        } else {
            resto++;
            navio = navio->prox;
        }
    } while(navio != navios->ini);
 
    return resto;
}

int confere_demanda(p_fila navios, int qtd_navios, p_pilha lista_docas[], int qtd_docas) {
    int i, resto=0;
    p_nv navio = navios->ini;
    
    do {   // se achar um descarrega, sabe que ainda pode retirar carga, portanto sai
        if(strcmp(navio->objetivo, "descarrega") == 0) {
            return -1;
        } else {
            for(i=0; i<qtd_docas; i++) {
                if(lista_docas[i]->topo != NULL) {
                    if(strcmp(lista_docas[i]->topo->carga, navio->carga) == 0) {
                        return -1;
                    }
                }
            }
            resto++;
            navio = navio->prox;
        }
    } while(navio != navios->ini);
    
    return resto;
}


void destroi_docas(p_pilha docas[], int qtd_docas) {
    int i;
    
    for(i=0; i<qtd_docas; i++) {
        free(docas[i]);
    }    
    free(docas);
}

void destroi_navios(p_fila navios) {
    while(navios->ini != NULL) {
        remove_fila(navios, navios->ini);
    } 
    free(navios);
}