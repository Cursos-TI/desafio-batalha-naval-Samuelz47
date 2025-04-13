#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

// Função para verificar se é possível posicionar o navio sem sair dos limites ou sobrepor outro
int pode_posicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha;
        int c = coluna;

        if (diagonal == 1) {         // Diagonal ↘ (linha++, coluna++)
            l += i;
            c += i;
        } else if (diagonal == 2) {  // Diagonal ↙ (linha++, coluna--)
            l += i;
            c -= i;
        } else if (direcao == 0) {   // Horizontal (coluna++)
            c += i;
        } else if (direcao == 1) {   // Vertical (linha++)
            l += i;
        }

        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO)
            return 0; // fora dos limites
        if (tabuleiro[l][c] != VALOR_AGUA)
            return 0; // sobreposição
    }
    return 1; // pode posicionar
}

// Função para posicionar o navio
void posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha;
        int c = coluna;

        if (diagonal == 1) {         // Diagonal ↘
            l += i;
            c += i;
        } else if (diagonal == 2) {  // Diagonal ↙
            l += i;
            c -= i;
        } else if (direcao == 0) {   // Horizontal
            c += i;
        } else if (direcao == 1) {   // Vertical
            l += i;
        }

        tabuleiro[l][c] = VALOR_NAVIO;
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Define as coordenadas e direções dos 4 navios
    // horizontal: direcao = 0 | vertical: direcao = 1
    // diagonal: diagonal = 1 (↘) ou 2 (↙)

    // Navio 1 - Horizontal
    int l1 = 0, c1 = 0;
    if (pode_posicionar(tabuleiro, l1, c1, 0, 0))
        posicionar_navio(tabuleiro, l1, c1, 0, 0);
    else {
        printf("Erro ao posicionar navio horizontal\n");
        return 1;
    }

    // Navio 2 - Vertical
    int l2 = 2, c2 = 4;
    if (pode_posicionar(tabuleiro, l2, c2, 1, 0))
        posicionar_navio(tabuleiro, l2, c2, 1, 0);
    else {
        printf("Erro ao posicionar navio vertical\n");
        return 1;
    }

    // Navio 3 - Diagonal ↘
    int l3 = 5, c3 = 1;
    if (pode_posicionar(tabuleiro, l3, c3, 0, 1))
        posicionar_navio(tabuleiro, l3, c3, 0, 1);
    else {
        printf("Erro ao posicionar navio diagonal ↘\n");
        return 1;
    }

    // Navio 4 - Diagonal ↙
    int l4 = 6, c4 = 8;
    if (pode_posicionar(tabuleiro, l4, c4, 0, 2))
        posicionar_navio(tabuleiro, l4, c4, 0, 2);
    else {
        printf("Erro ao posicionar navio diagonal ↙\n");
        return 1;
    }

    // Exibe o tabuleiro
    printf("\nTabuleiro de Batalha Naval:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
