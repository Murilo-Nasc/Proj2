#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int opcao;

  printf("BEM VINDO AO RPG\n");

  while (1){
    printf("1. Começar Uma Nova Jornada\n2. Continuar Sua Jornada\n3. Sair\n");
    scanf("%d", &opcao);

    switch (opcao){
      case 1:
        break;
      case 2:
        break;
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