#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define o tamanho do tabuleiro
#define SIZE 8

// Inicializa o tabuleiro com as peças de xadrez
void inicializarTabuleiro(char tabuleiro[SIZE][SIZE]) {
    // Peças brancas
    const char *pecasBrancas = "RNBQKBNR";
    const char *peoesBrancos = "PPPPPPPP";
    // Peças pretas
    const char *pecasPretas = "rnbqkbnr";
    const char *peoesPretos = "pppppppp";

    // Linha das peças
    for (int i = 0; i < SIZE; i++) {
        tabuleiro[0][i] = pecasPretas[i];
        tabuleiro[1][i] = peoesPretos[i];
        tabuleiro[6][i] = peoesBrancos[i];
        tabuleiro[7][i] = pecasBrancas[i];
    }

    // Espaços vazios
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < SIZE; j++) {
            tabuleiro[i][j] = '.';
        }
    }
}

// Mostra o tabuleiro no console
void mostrarTabuleiro(char tabuleiro[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", SIZE - i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("  a b c d e f g h\n");
}

// Converte a entrada do jogador em coordenadas do tabuleiro
bool converterCoordenadas(char col, int lin, int *x, int *y) {
    if (col < 'a' || col > 'h' || lin < 1 || lin > 8) {
        return false;
    }
    *x = 8 - lin;
    *y = col - 'a';
    return true;
}

// Move uma peça, se possível
bool moverPeca(char tabuleiro[SIZE][SIZE], int xOrig, int yOrig, int xDest, int yDest, bool turnoBranco) {
    char peca = tabuleiro[xOrig][yOrig];
    char destino = tabuleiro[xDest][yDest];

    if (peca == '.' || (turnoBranco && peca >= 'a' && peca <= 'z') || 
        (!turnoBranco && peca >= 'A' && peca <= 'Z')) {
        return false;
    }

    // Simplesmente permite qualquer movimento no momento
    tabuleiro[xDest][yDest] = peca;
    tabuleiro[xOrig][yOrig] = '.';

    return true;
}

int main() {
    char tabuleiro[SIZE][SIZE];
    inicializarTabuleiro(tabuleiro);

    bool turnoBranco = true; // Branco começa
    while (true) {
        mostrarTabuleiro(tabuleiro);
        printf("Turno do jogador %s. Digite o movimento (ex: e2 e4): ", turnoBranco ? "Branco" : "Preto");
        char colOrig, colDest;
        int linOrig, linDest;
        scanf(" %c%d %c%d", &colOrig, &linOrig, &colDest, &linDest);

        int xOrig, yOrig, xDest, yDest;
        if (!converterCoordenadas(colOrig, linOrig, &xOrig, &yOrig) || 
            !converterCoordenadas(colDest, linDest, &xDest, &yDest)) {
            printf("Movimento inválido. Tente novamente.\n");
            continue;
        }

        if (!moverPeca(tabuleiro, xOrig, yOrig, xDest, yDest, turnoBranco)) {
            printf("Movimento inválido. Tente novamente.\n");
            continue;
        }

        // Alterna o turno
        turnoBranco = !turnoBranco;
    }

    return 0;
}