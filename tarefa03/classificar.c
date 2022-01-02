#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

void ordena(char lista[MAX][30], int tam) {
    int i, j;
    char aux[30];

    for (i = 1; i < tam; i++) {
        for (j = 1; j < tam; j++) {
            if (strcmp(lista[j - 1], lista[j]) > 0) {
                strcpy(aux, lista[j - 1]);
                strcpy(lista[j - 1], lista[j]);
                strcpy(lista[j], aux);
            }
        }
    }
}

int homonimos(char nomes[MAX][30], char resultado[MAX][30], int tamanho) {
    int i, j, k=0, len;
    char aux_1[MAX][30];

    for (i=0; i<tamanho; i++) {
        len = strlen(nomes[i]);
        for (j=0; j<len; j++) { 
            if (nomes[i][j] == '_') {
                aux_1[i][j] = '\0';
                break;
            }
            aux_1[i][j] = nomes[i][j];
        }
    }

    for (i=0; i<tamanho; i++) {
        if (i == 0 && strcmp(aux_1[i], aux_1[i+1]) == 0) {
            strcpy(resultado[k], nomes[i]);
            k++;
        } else if (i == tamanho-1 && strcmp(aux_1[i], aux_1[i-1]) == 0) {
            strcpy(resultado[k], nomes[i]);
            k++;
        } else if (i != 0 && i != tamanho-1) {
            if (strcmp(aux_1[i], aux_1[i+1]) == 0 || strcmp(aux_1[i], aux_1[i-1]) == 0) {
                strcpy(resultado[k], nomes[i]);
                k++;
            }
        }
    }
    return k;
} 

// char parentes(char* nomes, int tamanho) {
    
// } 

int main() {
    int i, quant, quant_de_nomes;
    char tipo[10], nomes[MAX][30], resultado[MAX][30];

    scanf("%d", &quant);
    scanf("%s", tipo);

    for (i=0; i<quant; i++) {
        scanf("%s", nomes[i]);
    }

    ordena(nomes, quant);

    if (strcmp(tipo, "homonimos") == 0) {
        quant_de_nomes = homonimos(nomes, resultado, quant);
    // } else {
    //     parentes(nomes, quant);
    //     homoniomos(nomes, quant);
    }

    for (i=0; i<quant_de_nomes; i++) {
        printf("%s\n", resultado[i]);
    }

    return 0;
}