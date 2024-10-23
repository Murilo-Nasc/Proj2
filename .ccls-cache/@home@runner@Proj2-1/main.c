#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "funcoes.h"

int main(void) {
  int opcao, opcao_inimigo;
  char lixo;
  Player info_player;
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

  // EXPLORAÇÃO
  while (1) {
    printf("\nANDAR %d\n", info_player.andar);
    int total_encontros;
    int *encontros = gerar_encontros(&total_encontros);
    // Andar de Boss
    if (info_player.andar % 5 == 0) {
      while (1) {
        printf("\nVocê está entrando em um salão de boss! Deseja usar uma poção (%d)?\n", info_player.pocoes);
        scanf("%d", &opcao);
        scanf("%c", &lixo);
        if (opcao == 1) {usar_pocao(&info_player); break;}
        else if (opcao == 2) {printf("Nenhuma poção foi usada.\n"); break;}
        else if (opcao != 2) {printf("Opção Inválida"); continue;}
      }
      criar_boss(&info_player);
    }
    // Andar Normal
    else {
      for (int i = 0; i < total_encontros; i++) {
        if (encontros[i] == 1) {
          combate(&info_player);
          if (info_player.vida_atual <= 0) {
            break;
          }
        } 
        else if (encontros[i] == 2) {
          bau(&info_player);
          //Lógica do baú
        }
      }
    }
    
    if (info_player.vida_atual <= 0) {
      printf("Você morreu!\n");
      funcao_morte();
      break;
    }
    
    printf("Andar Concluído!\n");
    while (1) {
      printf("Deseja continuar?\n1. Sim\n2. Não\n");
      scanf("%d", &opcao);
      scanf("%c", &lixo);
      if (opcao == 1) {
        info_player.andar++;
        printf("Seguindo ao próximo andar...\n");
        break;
      }
      else if (opcao == 2) {
        info_player.andar++;
        salvar_player(&info_player);
        printf("Adeus!");
        break; 
      }
      else {
        printf("Opção Inválida.\n");
        continue;
      }
    }
    if (opcao == 2) {break;}
  }

  return 0;
}