#include <stdio.h>
#include <stdlib.h>

#define MAX 3
#define MAX_NAME 30
#define P1 1
#define P2 2
#define EMPATE 3
#define X 'X'
#define O 'O'

//quadro
typedef struct quadro {
    char matriz[MAX][MAX];
} Quadro;

//player
typedef struct player {
    int id;
    int score;
} Player;

//FUNCAO QUE INICIALIZA O QUADRO
void resetaQuadro(Quadro *quadro) {
    int i = 0, j = 0;

    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            quadro->matriz[i][j] = ' ';
        }
    }
}

//FUNCAO QUE INICIALIZA O GAME
void inicializar(Player *player1, Player *player2, Quadro *quadro) {
    player1->id = P1;
    player2->id = P2;

    player1->score = 0;
    player2->score = 0;

    resetaQuadro(quadro);
}

//FUNCAO QUE DESENHA O QUADRO
void desenhaQuadro(Quadro quadro) {
    int i = 0, j = 0;

    system("clear || cls");

    for (i = 0; i < MAX-1; i++) {
        printf("%c | %c | %c\n", quadro.matriz[i][0], quadro.matriz[i][1], quadro.matriz[i][2]);
        printf("---------\n");
    }

    printf("%c | %c | %c\n", quadro.matriz[i][0], quadro.matriz[i][1], quadro.matriz[i][2]);
}

//FUNCAO QUE DESENHA O SCORE
void desenhaScore(int score1, int score2) {
    printf("\nPLACAR\n");
    printf("PLAYER 1: %d    PLAYER 2: %d\n\n", score1, score2);
}

//DESENHA TUDO
void desenhaTudo(Quadro quadro, Player player1, Player player2) {
    desenhaQuadro(quadro);
    desenhaScore(player1.score, player2.score);
}

//FUNCAO QUE VERIFICA SE O JOGO TERMINOU
int terminouGame(Quadro quadro) {
    int i = 0;
    
    //verifica se teve alguma coluna com todos os caracteres iguais
    for (i = 0; i < MAX; i++) {
        if ((quadro.matriz[0][i] == X) && (quadro.matriz[1][i] == X) && (quadro.matriz[2][i] == X)) {
            return P1;
        }
        if ((quadro.matriz[0][i] == O) && (quadro.matriz[1][i] == O) && (quadro.matriz[2][i] == O)) {
            return P2;
        }
    }

    //verifica se teve alguma linha com todos os caracteres iguais
    for (i = 0; i < MAX; i++) {
        if ((quadro.matriz[i][0] == X) && (quadro.matriz[i][1] == X) && (quadro.matriz[i][2] == X)) {
            return P1;
        }
        if ((quadro.matriz[i][0] == O) && (quadro.matriz[i][1] == O) && (quadro.matriz[i][2] == O)) {
            return P2;
        }
    }

    //verifica diagonal principal
    if ((quadro.matriz[0][0] == X) && (quadro.matriz[1][1] == X) && (quadro.matriz[2][2] == X)) {
        return P1;
    }
    if ((quadro.matriz[0][0] == O) && (quadro.matriz[1][1] == O) && (quadro.matriz[2][2] == O)) {
        return P2;
    }

    //verifica a diagonal secundaria
    if ((quadro.matriz[0][2] == X) && (quadro.matriz[1][1] == X) && (quadro.matriz[2][0] == X)) {
        return P1;
    }
    if ((quadro.matriz[0][2] == O) && (quadro.matriz[1][1] == O) && (quadro.matriz[2][0] == O)) {
        return P2;
    }

    return -1;
}

//FUNCAO QUE CHECA SE TODO O QUADRO FOI PREENCHIDO
int preenchidoCompletamente(Quadro quadro) {
    int i = 0, j = 0;

    for (i = 0; i < MAX; i++) {
        for (j = 0; j < MAX; j++) {
            if (quadro.matriz[i][j] == ' ') {
                return 0;
            }
        }
    }

    return 1;
}

//FUNCAO QUE REALIZA A JOGADA
int jogada(Player player, int linha, int coluna, Quadro *quadro) {
    if (quadro->matriz[linha][coluna] == ' ') {
        if (player.id == P1) {
            quadro->matriz[linha][coluna] = X;
        } else {
            quadro->matriz[linha][coluna] = O;
        }

        return 1;
    }

    return 0;
}

//FUNCAO QUE FAZ A LEITURA DA LINHA
int lerLinha() {
    int linha = 0;
    
    do {
        printf("Linha: ");
        scanf("%d", &linha);
        if (linha < 1 || linha > 3) {
            printf("Error: linha invalida!\n");
            printf("Tente novamente.\n");
        }
    } while (linha < 1 || linha > 3);

    return linha;
}

//FUNCAO QUE FAZ A LEITURA DA COLUNA
int lerColuna() {
    int coluna = 0;

    do {
        printf("Coluna: ");
        scanf("%d", &coluna);
        if (coluna < 1 || coluna > 3) {
            printf("Error: coluna invalida!\n");
            printf("Tente novamente.\n");
        }
    } while (coluna < 1 || coluna > 3);

    return coluna;
}


//GAME
int main() {
    Quadro quadro;
    Player player1, player2;
    int linha = 0, coluna = 0;
    int novo_game = 1, fim_jogo = 0;
    int resultado = -1, tmp = 0;

    inicializar(&player1, &player2, &quadro);
    while (novo_game == 1) {
        //inicializa o game
        resetaQuadro(&quadro);
        desenhaTudo(quadro, player1, player2);
        fim_jogo = 0;
        resultado = -1;

        //realiza as jogadas
        while (!fim_jogo) {
            if (resultado == -1) {
                printf("Jogada do Player 1\n");

                do {
                    linha = lerLinha() - 1;
                    coluna = lerColuna() - 1;
                    tmp = jogada(player1, linha, coluna, &quadro);

                    if (!tmp) {
                        printf("Error: jogada invalida!\n");
                        printf("Tente novamente.\n");
                    }
                } while (!tmp);

                desenhaTudo(quadro, player1, player2);
                if (preenchidoCompletamente(quadro)) {
                    break;
                }
                resultado = terminouGame(quadro);
            }
            
            
            if (resultado == -1) {
                printf("Jogada do Player 2\n");
                
                do {
                    linha = lerLinha() - 1;
                    coluna = lerColuna() - 1;
                    tmp = jogada(player2, linha, coluna, &quadro);
                    if (!tmp) {
                        printf("Error: jogada invalida!\n");
                        printf("Tente novamente.\n");
                    }
                } while (!tmp);

                desenhaTudo(quadro, player1, player2);
                if (preenchidoCompletamente(quadro)) {
                    break;
                }
                resultado = terminouGame(quadro);
            }

            if (resultado != -1) {
                fim_jogo = 1;
                
                if (resultado == P1) {
                    player1.score++;
                } else if (resultado == P2) {
                    player2.score++;
                }

                desenhaTudo(quadro, player1, player2);
            }
        }

        //novo game?
        do {
            printf("Realizar um novo game?\n");
            printf("1 - SIM     2 - NAO\n");
            scanf("%d", &novo_game);
            if (novo_game != 1 && novo_game != 2) {
                printf("Error: opcao invalida!\n");
                printf("Tente novamente.\n");
            }
        } while (novo_game != 1 && novo_game != 2);
    }

    return 0;
}