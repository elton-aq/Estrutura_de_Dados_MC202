#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "planejar.h"

int main() {
    Voo voos[100];
    Data datas[100], ferias[2];
    char instrucao[10], cod_origem[4];
    int i, numero_voo;
    float valor;

    do {
        scanf("%s", instrucao);
    
        if (strcmp(instrucao, "registrar") == 0) {
            scanf("%d", &voos[i].numero);
            scanf("%s" "%s", voos[i].origem, voos[i].destino);
            ler_data(datas, i);
            scanf("%f", &voos[i].valor);
            i++;
            
        } else if (strcmp(instrucao, "alterar") == 0) {
            scanf("%d" "%f", &numero_voo, &valor);
            alterar(voos, i, numero_voo, valor);

        } else if (strcmp(instrucao, "cancelar") == 0) {
            scanf("%d", &numero_voo);
            cancelar(voos, i, numero_voo);

        } else if (strcmp(instrucao, "planejar") == 0) {
            scanf("%s", cod_origem);
            ler_data_ferias(ferias, 0, ferias, 1);
            planejar(voos, i, ferias, cod_origem, datas);
        }
    } while (strcmp(instrucao, "planejar") != 0);

    return 0;
}