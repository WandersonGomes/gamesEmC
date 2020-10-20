/*
Autor: Wanderson Gomes da Costa
Data: 06 de Outubro de 2020
Implementacao do game do campo minado
*/
#include <stdio.h>
#include <stdlib.h>

#define DIM 8
#define QTD_MINES 10

//MINAS
typedef struct mine {
    int x;
    int y;
} Mine;

//CAMPO
typedef struct camp {
    int celulas[DIM][DIM];
    int abertas;
} Campo;

//JOGADA
typedef struct jog {
    int x;
    int y;
} Jogada;

//FUNCAO QUE VERIFICA SE AS COORDENADAS SAO VALIDAS
int coordenadaValida(int x, int y) {
    if (x < 0 || x >= DIM) {
        return 0;
    }
    if (y < 0 || y >= DIM) {
        return 0;
    }

    return 1;
}

//FUNCAO QUE INICIALIZA A MASCARA E O CAMPO
void inicializaCampoMascara(Campo* campo, Campo* mascara, Mine minas[QTD_MINES]) {
    int x = 0, y = 0, i = 0, j = 0;
    
    //zera tudo
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            mascara->celulas[i][j] = 1;
            campo->celulas[i][j] = 0;
        }
    }

    campo->abertas = 0;
    mascara->abertas = 0;

    //adiciona as minas
    for (i = 0; i < QTD_MINES; i++) {
        x = minas[i].x;
        y = minas[i].y;

        campo->celulas[x][y] = -1;
        
        //atualiza os indicadores ao redor
        if (coordenadaValida(x - 1, y - 1) && (campo->celulas[x-1][y-1] != -1))
            campo->celulas[x-1][y-1]++;

        if (coordenadaValida(x - 1, y) && (campo->celulas[x-1][y] != -1))
            campo->celulas[x-1][y]++;
        
        if (coordenadaValida(x - 1, y + 1) && (campo->celulas[x-1][y+1] != -1))
            campo->celulas[x-1][y+1]++;
        
        if (coordenadaValida(x, y - 1) && (campo->celulas[x][y-1] != -1))
            campo->celulas[x][y-1]++;
        
        if (coordenadaValida(x, y + 1) && (campo->celulas[x][y+1] != -1))
            campo->celulas[x][y+1]++;
        
        if (coordenadaValida(x + 1, y - 1) && (campo->celulas[x+1][y-1] != -1))
            campo->celulas[x+1][y-1]++;
        
        if (coordenadaValida(x + 1, y) && (campo->celulas[x+1][y] != -1))
            campo->celulas[x+1][y]++;
        
        if (coordenadaValida(x + 1, y + 1) && (campo->celulas[x+1][y+1] != -1))
            campo->celulas[x+1][y+1]++;
    }
}

//FUNCAO QUE APRESENTA O CAMPO MINADO (MASCARA)
void desenhaCampo(Campo campo, Campo mascara) {
    int i = 0, j = 0;
    system("clear || cls");

    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            if (mascara.celulas[i][j]) {
                printf(" # ");
            } else {
                printf(" %d ", campo.celulas[i][j]);
            }
        }
        printf("\n");
    }
}

//FUNCAO QUE LER A JOGADA
Jogada lerJogada() {
    Jogada jogada;
    
    printf("JOGADA\n");

    while (1) {
        printf("Linha: ");
        scanf("%d", &jogada.x);
        printf("Coluna: ");
        scanf("%d", &jogada.y);

        jogada.x--;
        jogada.y--;

        if (coordenadaValida(jogada.x, jogada.y) == 0) {
            printf("Error: jogada invalida!\n");
            printf("Tente novamente.\n");
        } else {
            break;
        }
    }

    return jogada;
}

//FUNCAO QUE REALIZA A JOGADA E VERIFICA SE TUDO OCORREU BEM
int realizaJogada(Jogada jogada, Campo campo) {
    if (campo.celulas[jogada.x][jogada.y] == -1) {
        return 0;
    }
    return 1;
}

//FUNCAO QUE ATUALIZA A MASCARA
void atualizaMascara(int x, int y, Campo* mascara, Campo campo) {
    if (coordenadaValida(x,y)) {
        if (mascara->celulas[x][y] == 1) {
            if (campo.celulas[x][y] > 0) {
                mascara->celulas[x][y] = 0;
                mascara->abertas++;
            } else if (campo.celulas[x][y] == 0) {
                mascara->celulas[x][y] = 0;
                mascara->abertas++;
                atualizaMascara(x - 1, y - 1, mascara, campo);
                atualizaMascara(x - 1, y, mascara, campo);
                atualizaMascara(x - 1, y + 1, mascara, campo);
                atualizaMascara(x, y - 1, mascara, campo);
                atualizaMascara(x, y + 1, mascara, campo); //ponto a observar
                atualizaMascara(x + 1, y - 1, mascara, campo);
                atualizaMascara(x + 1, y, mascara, campo);
                atualizaMascara(x + 1, y + 1, mascara, campo);
            }
        }
    }
}

//FUNCAO QUE RETORNA O STATUS DO GAME (0 continua) (1 venceu)
int estadoGame(Campo mascara) {
    return (mascara.abertas == ((DIM*DIM) - QTD_MINES)) ? 1 : 0;
}

//GAME
int main() {
    Campo campo, mascara;
    Mine minas[QTD_MINES];
    Mine mina;
    Jogada jogada;
    int estado_game = 0;

    mina.x = 1; mina.y = 5; //ok
    minas[0] = mina;

    mina.x = 2; mina.y = 4; //ok
    minas[1] = mina;

    mina.x = 3; mina.y = 5; //ok
    minas[2] = mina;
    
    mina.x = 4; mina.y = 1; //ok
    minas[3] = mina;

    mina.x = 4; mina.y = 7; //ok
    minas[4] = mina;

    mina.x = 5; mina.y = 2; //ok
    minas[5] = mina;

    mina.x = 6; mina.y = 0; //ok
    minas[6] = mina;

    mina.x = 6; mina.y = 1; //ok
    minas[7] = mina;

    mina.x = 7; mina.y = 0; //ok
    minas[8] = mina;

    mina.x = 7; mina.y = 1; //ok
    minas[9] = mina;

    inicializaCampoMascara(&campo, &mascara, minas);
    desenhaCampo(campo, mascara);

    while (1) {
        jogada = lerJogada();

        if (realizaJogada(jogada, campo)) {
            atualizaMascara(jogada.x, jogada.y, &mascara, campo);
            estado_game = estadoGame(mascara);
            if (estado_game == 1) {
                printf("VENCEDOR!\n");
                break;
            }
        } else {
            printf("GAME OVER!\n");
            break;
        }
        desenhaCampo(campo, mascara);
    }


    return 0;
}