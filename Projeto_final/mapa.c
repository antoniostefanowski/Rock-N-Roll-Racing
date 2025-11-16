#include <raylib.h>
#include <stdio.h>

// Dimensões do mapa em "blocos"
#define MAP_LINES 20
#define MAP_COLS  80

// Tamanho de cada bloco em pixels na tela
#define BLOCK_SIZE 20

#define HUD_HEIGHT 100 //A HUD EH A AREA PRETA EMBAIXO
// Tamanho da tela (calculado a partir do mapa)
#define SCREEN_WIDTH (MAP_COLS * BLOCK_SIZE)
#define SCREEN_HEIGHT ((MAP_LINES * BLOCK_SIZE) + HUD_HEIGHT)
// NOTA: O trabalho pede uma área de HUD embaixo,
// então você pode querer SCREEN_HEIGHT (MAP_LINES * BLOCK_SIZE) + 200

// Variável global ou passada como parâmetro
char g_mapa[MAP_LINES][MAP_COLS];

// Função para carregar o mapa do arquivo
void CarregarMapa(const char *fileNome)
{
    FILE *arquivo = fopen(fileNome, "r");
    if (arquivo == NULL)
    {
        TraceLog(LOG_ERROR, "Nao foi possivel abrir o arquivo do mapa: %s", fileNome); // **********
        return;
    }

    for (int i = 0; i < MAP_LINES; i++)
    {
        for (int j = 0; j < MAP_COLS; j++)
        {
            char c = fgetc(arquivo);
            if (c == '\n' || c == EOF)   // Se a linha acabar antes, quebra
            {
                break;
            }
            g_mapa[i][j] = c; // pq igualar a c??????
        }
        // Pula o resto da linha até o '\n' (para garantir)
        while (fgetc(arquivo) != '\n' && !feof(arquivo));
    }

    fclose(arquivo);
}
// Função para desenhar o mapa na tela
void DesenhaMapa(void)
{
    for (int i = 0; i < MAP_LINES; i++)
    {
        for (int j = 0; j < MAP_COLS; j++)
        {

            int posX = j * BLOCK_SIZE;
            int posY = i * BLOCK_SIZE;

            // cor que define um "ERRO"
            Color cor = (Color)
            {
                190, 190, 150, 255
            }; // Se não for nada, pinte de cinza
            switch (g_mapa[i][j]) // eh como se pegasse o caracter que esta na linha i e coluna j e aplicasse os cases
            {
            case 'p':
                cor = (Color)
                {
                    139, 69, 19, 255
                }; //especificamos a tonalidade do marrom
                break;

            case ' ':
                cor = (Color)
                {
                    190, 190, 150, 255
                }; //especificamos a tonalidade do cinza
                break;
            case 'L':
                cor = BLACK;
                break;

            }

            DrawRectangle(posX, posY, BLOCK_SIZE, BLOCK_SIZE, cor); // funcao que desenha, dentro tem (pos x, pos y, largura, altura, cor)
        }
    }
}

int main(void)
{

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Meu Jogo - O Mapa"); //funcao que inicializa a janela, dentro tem (largura , altura, titulo)
    SetTargetFPS(60); // diz pro pc rodar em 60 fps, ou pelo menos tentar, caso ele n tenha essa capacidade

    // 2. Carregar dados (fora do loop)
    CarregarMapa("pista1.txt"); // Use o nome do seu arquivo

    // 3. Game Loop
    while (!WindowShouldClose()) // **********
    {
        // 4. Atualizar lógica (ainda não temos)
        // ...

        // 5. Desenhar
        BeginDrawing(); // **********
        ClearBackground(BLACK); // **********

        DesenhaMapa(); // Chama sua função de desenho


        EndDrawing();
    }

    // 6. Finalização
    CloseWindow();
    return 0;

}







