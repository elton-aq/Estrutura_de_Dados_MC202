#include <stdio.h>

void muda_tipo1(int* fila, int tamanho, int a, int b) {
    int i, j, k, diferenca, lista_aux[10000];
    
    // descobre a posição I de a
    for (i=0; i<tamanho; i++) {
        if (fila[i] == a) {
            break;
        }
    }

    // descobre a posição J de b
    for (j=0; j<tamanho; j++) {
        if (fila[j] == b) {
            break;
        }
    }
    
    // avalia o intevalo que sera mudado
    diferenca = j - i;

    // monta lista auxiliar só com os termos que vão mudar
    for (k=0; k<diferenca+1; k++) {
        lista_aux[k] = fila[k+i];
    }

    // faz as mudaças
    for (i=0; i<tamanho; i++) {
        if (fila[i] == a) {
            for (j=0; j<diferenca+1; j++) {
                fila[i] = lista_aux[diferenca - j];
                i++;
            }
            break;
        }
    }
}

void muda_tipo2(int* fila, int tamanho, int a, int b) { 
    int i, j;

    // faz as mudanças
    for (i=0; i<tamanho; i++) {
        if (fila[i] == a) {
            for (j=0; j<tamanho; j++) {
                if (fila[i] == b) {
                    fila[i] = a;
                    break;
                } else {
                    fila[i] = fila[i+1];
                    i++;
                }
            }
        break;
        }         
    }  
}

int main() {
    int tamanho, numero_trocas, fila[10000], i, tipo_da_troca, a, b; 

    scanf("%d", &tamanho);
    scanf("%d", &numero_trocas);

    for (i=0; i<tamanho; i++) {         
        // cria fila
        fila[i] = i+1;
    }

    for (i=0; i<numero_trocas; i++) {   
        // redireciona a fila para modifica-la
        scanf("%d" "%d" "%d", &tipo_da_troca, &a, &b);
        if (tipo_da_troca == 1) {
            muda_tipo1(fila, tamanho, a, b);
        } else {
            muda_tipo2(fila, tamanho, a, b);
        }
    }

    for (i=0; i<tamanho; i++) {
        printf("%d ", fila[i]);
    }       
    
    return 0;
}