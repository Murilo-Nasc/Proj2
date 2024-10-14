#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "funcoes.h"

int main(void) {
  int opcao;
  Player info_player;
  info_player.lvl = -1; // Salva um nível padrão -1 para futura verificação da existência de um player salvo

  carregar_player(&info_player);


  printf("BEM VINDO AO RPG\n");
  while (1){
    printf("1. Começar Uma Nova Jornada\n2. Continuar Sua Jornada\n3. Sair\n");
    scanf("%d", &opcao);

    switch (opcao){
      case 1:
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

  return 0;
}