#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "planejar.h"

int diferenca_data(int data1[], int data2[]) {
    int resultado1, resultado2, final;

    if (data1[2] == 2021 && data2[2] == 2022) {
        
        if (data1[1] == 2) {
            resultado1 = 31 + data1[0];
        } else if (data1[1] == 1) {
            resultado1 = data1[0];
        }else if (data1[1] % 2 == 0 && data1[1] <= 7) {
            resultado1 = (data1[1]-1)*30 + data1[1]/2 - 2 + data1[0];
        } else if (data1[1] % 2 == 1 && data1[1] <= 7) {
             resultado1 = (data1[1]-1)*30 + (data1[1]-1)/2 - 2 + data1[0];
        } else if (data1[1] % 2 == 0 && data1[1] > 7) {
            resultado1 = (data1[1]-1)*30 + data1[1]/2 - 2 + data1[0]; 
        } else if (data1[1] % 2 == 1 && data1[1] > 7) {
            resultado1 = (data1[1]-1)*30 + data1[1]/2 - 1 + data1[0];
        } 
        resultado1 = 365 - resultado1; 
        
        if (data2[1] == 2) {
            resultado2 = 31 + data2[0];
        } else if (data2[1] == 1) {
            resultado2 = data2[0];
        } else if (data2[1] % 2 == 0 && data2[1] <= 7) {
            resultado2 = (data2[1]-1)*30 + data2[1]/2 - 2 + data2[0];
        } else if (data2[1] % 2 == 1 && data2[1] <= 7) {
             resultado1 = (data2[1]-1)*30 + (data2[1]-1)/2 - 2 + data2[0];
        } else if (data2[1] % 2 == 0 && data2[1] > 7) {
            resultado2 = (data2[1]-1)*30 + data2[1]/2 - 2 + data2[0]; 
        } else if (data2[1] % 2 == 1 && data2[1] > 7) {
            resultado2 = (data2[1]-1)*30 + data2[1]/2 - 1 + data2[0];
        } 

        final = resultado2 + resultado1 + 1;
        return final;

    } else if (data1[2] == data2[2]) {
        
        if (data1[1] == 2) {
            resultado1 = 31 + data1[0];
        } else if (data1[1] == 1) {
            resultado1 = data1[0];
        }else if (data1[1] % 2 == 0 && data1[1] <= 7) {
            resultado1 = (data1[1]-1)*30 + data1[1]/2 - 2 + data1[0];
        } else if (data1[1] % 2 == 1 && data1[1] <= 7) {
             resultado1 = (data1[1]-1)*30 + (data1[1]-1)/2 - 2 + data1[0];
        } else if (data1[1] % 2 == 0 && data1[1] > 7) {
            resultado1 = (data1[1]-1)*30 + data1[1]/2 - 2 + data1[0]; 
        } else if (data1[1] % 2 == 1 && data1[1] > 7) {
            resultado1 = (data1[1]-1)*30 + data1[1]/2 - 1 + data1[0];
        } 
        
        if (data2[1] == 2) {
            resultado2 = 31 + data2[0];
        } else if (data2[1] == 1) {
            resultado2 = data2[0];
        } else if (data2[1] % 2 == 0 && data2[1] <= 7) {
            resultado2 = (data2[1]-1)*30 + data2[1]/2 - 2 + data2[0];
        } else if (data2[1] % 2 == 1 && data2[1] <= 7) {
             resultado1 = (data2[1]-1)*30 + (data2[1]-1)/2 - 2 + data2[0];
        } else if (data2[1] % 2 == 0 && data2[1] > 7) {
            resultado2 = (data2[1]-1)*30 + data2[1]/2 - 2 + data2[0]; 
        } else if (data2[1] % 2 == 1 && data2[1] > 7) {
            resultado2 = (data2[1]-1)*30 + data2[1]/2 - 1 + data2[0];
        } 

        final = resultado2 - resultado1 + 1;
        return final;
        
    } else {
        return -1;
    }
}

int compara_data(int data1[], int data2[]) {
    int diferenca;

    if (data1[2] <= data2[2]) {
        diferenca = diferenca_data(data1, data2);    
        if (diferenca >= 0) {
            return diferenca;
        } 
    }
    return -1;
}

void ler_data(Data datas[], int posicao) {
    scanf("%d/%d/%d", &datas[posicao].dt_inteira[0], &datas[posicao].dt_inteira[1], &datas[posicao].dt_inteira[2]);
}

void ler_data_ferias(Data datas1[], int posicao1, Data datas2[], int posicao2) {
    scanf("%d/%d/%d" "%d/%d/%d", &datas1[posicao1].dt_inteira[0], &datas1[posicao1].dt_inteira[1], &datas1[posicao1].dt_inteira[2], &datas2[posicao2].dt_inteira[0], &datas2[posicao2].dt_inteira[1], &datas2[posicao2].dt_inteira[2]);
}

void alterar(Voo voos[], int qtd_voos, int numero_voo, float novo_valor) {
    int i;
    
    for (i=0; i<qtd_voos; i++) {
        if (numero_voo == voos[i].numero) {
            voos[i].valor = novo_valor;
            break;
        }
    }

}

void cancelar(Voo voos[], int qtd_voos, int numero_voo) {
    int i;
    
    for (i=0; i<qtd_voos; i++) {
        if (numero_voo == voos[i].numero) {
            voos[i].numero = 0;
            voos[i].valor = 0;
            strcpy(voos[i].origem, "0\0"); 
            strcpy(voos[i].destino, "0\0");
            break;
        }
    }
}

void planejar(Voo voos[], int qtd_voos, Data ferias[], char codigo_origem[], Data datas[]) {
    int i, j, resultado[2];
    float menor_valor; 

    
    menor_valor = 10000.0;
    for (i=0; i<qtd_voos; i++) {
        if (strcmp(codigo_origem, voos[i].origem) == 0) {
            for (j=0; j<qtd_voos; j++) {
                if (strcmp(voos[i].destino, voos[j].origem) == 0 && strcmp(voos[j].destino, codigo_origem) == 0) {
                    if (voos[i].valor + voos[j].valor <= menor_valor) {
                        if (compara_data(ferias[0].dt_inteira, datas[i].dt_inteira) >= 1 && compara_data(datas[j].dt_inteira, ferias[1].dt_inteira) >= 1 && compara_data(datas[i].dt_inteira, datas[j].dt_inteira) >= 4) {
                            menor_valor = voos[i].valor + voos[j].valor;
                            resultado[0] = voos[i].numero;
                            resultado[1] = voos[j].numero;  
                        }
                    }
                } 
            }
        }
    } 
    
    printf("%d\n", resultado[0]);
    printf("%d\n", resultado[1]);
}