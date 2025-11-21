#ifndef FUNCOES_H
#define FUNCOES_H

#include "structs.h"

// Cores para terminal ANSI
#define COR_RESET    "\x1B[0m"
#define COR_VERMELHO "\x1B[31m"
#define COR_VERDE    "\x1B[92m"
#define COR_AMARELO  "\x1B[93m"
#define COR_AZUL     "\x1B[34m"
#define COR_ROXO     "\x1B[35m"

// Utilitarios
void limpar_tela();
void pausar_tela();

// Narrativa
void introducao();
void exibir_boot_sequence();
void prologo_historia();
void menu_dialogo(Capanga *equipe);

// Mapa e Missão
void resetar_mapa(char mapa[4][4]);
void gerar_missao_mapa(char mapa[4][4], int *missao_x, int *missao_y);
void exibir_mapa(char mapa[4][4]);

// Lógica do Jogo
void resolver_missao(Capanga *escolhido, int mx, int my);
void evento_interacao(Capanga *c, int *animo_equipe);

// --- NOVAS FUNÇÕES OBRIGATÓRIAS ---

// Arquivos
void salvar_jogo(Capanga *lista, int quantidade);
int carregar_jogo(Capanga *lista, int quantidade);

// Recursão (Hackear)
// ATUALIZADO: Agora aceita ponteiro para a equipe
void tentar_hackear_sistema(Capanga *equipe);


#endif