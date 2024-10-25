#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct {
  char nome[50];
  float vida_max;
  float vida_atual;
  int lvl;
  float exp_max;
  float exp_atual;
  int ataque;
  int andar;
  int pocoes;
  int dano_espada;
} Player;

typedef struct {
    char nome[50];
    float vida_max;
    float vida_atual;
    int ataque;
    int exp;
} Inimigo;

// ARQUIVAMENTO DO PLAYER
void salvar_player(Player *info_player);
void carregar_player(Player *info_player);
void criar_player(Player *info_player);
// COMBATE
Inimigo criar_inimigo(int tipo, Player player);
void combate(Player *player);
void atacar(Player *jogador, Inimigo *inimigo, int acao_inimigo);
void ataque_inim(Inimigo *inimigo, Player *player, int defesa_player);
void usar_pocao(Player *player);
// ANDARES/ENCONTROS
int* gerar_encontros(int *total_encontros);
void embaralhar(int *array, int tamanho);
void funcao_morte();
void bau(Player *player);
void upar_lvl(Player *player);
// BOSS
void criar_boss(Player *player);
void combate_criatura_abismo(Inimigo inimigo, Player *player);
void combate_maquina_combate(Inimigo inimigo, Player *player);
void combate_colosso_mortovivo(Inimigo inimigo, Player *player);
// HISTÓRICO
void historico(Player *player, char inimigo[]);
void consultar_historico();

#endif