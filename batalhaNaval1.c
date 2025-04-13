#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3

int main() {
    // Matriz representando o tabuleiro do jogo (10x10), inicializada com água (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Coordenadas iniciais dos navios
    int linha_horizontal = 2;
    int coluna_horizontal = 1;

    int linha_vertical = 5;
    int coluna_vertical = 7;

    // Posicionamento do navio horizontal
    // Verifica se ele cabe no tabuleiro
    if (coluna_horizontal + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            // Verifica se a posição já está ocupada
            if (tabuleiro[linha_horizontal][coluna_horizontal + i] != VALOR_AGUA) {
                printf("Erro: Sobreposição detectada ao posicionar navio horizontal.\n");
                return 1;
            }
        }
        // Preenche as posições do navio horizontal no tabuleiro
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha_horizontal][coluna_horizontal + i] = VALOR_NAVIO;
        }
    } else {
        printf("Erro: Navio horizontal não cabe no tabuleiro.\n");
        return 1;
    }

    // Posicionamento do navio vertical
    // Verifica se ele cabe no tabuleiro
    if (linha_vertical + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            // Verifica se a posição já está ocupada
            if (tabuleiro[linha_vertical + i][coluna_vertical] != VALOR_AGUA) {
                printf("Erro: Sobreposição detectada ao posicionar navio vertical.\n");
                return 1;
            }
        }
        // Preenche as posições do navio vertical no tabuleiro
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[linha_vertical + i][coluna_vertical] = VALOR_NAVIO;
        }
    } else {
        printf("Erro: Navio vertical não cabe no tabuleiro.\n");
        return 1;
    }

    // Exibição do tabuleiro no console
    printf("Tabuleiro de Batalha Naval:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}