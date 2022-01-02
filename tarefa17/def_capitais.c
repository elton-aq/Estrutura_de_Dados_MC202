#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "def_capitais.h"
#define INF 999999

int main() {
    int i, quant_cdd, ind1, ind2, ppc_total=0, tmn_ord=0;
    double dist;
    char nome1[51], nome2[51];
    Cdd *cidades, *cdds_ord;
    p_grafo grafo, aux;

    scanf("%d", &quant_cdd);
    cidades = malloc(quant_cdd * sizeof(Cdd));
    cdds_ord = malloc(quant_cdd * sizeof(Cdd));
    grafo = cria_grafo(quant_cdd);
    aux = cria_grafo(quant_cdd);

    for(i=0; i<quant_cdd; i++) {
        scanf("%s %d", cidades[i].nome, &cidades[i].ppc);
        ppc_total += cidades[i].ppc;
    }

    while(scanf("%s %s %lf", nome1, nome2, &dist) != EOF) {
        ind1 = acha_indice(nome1, cidades, quant_cdd);
        ind2 = acha_indice(nome2, cidades, quant_cdd);
        grafo->adj[ind1][ind2] = dist;
        grafo->adj[ind2][ind1] = dist;
    }

    fw(grafo, aux);

    for(i=0; i<quant_cdd; i++) {
        ind1 = acha_indice(cidades[i].nome, cidades, quant_cdd);
        cidades[i].fator_c = calcula_fator(grafo, cidades, ind1, ppc_total);
        if(cidades[i].fator_c != 0) {
            cdds_ord = add_ordenado(cidades[i], cdds_ord, tmn_ord);
            tmn_ord++;
        }
    }

    printa_lista(cdds_ord, tmn_ord);

    destroi_grafos(grafo, aux);
    free(cidades); 
    free(cdds_ord);
}

p_grafo cria_grafo(int n) {
    int i, j;
    p_grafo novo = malloc(sizeof(Grafo));
    
    novo->n = n;
    novo->adj = malloc(n*sizeof(double*));
    
    for(i=0; i<n; i++) {
        novo->adj[i] = malloc(n*sizeof(double));
        for(j=0; j<n; j++) {
            if(i==j)
                novo->adj[i][j] = 0;
            else
                novo->adj[i][j] = INF;
        }
    }

    return novo;
}

void fw(p_grafo grafo, p_grafo dist) {
    int i, j, k, n = grafo->n;

    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {
            dist->adj[i][j] = grafo->adj[i][j];
        }
    } 

    for(k=0; k<n; k++) {
        for(i=0; i<n; i++) {
            for(j=0; j<n; j++) {
                if(dist->adj[i][j] > dist->adj[i][k] + dist->adj[k][j]) {
                    dist->adj[i][j] = dist->adj[i][k] + dist->adj[k][j];
                }
            }
        }
    } 
    
    for(i=0; i<n; i++) {
        for(j=0; j<n; j++) {   
            grafo->adj[i][j] = dist->adj[i][j];
        }
    } 

} 

int acha_indice(char nome[], Cdd lista[], int tmn) {
    int i;

    for(i=0; i<tmn; i++) {
        if(strcmp(nome, lista[i].nome) == 0) {
            return i;
        }
    }
    return -1;
}

double calcula_fator(p_grafo grafo, Cdd cidades[], int indice, int ppc_total) {
    int i, soma_ppc=0;
    double soma_ppc_e_dist=0;

    for(i=0; i<grafo->n; i++) {
        if(grafo->adj[indice][i] != INF && i != indice) {
            soma_ppc_e_dist += cidades[i].ppc * grafo->adj[indice][i];  
            soma_ppc += cidades[i].ppc;
        }
    }
    soma_ppc += cidades[indice].ppc;

    if(ppc_total/2 >= soma_ppc) {
        return 0;
    } else {
        return soma_ppc_e_dist/soma_ppc;
    } 
        
}

Cdd* add_ordenado(Cdd cidade, Cdd lista[], int tmn_vetor) {
    int i;
    
    if(tmn_vetor == 0) {
        strcpy(lista[0].nome, cidade.nome);
        lista[0].ppc = cidade.ppc;
        lista[0].fator_c = cidade.fator_c;
        return lista;
    }

    for(i=tmn_vetor-1; i>=0; i--){
        if(lista[i].fator_c > cidade.fator_c) {
            lista[i+1] = lista[i];
            if(i==0) {
                strcpy(lista[i].nome, cidade.nome);
                lista[i].ppc = cidade.ppc;
                lista[i].fator_c = cidade.fator_c; 
            }
        } else if(lista[i].fator_c == cidade.fator_c) {
            if(strcmp(lista[i].nome, cidade.nome) > 0) {
                lista[i+1] = lista[i];
            } else {
                strcpy(lista[i+1].nome, cidade.nome);
                lista[i+1].ppc = cidade.ppc;
                lista[i+1].fator_c = cidade.fator_c;
                break;        
            }
        } else {
            strcpy(lista[i+1].nome, cidade.nome);
            lista[i+1].ppc = cidade.ppc;
            lista[i+1].fator_c = cidade.fator_c;
            break;
        }
    }
    return lista;
}

void printa_lista(Cdd lista[], int tmn) {
    int i;

    for(i=0; i<tmn; i++) {
        printf("\n%s %.2lf", lista[i].nome, lista[i].fator_c);
    }
}

void destroi_grafos(p_grafo grafo1, p_grafo grafo2) {
    int i, n = grafo1->n;

    for(i=0; i<n; i++) {
        free(grafo1->adj[i]);
        free(grafo2->adj[i]);
    }
    free(grafo1->adj);
    free(grafo2->adj);
    free(grafo1);
    free(grafo2);
}