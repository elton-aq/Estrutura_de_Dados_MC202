typedef struct data {
    int dt_inteira[3]; //{dia, mes, ano}
} Data;

struct voo {
    int numero;
    char origem[4], destino[4]; 
    float valor;
};
typedef struct voo Voo; 

void ler_data(Data datas[], int posicao);

void ler_data_ferias(Data datas1[], int posicao1, Data datas2[], int posicao2);

int compara_data(int data1[], int data2[]);

int diferenca_data(int data1[], int data2[]);

void cancelar(Voo voos[], int qtd_voos, int numero_voo);

void alterar(Voo voos[], int qtd_voos, int numero_voo, float novo_valor);

void planejar(Voo voos[], int qtd_voos, Data ferias[], char codigo_origem[], Data datas[]);