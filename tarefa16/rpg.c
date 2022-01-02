#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rpg.h"

int main() {  
    /* matriz_fim corresponde a matriz das possibiliades da posição de termino de cada personagem */
    int i, quant_celas, quant_psng, indice, *indices;
    p_grafo grafo;
    Cela *celas, personagem;

    scanf("%d", &quant_celas);  
    grafo = cria_grafo(quant_celas);
    celas = malloc(quant_celas * sizeof(Cela));

    for(i=0; i<quant_celas; i++) {
        scanf("%s %d %d %d %d %d %d", celas[i].nome, &celas[i].atb[0], &celas[i].atb[1], &celas[i].atb[2], &celas[i].atb[3], &celas[i].atb[4], &celas[i].atb[5]);
    }

    scanf("%d", &quant_psng);
    indices = malloc(quant_psng * sizeof(int));

    for(i=0; i<quant_psng; i++) {
        scanf("%s %d %d %d %d %d %d", personagem.nome, &personagem.atb[0], &personagem.atb[1], &personagem.atb[2], &personagem.atb[3], &personagem.atb[4], &personagem.atb[5]);
        indice = acha_indice(celas, grafo->n, personagem);
        if(indice == -1) {
            printf("Impossivel terminar em duas rodadas.");
            break;
        } else {
            indices[i] = indice;
            monta_adjacencias(celas, grafo, personagem, indice, 1, indice);
        }
    }   
          
    compara_resultados(grafo, indices, quant_psng, celas);  

    destroi_grafo(grafo);
    free(celas);
    free(indices);

    return 0;
}

p_grafo cria_grafo(int tmn) {
    int i, j;
    p_grafo grafo = malloc(sizeof(Grafo));
    grafo->n = tmn;
    grafo->adj = malloc(tmn * sizeof(int*));
    
    for(i=0; i<tmn; i++) 
        grafo->adj[i] = malloc(tmn * sizeof(int));

    /* Sabendo que essa grafo é completo podemos 
    preencher sua coluna principal com 1 por não
    existirem auto-laços */
    for(i=0; i<tmn; i++) {
        for(j=0; j<tmn; j++) {
            if(i==j) 
                grafo->adj[i][j] = 1;
            else
                grafo->adj[i][j] = 0;
        }
    }

    return grafo;
}

int acha_indice(Cela celas[], int tmn, Cela psng) {
    int i;

    for(i=0; i<tmn; i++) {
        if(celas[i].atb[0] == psng.atb[0] && celas[i].atb[1] == psng.atb[1] && celas[i].atb[2] == psng.atb[2] && 
        celas[i].atb[3] == psng.atb[3] && celas[i].atb[4] == psng.atb[4] && celas[i].atb[5] == psng.atb[5]) {
            return i;    
        }
    } 
    return -1;
}

void monta_adjacencias(Cela celas[], p_grafo grafo, Cela personagem, int indice, int contagem, int i_personagem) {
    int i;
    
    for(i=0; i < grafo->n; i++) {
        if(i != indice && pode_ir(personagem, celas[i], contagem)) {
            if(contagem == 2) {
                /* Sabendo que o grafo é não direcionados devemos marcar 
                a "ida e volta" como dos vertices como adjacentes */
                grafo->adj[i_personagem][i] = 1;
                grafo->adj[i][i_personagem] = 1;
            } else if(contagem < 2){ 
                monta_adjacencias(celas, grafo, personagem, i, contagem+1, i_personagem);
            }
        } 
    }
}

int pode_ir(Cela cela1, Cela cela2, int nivel) {
    int i, dif, cont=0;

    for(i=0; i<6; i++) {       
        dif = cela2.atb[i]-cela1.atb[i];
        if(dif == 1) {
            cont++;
        } else if(dif == 2) {
            cont++;
            cont++;
        } else if(dif > 2) {
            cont = 3;
            break;
        }
    }

    if(cont <= nivel)
        return 1;
    else 
        return 0;
}

void compara_resultados(p_grafo grafo, int *psng, int quant, Cela *celas) {
    int i, j, cont1, cont2=0;
    /* cont1 tem a função de mostrar se as celas são ou não em comuns,
    o cont2 tem a função de montras se alguma celas foi printada para 
    sabermos se é possivel completar o rpg*/

    printf("\n");
    for(i=0; i<grafo->n; i++) {
        cont1 = 0;
        for(j=0; j<quant; j++) {
            /* psng[j] é a lista de posição inicial dos 
            personagens no grafo, variamos ela pra olharmos 
            somente para essas posições que nos importa */
            if(grafo->adj[psng[j]][i] == 0) {
                cont1++;
                cont2++;
                break;
            }
        }         
        if(cont1 == 0) {
            printf("%s\n", celas[i].nome);
        }
    }
    if(cont2 == grafo->n) {
        printf("Impossivel terminar em duas rodadas.");
    }
}

void destroi_grafo(p_grafo grafo) {
    int i, tmn = grafo->n;

    for (i = 0; i < tmn; i++)
        free(grafo->adj[i]);
    free(grafo->adj);
    free(grafo);
}