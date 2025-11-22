#include <raylib.h>
#include <stdio.h>
#include <math.h>

#define VELOCIDADE_MAXIMA 5.0f
#define ACELERACAO 0.1f
#define ROTACAO_VELOCIDADE 3.0f
#define ATRITO 0.98f

typedef struct Carro {
    Vector2 posicao;      // Posição (x, y) do carro na TELA (em pixels)
    Vector2 velocidade;   // Velocidade (x, y)
    float angulo;         // Direção para onde o carro aponta (em graus)
    float velocidadeLinear;
    int vida;
    int voltas;
    // int inventario(pra depois)
} CARRO;


CARRO g_jogador;

void AtualizarPosicao(void) {
    // 1. Rotação (A e D)
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
        g_jogador.angulo = g_jogador.angulo - ROTACAO; //girando no sentido antihorario, por isso o menos
    }
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
        g_jogador.angulo = g_jogador.angulo + ROTACAO; //girando no sentido horario, por isso soma
    }



    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
        g_jogador.velocidadeLinear = g_jogador.velocidadeLinear + ACELERACAO;
    }
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) {
        g_jogador.velocidadeLinear = g_jogador.velocidadeLinear - ACELERACAO;
    }

    // 3. Limites de Velocidade e Atrito
    if (g_jogador.velocidadeLinear > VELOCIDADE_MAXIMA) g_jogador.velocidadeLinear = VELOCIDADE_MAXIMA;
    if (g_jogador.velocidadeLinear < -VELOCIDADE_MAXIMA/2) g_jogador.velocidadeLinear = -VELOCIDADE_MAXIMA/2; // Ré é mais lenta

    // Aplica atrito (o carro para sozinho se soltar W)
    g_jogador.velocidadeLinear *= ATRITO;

    // 4. A Mágica da Matemática (Converter Angulo+Velocidade em X e Y)
    // DEG2RAD é uma constante da Raylib para converter Graus em Radianos
    g_jogador.velocidade.x = cos(g_jogador.angulo * DEG2RAD) * g_jogador.velocidadeLinear;
    g_jogador.velocidade.y = sin(g_jogador.angulo * DEG2RAD) * g_jogador.velocidadeLinear;

    // 5. Atualiza a Posição
    g_jogador.posicao.x += g_jogador.velocidade.x;
    g_jogador.posicao.y += g_jogador.velocidade.y;
}

