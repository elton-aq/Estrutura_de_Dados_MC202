#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pode_inserir(int **matriz, int tmn, int x, int y, int pivo) {
    int i, aux;
    int casos_esq = 1, casos_dir = 1, casos_cima = 1, casos_baixo = 1;

// ---------- verifica repetição ---------- //
    for(i=1; i<tmn-1; i++) {
        if(pivo == matriz[y][i] && i!=x) {
            return 0;
        }
        if(pivo == matriz[i][x] && i!=y) {
            return 0;
        }
    }

// ---------- verifica posições ---------- //
/* 
cada laço conta (em todas as direções) quantos predios o observador 
vê e no final confere se esta de acordo com as dicas 
*/
    aux = matriz[y][1];   
    for(i=1; i<=x; i++) {
        if(matriz[y][i] > aux) {
            aux = matriz[y][i];
            casos_esq++;
        }
    }
    if(matriz[y][0] < casos_esq){
        return 0;
    }

    aux = matriz[1][x]; 
    for(i=1; i<=y; i++) {
        if(matriz[i][x] > aux) {
            aux = matriz[i][x];
            casos_cima++;
        }
    }
    if(matriz[0][x] < casos_cima) {
        return 0;
    }

    if(y == tmn-2) {      // Entra se esta na ultima linha       
        
        aux = matriz[tmn-2][x];
        for(i=tmn-2; i>0; i--) {        // vai subindo a coluna e conferindo
            if(matriz[i][x] > aux) {
                aux = matriz[i][x];
                casos_baixo++;
            }
        }
        if(matriz[tmn-1][x] != casos_baixo && matriz[0][x] != casos_cima) {
            return 0;
        }
    }

    
    if(x == tmn-2) {      // Entra se esta na ultima coluna 
        
        aux = matriz[y][tmn-2];
        for(i=tmn-2; i>0; i--) {
            if(matriz[y][i] > aux) {
                aux = matriz[y][i];
                casos_dir++;
            }
        }

        if(matriz[y][0] == casos_esq && matriz[y][tmn-1] == casos_dir) { 
            return 1;
        } else {
            return 0;
        }
    }

    return 1;
}

void imprime_matriz(int **resultado, int tamanho) {
    int i, j;

    printf("\n");
    for(i=1; i<tamanho-1; i++) {
        for(j=1; j<tamanho-1; j++) {
            printf("%d ", resultado[i][j]);
        }
        printf("\n");
    }
}

int monta(int **matriz, int tmn, int x, int y) {
    int i;
    
    for(i=1; i<tmn-1; i++) {
        
        if (y == tmn-2 && x == tmn-1) {
            return 1;
        }

        if (x == tmn-1) {
            if(monta(matriz, tmn, 1, y+1)) {
                return 1;
            } else {
                return 0;
            }
        }
            
        if (x != tmn-1) {    
            matriz[y][x] = i;
            if(pode_inserir(matriz, tmn, x, y, i)) {
                if(monta(matriz, tmn, x+1, y)) {
                    return 1;
                }
            } else {
                matriz[y][x] = 0;
            }
        }
    }
    return 0; 
}   

int main() {
    int i, j, lado, **matriz, **aux;


    scanf("%d", &lado);
    lado = lado+2;

    matriz = malloc(lado * sizeof(int*));
    aux = malloc(lado * sizeof(int*));
    for(i=0; i<lado; i++) {
        matriz[i] = malloc(lado * sizeof(int));
        aux[i] = calloc(lado, sizeof(int)); 
    }

    for(i=0; i<lado; i++) {
        for(j=0; j<lado; j++) {
            scanf("%d", &matriz[i][j]);
        }
    }
    
    if(monta(matriz, lado, 1, 1)) {  
        imprime_matriz(matriz, lado);
    }

// -------- Free -------- //
    for(i=0; i<lado; i++) {
        free(matriz[i]);
        free(aux[i]);
    }
    free(matriz);
    free(aux);
    
    return 0;
}