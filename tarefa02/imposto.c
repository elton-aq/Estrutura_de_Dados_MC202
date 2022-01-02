#include <stdio.h>
#define MAX 1000        //tamanho da lista 

// ---------------------- funções ---------------------- //

float anual(float valor) {
    
    if (valor < 18000.00) {
        valor = 0.00;
    } else if (valor < 26400.00 ) {
        valor -= 18000.00;
        valor *= 0.075;
    } else if (valor < 36000.00) {
        valor -= 26400.00; 
        valor *= 0.15;
        valor += 630.00;
    } else if (valor < 44400.00) {
        valor -= 36000.00; 
        valor *= 0.225;
        valor += 2070.00;
    } else {
        valor -= 44400.00;
        valor *= 0.275;
        valor += 3960.00; 
    }
    return valor; 
} 

float soma(float* lista) {
    int i;
    float valor_final = 0;
    
    for (i=0; i<12; i++) {
        valor_final += lista[i];
    }
    return valor_final;
}

void mensal (float* lista) {
    int i;
    
    for (i=0; i<12; i++) {
        if (lista[i] < 1499.15) {
            lista[i] = 0.00;
        } else if (lista[i] < 2246.75 ) {
            lista[i] -= 1499.15;
            lista[i] *= 0.075;
        } else if (lista[i] < 2995.70) {
            lista[i] -= 2246.75; 
            lista[i] *= 0.15;
            lista[i] += 56.07;
        } else if (lista[i] < 3743.19) {
            lista[i] -= 2995.70; 
            lista[i] *= 0.225;
            lista[i] += 168.4125;
        } else {
            lista[i] -= 3743.19;
            lista[i] *= 0.275;
            lista[i] += 336.59775; 
        } 
    }
}

int main() {
    // ---------------------- coleta de dados ---------------------- //

    int i, j, funcionarios;
    float matriz_valores[MAX][12], lista_abatimento[MAX], lista_anual[MAX], lista_retido[MAX], abatimento;

    scanf("%d", &funcionarios);

    for (i=0; i<funcionarios; i++) {
        scanf("%f" "%f" "%f" "%f" "%f" "%f" "%f" "%f" "%f" "%f" "%f" "%f" , &matriz_valores[i][0], &matriz_valores[i][1], &matriz_valores[i][2], &matriz_valores[i][3], &matriz_valores[i][4], &matriz_valores[i][5], &matriz_valores[i][6], &matriz_valores[i][7], &matriz_valores[i][8], &matriz_valores[i][9], &matriz_valores[i][10], &matriz_valores[i][11]);
    }

    for (i=0; i<funcionarios; i++) {
        scanf("%f", &abatimento);
        lista_abatimento[i] = abatimento; 
    }

    // ---------------------- anual ---------------------- //
    
    for (i=0; i<funcionarios; i++) {
        lista_anual[i] = soma(matriz_valores[i]);
        lista_anual[i] -= lista_abatimento[i];
        lista_anual[i] = anual(lista_anual[i]);
    }

    // ---------------------- mensal ---------------------- //

    for (i=0; i<funcionarios; i++) {
        mensal(matriz_valores[i]);    
        lista_retido[i] = soma(matriz_valores[i]);
    }
    
    // ---------------------- imprime resultados ---------------------- //

    printf("Jan Fev Mar Abr Mai Jun Jul Ago Set Out Nov Dez Retido  Devido  Ajuste\n");
    for (i=0; i<funcionarios; i++) {
        for (j=0; j<12; j++) {
            printf("%.2f\t", matriz_valores[i][j]);
        } 
        printf("%.2f\t" "%.2f\t" "%.2f\n", lista_retido[i], lista_anual[i], lista_anual[i] - lista_retido[i]);
    }
    return 0;
}