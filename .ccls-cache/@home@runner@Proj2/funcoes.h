#ifndef FUNCOES_H
#define FUNCOES_H

#include <stdio.h>

typedef struct {
  char nome[50];
  int vida_max;
  int vida_atual;
  int lvl;
  int exp;
  int ataque;
} Player;

void salvar_player(Player *info_player);
void carregar_player(Player *info_player);

#endif