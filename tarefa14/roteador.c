#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "roteador.h"

int main(){
    int i, k, m, cont = 0, tmn;
    int id, prio, inc;  
    p_fila fila;

    scanf("%d %d", &k, &m); 
    /* k = numero de pacotes quem o roteador manda p/ tick
       m = limite de memoria do roteador */

    fila = cria_fila(m);
    while(scanf("%d %d %d", &id, &prio, &inc) != EOF) {
        if(id != 0 || prio != 0 || inc != 0) {
            if(m > fila->n) 
                insere(fila, id, prio, inc);
        } else if(k != 0){
            cont++;
            printf("TICK %d\n", cont);
            tmn = fila->n;
            for(i=0; i<tmn; i++) {
                if(i<k)  
                    extrai_maximo(fila);
            }  
            printf("\n");
            fila = atualiza_prioridades(fila);
            sobe_no_heap(fila, fila->n-1);
            desce_no_heap(fila, 0);
        }
    }
    destroi_fila(fila);
    return 0;
}

p_fila cria_fila(int tam) {
    p_fila fila = malloc(sizeof(FilaPrio));
    fila->v = malloc(tam * sizeof(item));
    fila->n = 0;
    fila->tmn = tam;
    return fila;
}

void insere(p_fila fila, int id, int prio, int inc) {
    fila->v[fila->n].id = id;
    fila->v[fila->n].prio = prio;
    fila->v[fila->n].inc = inc;
    fila->n++;
    sobe_no_heap(fila, fila->n-1);
}

void troca(item *a, item *b) {
    item t = *a;
    *a = *b;
    *b = t;
}

void sobe_no_heap(p_fila fila, int k) {
    if (k > 0 && fila->v[PAI(k)].prio < fila->v[k].prio) {
        troca(&fila->v[k], &fila->v[PAI(k)]);
        sobe_no_heap(fila, PAI(k));
    }
}

void desce_no_heap(p_fila fila, int k) {
    int maior_filho;
    
    if (F_ESQ(k) < fila->n) {
        maior_filho = F_ESQ(k);
        if(F_DIR(k) < fila->n &&
        fila->v[F_ESQ(k)].prio < fila->v[F_DIR(k)].prio)
            maior_filho = F_DIR(k);
        if (fila->v[k].prio < fila->v[maior_filho].prio) {
            troca(&fila->v[k], &fila->v[maior_filho]);
            desce_no_heap(fila, maior_filho);
        }
    }
}

void extrai_maximo(p_fila fila) {
    item item = fila->v[0];
    
    troca(&fila->v[0], &fila->v[fila->n - 1]);
    fila->n--;
    desce_no_heap(fila, 0);
    printf("%d\t%d\t%d\n", item.id, item.prio, item.inc);
}

p_fila atualiza_prioridades(p_fila fila) {
    int i, tmn = fila->n;

    for(i=0; i<tmn; i++) {
        fila->v[i].prio += fila->v[i].inc;
    }

    return fila;
}

void destroi_fila(p_fila fila) {
    free(fila->v);
    free(fila);
}
