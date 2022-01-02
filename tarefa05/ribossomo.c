#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

int main() {
    char dna[14], rna[14], *seg_dna, *seg_rna;
    int i, j, n=0, tamanho, *lista_id;

    scanf("%s", dna);
    scanf("%s", rna);
    scanf("%d", &tamanho);
    seg_dna = malloc(tamanho+1 * sizeof(char));
    seg_rna = malloc(tamanho+1 * sizeof(char));   
    lista_id = malloc(tamanho * sizeof(int));   
    scanf("%s", seg_dna);

    for (i=0; i<tamanho; i++) {
        for (j=0; j<14; j++){
            if (seg_dna[i] == dna[j]) {
                seg_rna[i] = rna[j];    
                break;
            }
        }
    }

    for (i=0; i<tamanho; i++) {
        for (j=0; j<tamanho; j++) {
            if (seg_dna[i] == seg_dna[j]) {
                lista_id[j] = n;
                n++;
            }
        }
        n = 0;
    }

    printf("\n");
    printf("ID:\t");
    for (i=0; i<tamanho; i++) {
        printf("%d\t", lista_id[i]);
    } 
    printf("\n");
    printf("DNA:\t");
    for (i=0; i<tamanho; i++) {
        printf("%c\t", seg_dna[i]);
    } 
    printf("\n");
    printf("\t");
    for (i=0; i<tamanho; i++) {
        printf("|\t");
    } 
    printf("\n");
    printf("RNA:\t");
    for (i=0; i<tamanho; i++) {
        printf("%c\t", seg_rna[i]);
    } 


    free(seg_dna);
    free(seg_rna);
    free(lista_id);
    return 0;
}