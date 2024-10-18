#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"

int main(void) {
  int opcao, opcao_inimigo;
  char lixo;
  Player info_player;
  Inimigo inimigo_atual;
  info_player.lvl = -1; // Salva um nível padrão -1 para futura verificação da existência de um player salvo
  srand(time(NULL));

  carregar_player(&info_player);


  printf("BEM VINDO AO RPG\n");
  while (1) {
    printf("1. Começar Uma Nova Jornada\n2. Continuar Sua Jornada\n3. Sair\n");
    scanf("%d", &opcao);
    scanf("%c", &lixo);

    switch (opcao) {
      case 1:
        criar_player(&info_player);
        break;
      
      case 2:
        if (info_player.lvl == -1) {
          printf("Não há jogo salvo.\n");
          continue;
        }
        else {
          break;
        }
      
      case 3:
        printf("Saindo...\n");
        return 0;
      
      default:
        printf("Opção Inválida.\n");
        continue;
    }
    break;
  }

  system("clear");

  // LUTA
  opcao_inimigo = rand() % 5 + 1; // Entre 1 e 5
  inimigo_atual = criar_inimigo(opcao_inimigo);
  printf("Você encontrou um %s!\n", inimigo_atual.nome);
  
  return 0;
}