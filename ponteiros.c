#include <stdio.h>

int main() {
    int variavel = 10;
    int *ponteiro;

    while (1) {
        ponteiro = &variavel;

        printf("%p\n", ponteiro);
        printf("%d\n", (*ponteiro));
        getchar();
    }

    return 0;
}