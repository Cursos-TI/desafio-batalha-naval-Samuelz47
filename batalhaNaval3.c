#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define VALOR_AGUA 0
#define VALOR_NAVIO 3
#define VALOR_HABILIDADE 5

// Verifica se o navio pode ser posicionado sem sair do tabuleiro e sem sobrepor outro navio
int pode_posicionar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha;
        int c = coluna;

        if (diagonal == 1) {         // Diagonal ↘
            l += i;
            c += i;
        } else if (diagonal == 2) {  // Diagonal ↙
            l += i;
            c -= i;
        } else if (direcao == 0) {   // Horizontal →
            c += i;
        } else if (direcao == 1) {   // Vertical ↓
            l += i;
        }

        if (l < 0 || l >= TAMANHO_TABULEIRO || c < 0 || c >= TAMANHO_TABULEIRO)
            return 0;
        if (tabuleiro[l][c] != VALOR_AGUA)
            return 0;
    }
    return 1;
}

// Posiciona o navio no tabuleiro
void posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int direcao, int diagonal) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha;
        int c = coluna;

        if (diagonal == 1) {
            l += i;
            c += i;
        } else if (diagonal == 2) {
            l += i;
            c -= i;
        } else if (direcao == 0) {
            c += i;
        } else if (direcao == 1) {
            l += i;
        }

        tabuleiro[l][c] = VALOR_NAVIO;
    }
}

// Sobrepõe uma matriz de habilidade ao tabuleiro, centralizando na coordenada fornecida
void aplicar_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int habilidade[5][5], int origem_l, int origem_c) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (habilidade[i][j] == 1) {
                int l = origem_l + i - 2;
                int c = origem_c + j - 2;
                if (l >= 0 && l < TAMANHO_TABULEIRO && c >= 0 && c < TAMANHO_TABULEIRO) {
                    if (tabuleiro[l][c] == VALOR_AGUA) {
                        tabuleiro[l][c] = VALOR_HABILIDADE;
                    }
                }
            }
        }
    }
}

// Constrói a matriz de habilidade Cone (↧ em pirâmide)
void construir_cone(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            habilidade[i][j] = 0;
        }
    }
    habilidade[0][2] = 1;
    habilidade[1][1] = habilidade[1][2] = habilidade[1][3] = 1;
    for (int j = 0; j < 5; j++)
        habilidade[2][j] = 1;
}

// Constrói a matriz de habilidade Cruz (+)
void construir_cruz(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            habilidade[i][j] = (i == 2 || j == 2) ? 1 : 0;
}

// Constrói a matriz de habilidade Octaedro (◊)
void construir_octaedro(int habilidade[5][5]) {
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            habilidade[i][j] = (abs(i - 2) + abs(j - 2) <= 2) ? 1 : 0;
}

// Exibe o tabuleiro com legenda
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nLegenda: 0 = Água | 3 = Navio | 5 = Área de Habilidade\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Posiciona os 4 navios
    if (pode_posicionar(tabuleiro, 0, 0, 0, 0))  // Horizontal
        posicionar_navio(tabuleiro, 0, 0, 0, 0);
    if (pode_posicionar(tabuleiro, 2, 4, 1, 0))  // Vertical
        posicionar_navio(tabuleiro, 2, 4, 1, 0);
    if (pode_posicionar(tabuleiro, 5, 1, 0, 1))  // Diagonal ↘
        posicionar_navio(tabuleiro, 5, 1, 0, 1);
    if (pode_posicionar(tabuleiro, 6, 8, 0, 2))  // Diagonal ↙
        posicionar_navio(tabuleiro, 6, 8, 0, 2);

    // Matrizes de habilidades
    int cone[5][5], cruz[5][5], octaedro[5][5];

    // Construção das áreas de efeito
    construir_cone(cone);
    construir_cruz(cruz);
    construir_octaedro(octaedro);

    // Aplicação das habilidades ao tabuleiro (centrado nas coordenadas)
    aplicar_habilidade(tabuleiro, cone, 3, 3);
    aplicar_habilidade(tabuleiro, cruz, 6, 5);
    aplicar_habilidade(tabuleiro, octaedro, 8, 2);

    // Exibe o resultado final
    exibir_tabuleiro(tabuleiro);

    return 0;
}
