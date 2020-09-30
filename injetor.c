#include <stdio.h>

int main() {
    int *ponteiro;
    ponteiro = (int *) 140723096381724L;
    (*ponteiro) = 0;
    return 0;
}