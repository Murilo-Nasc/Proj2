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


// COMBATE


// Criar Inimigo
Inimigo criar_inimigo(int tipo) {
  Inimigo inimigo;

  switch (tipo) {
    case 1: // Goblin
      strcpy(inimigo.nome, "Goblin");
      inimigo.vida_max = 30;
      inimigo.vida_atual = 30;
      inimigo.ataque = 4;
      break;
    case 2: // Slime
      strcpy(inimigo.nome, "Slime");
      inimigo.vida_max = 25;
      inimigo.vida_atual = 25;
      inimigo.ataque = 3;
      break;
    case 3: // Lobo
      strcpy(inimigo.nome, "Lobo");
      inimigo.vida_max = 25;
      inimigo.vida_atual = 25;
      inimigo.ataque = 6;
      break;
    case 4: // Esqueleto
      strcpy(inimigo.nome, "Esqueleto");
      inimigo.vida_max = 35;
      inimigo.vida_atual = 35;
      inimigo.ataque = 5;
      break;
    case 5: // Zumbi
      strcpy(inimigo.nome, "Zumbi");
      inimigo.vida_max = 40;
      inimigo.vida_atual = 40;
      inimigo.ataque = 4;
      break;
    default:
      strcpy(inimigo.nome, "Desconhecido");
      inimigo.vida_max = 0;
      inimigo.vida_atual = 0;
      inimigo.ataque = 0;
      break;
  }

  return inimigo;
}

// Combate
void combate(Player *player) {
  int opcao_inimigo = rand() % 5 + 1; // Entre 1 e 5
  Inimigo inimigo_atual = criar_inimigo(opcao_inimigo);
  printf("Você encontrou um %s!\n", inimigo_atual.nome);
  
  while (1) {
    printf("\nSua vida: %.2f/%.2f\n", player->vida_atual, player->vida_max);
    printf("Vida do %s: %.2f/%.2f\n", inimigo_atual.nome, inimigo_atual.vida_atual, inimigo_atual.vida_max);
    printf("\nEscolha uma ação:\n");
    printf("1. Atacar\n");
    printf("2. Defender\n");
    printf("3. Usar Poção\n");

    int acao, acao_inimigo, defesa_player = 0;
    char lixo;
    scanf("%d", &acao);
    scanf("%c", &lixo);
    
    acao_inimigo = rand() % 2 + 1; // Escolhe entre atacar (1) ou defender (2)
    
    switch (acao) {
      case 1:
        atacar(player, &inimigo_atual, acao_inimigo);
        break;
      case 2:
        defesa_player = 1;
        break;
      case 3:
        // Lógica de poção
        break;
      default:
        printf("Ação inválida! Tente novamente.\n");
        continue;
    }

    if (inimigo_atual.vida_atual <= 0) {
      printf("Você derrotou o %s!\n", inimigo_atual.nome);
      break;
    }
    
    if (acao_inimigo == 1) {
      ataque_inim(&inimigo_atual, player, defesa_player);
    } else if (acao_inimigo == 2) {
      printf("O %s defendeu!\n", inimigo_atual.nome);
    }

    if (player->vida_atual <= 0) {
      printf("Você foi derrotado pelo %s!\n", inimigo_atual.nome);
      break;
    }
    
  }
}

// Atacar
void atacar(Player *jogador, Inimigo *inimigo, int acao_inimigo) {
  int dano_jogador = jogador->ataque + rand() % jogador->ataque;
  if (acao_inimigo == 2) {
    dano_jogador = (int)(dano_jogador / 1.5);
  }
  inimigo->vida_atual -= dano_jogador;
  printf("Você atacou o %s e causou %d de dano!\n", inimigo->nome, dano_jogador);
}

// Ataque Inimigo
void ataque_inim(Inimigo *inimigo, Player *player, int defesa_player) {
  int dano_inimigo = inimigo->ataque + rand() % inimigo->ataque;
  if (defesa_player) {
    dano_inimigo = (int)(dano_inimigo / 1.5);
  }
  player->vida_atual -= dano_inimigo;
  printf("O %s atacou você e causou %d de dano!\n", inimigo->nome, dano_inimigo);
}