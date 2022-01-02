#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "minecraft.h"

int **calcularAltitudes(int m, int n, int seed) {
    int **H, i, j;
    
    H = malloc(m * sizeof(int*));
    for(i=0; i<m; i++) {
        H[i] = malloc(n * sizeof(int));
    }

    for(i=0; i<m; i++) {
        for(j=0; j<n; j++) {
            H[i][j] = (seed*(202 + i + j) + 12345 + i + j) % 256; 
        }
    }
    return H;
}

Bloco ***criarMundo(int m, int n, int **altitudes, int seed) {
    int x, z, y, d=0, valor; 
    Bloco ***matriz_mundo;

    matriz_mundo = malloc(m * sizeof(Bloco**));
    for(z=0; z<m; z++) {
        matriz_mundo[z] = malloc(n * sizeof(Bloco*));
        for(y=0; y<n; y++) {
            matriz_mundo[z][y] = malloc(256 * sizeof(Bloco));
        }
    }

    for (y=0; y<256; y++) {
        for(x=0; x<m; x++) {
            for(z=0; z<n; z++) {
                if (y > altitudes[x][z]) {
                    strcpy(matriz_mundo[x][z][y].tipo, "vazio");
                    matriz_mundo[x][z][y].numero = 21;
                } else {
                    valor = (seed*(202 + x + y + z) + x + y + z) % 33;
                    
                    if (valor == 0) {
                        strcpy(matriz_mundo[x][z][y].tipo, "diamante"); 
                        matriz_mundo[x][z][y].numero = 0;
                        d++; 
                    } else if (valor == 1 || valor == 2) {
                        strcpy(matriz_mundo[x][z][y].tipo, "ouro"); 
                        matriz_mundo[x][z][y].numero = 1;
                    } else if (valor >= 3 && valor <= 5) {
                        strcpy(matriz_mundo[x][z][y].tipo, "ferro"); 
                        matriz_mundo[x][z][y].numero = 3;
                    } else if (valor >= 6 && valor <= 11) {
                        strcpy(matriz_mundo[x][z][y].tipo, "pedra"); 
                        matriz_mundo[x][z][y].numero = 6;
                    } else if (valor >= 12 && valor <= 20) {
                        strcpy(matriz_mundo[x][z][y].tipo, "terra"); 
                        matriz_mundo[x][z][y].numero = 12;
                    } else if (valor >= 21 && valor <= 23) {
                        strcpy(matriz_mundo[x][z][y].tipo, "vazio"); 
                        matriz_mundo[x][z][y].numero = 21;
                    } else if (valor >= 24 && valor <= 28) {
                        strcpy(matriz_mundo[x][z][y].tipo, "agua"); 
                        matriz_mundo[x][z][y].numero = 24;
                    } else if (valor >= 29 && valor <= 32) {
                        strcpy(matriz_mundo[x][z][y].tipo, "lava"); 
                        matriz_mundo[x][z][y].numero = 29;
                    }    
                }
            }
        }
    }
    return matriz_mundo;
}

double explorarMundo(
    Bloco ***mundo, int m, int n, int **altitudes, double tempoPorBloco, int *qtdDiamante,
    int *qtdOuro, int *qtdFerro, int *qtdBlocos) {

    int x, y, z;
    double tempo;

    *qtdDiamante = 0; 
    *qtdOuro = 0;
    *qtdFerro = 0;
    *qtdBlocos = 0;

    for(x=0; x<m; x++) {
        for(z=0; z<n; z++) { 
            for(y=0; y<=altitudes[x][z]; y++) {
                if (strcmp(mundo[x][z][y].tipo, "vazio") != 0 && strcmp(mundo[x][z][y].tipo, "agua") != 0 
                && strcmp(mundo[x][z][y].tipo, "lava") != 0) {

                *qtdBlocos = *qtdBlocos + 1;
                }
                if (strcmp(mundo[x][z][y].tipo, "diamante") == 0) {
                    *qtdDiamante = *qtdDiamante + 1;
                } else if (strcmp(mundo[x][z][y].tipo, "ouro") == 0) {
                    *qtdOuro = *qtdOuro + 1;
                } else if (strcmp(mundo[x][z][y].tipo, "ferro") == 0) {
                    *qtdFerro = *qtdFerro + 1;
                }
            }
        }
    }
    tempo = tempoPorBloco * (*qtdBlocos);
    return tempo;
}


int main() {
    int i, j, blocos_x, blocos_z, seed, **matriz_h, qtdDiamante, qtdOuro, qtdFerro, qtdBlocos; 
    double tempo,tempo_total; 
    Bloco ***matriz_mundo;

    scanf ("%d %d", &blocos_x, &blocos_z);
    scanf ("%d", &seed);
    scanf ("%lf", &tempo);
    
    matriz_h = calcularAltitudes(blocos_x, blocos_z, seed);
    
    matriz_mundo = criarMundo(blocos_x, blocos_z, matriz_h, seed);

    tempo_total = explorarMundo(matriz_mundo, blocos_x, blocos_z, matriz_h, tempo, &qtdDiamante, &qtdOuro, &qtdFerro, &qtdBlocos);

    printf("Total de Blocos: %d", qtdBlocos);
    printf("\nTempo total: %.2lfs", tempo_total);
    printf("\nDiamantes: %d", qtdDiamante);
    printf("\nOuros: %d", qtdOuro);
    printf("\nFerros: %d\n", qtdFerro);

    for(i=0; i<blocos_x; i++) {    
        for(j=0; j<blocos_z; j++) {
            free(matriz_mundo[i][j]);
        }
        free(matriz_mundo[i]); 
        free(matriz_h[i]); 
    }
    free(matriz_mundo);
    free(matriz_h);
    
        
    return 0;
}