#include <stdio.h>

int main() {
    int i, f;
    int* lista[7] = {1, 2, 3, 4, 5, 6, 7};
    
    for (i=0; i<7; i++) {
        if (i==5) {
            break;
        } else {
        lista[i], lista[6-i] = lista[6-i], lista[i];
        }
    }

    for (f=0; f<7; f++) {
        printf("%d ", lista[f]);
    }

    return 0;
}