typedef struct bloco {
    int numero, qtd;
    char tipo[9];
} Bloco;

// é obrigatório implementar os protótipos seguintes

/**
 * Cria uma matriz de altitudes representando
 * o relevo de um mundo.
 **/
int **calcularAltitudes(int m, int n, int seed);

/**
 * Cria um novo mundo representado por uma matriz
 * de blocos alocada dinamicamente.
 **/
Bloco ***criarMundo(int m, int n, int **altitudes, int seed);

/**
 * Explora o mapa de um mundo e devolve o tempo
 * necessário para minerar todo ele. Além disso,
 * devolve a quantidade de alguns minérios de
 * interesse.
 **/
double explorarMundo(
    Bloco ***mundo, int m, int n, int **altitudes, double tempoPorBloco,
    int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos);

/**
 * Passa por todos os elementos da do mundo 
 * buscando os minerios de interesse e guardando
 * eles em um vetor
 **/
void AchaMinerios(Bloco ***mundo, int **alturas, int qtd[], int m, int n);