#include "funcoes.h" 

// FUNÇÕES DE ARQUIVAMENTO DE PLAYER

// Salvar Player
void salvar_player(Player *info_player) {
  FILE *file = fopen("player.bin", "wb");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo para salvar");
    return;
  }

  fwrite(info_player, sizeof(Player), 1, file);
  fclose(file);
}


// Carregar Player
void carregar_player(Player *info_player) {
  FILE *file = fopen("player.bin", "rb");
  if (file == NULL) {
    perror("Erro ao abrir o arquivo para salvar");
    return;
  }

  // Verificação se o arquivo está vazio
  fseek(file, 0, SEEK_END); 
  long tamanho = ftell(file); 
  if (tamanho == 0) {
    fclose(file);
    return;
  }
  fseek(file, 0, SEEK_SET);
  
  fread(info_player, sizeof(Player), 1, file);
  fclose(file);
}


// Criar Player
void criar_player(Player *info_player) {
  char nome_player[50];
  
  printf("Digite o nome do seu personagem: \n");
  fgets(nome_player, sizeof(nome_player), stdin);
  nome_player[strcspn(nome_player, "\n")] = '\0';

  // Salva infos novas no info_player
  strncpy(info_player->nome, nome_player, sizeof(info_player->nome) - 1);
  info_player->nome[sizeof(info_player->nome) - 1] = '\0';
  info_player->vida_max = 50;
  info_player->vida_atual = 50;
  info_player->lvl = 1;
  info_player->exp_max = 100;
  info_player->exp_atual = 0;
  info_player->ataque = 5;
  info_player->andar = 1;
  salvar_player(info_player);
}

