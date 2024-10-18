#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>
#include <string.h>

typedef struct {
  char nome[50];
  float vida_max;
  float vida_atual;
  int lvl;
  float exp_max;
  float exp_atual;
  int ataque;
  int andar;
} Player;

typedef struct {
    char nome[50];
    float vida_max;
    float vida_atual;
    int ataque;
} Inimigo;

void salvar_player(Player *info_player);
void carregar_player(Player *info_player);
void criar_player(Player *info_player);
Inimigo criar_inimigo(int tipo);

#endif