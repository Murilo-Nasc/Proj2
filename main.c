#include <stdio.h>
#include <stdlib.h>

int main(void) {
  int opcao;

  printf("BEM VINDO AO RPG\n");

  while (1){
    printf("1. Começar Sua Jornada\n2. Sair\n");
    scanf("%d", &opcao);
    
    switch (opcao){
      case 1:
        break;
      case 2:
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