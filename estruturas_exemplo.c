#include <stdio.h>

#define MAX 30

//ESTRUTURA PESSOA
typedef struct ender {
    char rua[MAX];
    int numero;
    char bairro[MAX];
} Endereco;

typedef struct p {
    char nome[MAX];
    int idade;
    float peso;
    Endereco endereco;
} Pessoa;

void imprimiDadosAluno(Pessoa aluno) {
    printf("Nome: %s\n", aluno.nome);
    printf("Idade: %d\n", aluno.idade);
    printf("Peso: %.2f\n", aluno.peso);
    printf("Rua: %s\n", aluno.endereco.rua);
    printf("Numero: %d\n", aluno.endereco.numero);
    printf("Bairro: %s\n", aluno.endereco.bairro);
}


//FUNCAO PRINCIPAL
int main() {
    Pessoa aluno;

    scanf("%s", aluno.nome);
    scanf("%d", &aluno.idade);
    scanf("%f", &aluno.peso);

    scanf("%s", aluno.endereco.rua);
    scanf("%d", &aluno.endereco.numero);
    scanf("%s", aluno.endereco.bairro);

    imprimiDadosAluno(aluno);

    return 0;
}