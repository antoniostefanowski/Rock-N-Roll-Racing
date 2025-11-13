#define _CRT_SECURE_NO_WARNINGS
#include "raylib.h"
#include <stdio.h>  
#include <string.h> 
#define MAP_LINES 20
#define MAP_COLS 80  
#define ESCALA 10


int largura_tela = MAP_COLS * ESCALA;
int comprimento_tela = (MAP_LINES * ESCALA) + 60; //O + 60 é para adicionar a parte da vida e voltas 
int comprimento_jogo = MAP_LINES * ESCALA;

//Matriz mapa(espelho txt)
char mapa[MAP_LINES][MAP_COLS];

void carregarMapa(char* nomeArquivo);
void desenharMapa(void);

int main(){
   
    InitWindow(largura_tela, comprimento_tela, "Rock N Roll Racing");
    carregarMapa("testepista.txt");

   
    while (!WindowShouldClose()) {
       
        BeginDrawing(); 

        desenharMapa();

        EndDrawing();
    }

    CloseWindow(); 

    return 0;
}

//funcao carregar mapa
void carregarMapa(char* nomeArquivo){

    FILE* arquivo = fopen(nomeArquivo, "r");

    if (arquivo ==  NULL){
        printf("ERRO: Nao foi possivel abrir o arquivo %s\n", nomeArquivo);
        return; 
    }

    printf("Carregando mapa %s...\n", nomeArquivo);

    // +2 para o '\n' no final da linha e o '\0' do C
    char temp[MAP_COLS + 2];

    for (int i = 0; i < MAP_LINES; i++){

        if (fgets(temp, sizeof(temp), arquivo) != NULL){

            strncpy(mapa[i], temp, MAP_COLS);
        }
    }

    fclose(arquivo); 
    printf("Mapa carregado com sucesso.\n");
}

//função desenhar mapa
void desenharMapa(){

    for (int i = 0; i < MAP_LINES; i++){
        for (int j = 0; j < MAP_COLS; j++){
            
            char tijolo = mapa[i][j];
            int posX = j * ESCALA; // Coluna * escala
            int posY = i * ESCALA; // Linha * escala

            
            switch (tijolo){
                case 'p': 
                    DrawRectangle(posX, posY, ESCALA, ESCALA, GRAY); 
                    break;
                case 'L':
                    DrawRectangle(posX, posY, ESCALA, ESCALA, WHITE); 
                    break;
                case 'j': 
                    DrawRectangle(posX, posY, ESCALA, ESCALA, BLUE);
                    break;
                case 'i': 
                    DrawRectangle(posX, posY, ESCALA, ESCALA, RED); 
                    break;
                case ' ': 
                    DrawRectangle(posX, posY, ESCALA, ESCALA, LIGHTGRAY); 
                    break;
                default:  
                    DrawRectangle(posX, posY, ESCALA, ESCALA, LIGHTGRAY); 
                    break;
            }
        }
    }
}