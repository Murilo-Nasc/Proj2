#include "funcoes.h" 


// ARQUIVAMENTO DO PLAYER


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
  info_player->exp_max = 120;
  info_player->exp_atual = 0;
  info_player->ataque = 5;
  info_player->andar = 1;
  info_player->pocoes = 3;
  info_player->dano_espada = 2;
  salvar_player(info_player);
}


// COMBATE


// Criar Inimigo
Inimigo criar_inimigo(int tipo, Player player) {
  Inimigo inimigo;
  double poder = pow(1.05, player.andar);

  switch (tipo) {
    case 1: // Goblin
      strcpy(inimigo.nome, "Goblin");
      inimigo.vida_atual = inimigo.vida_max = (int)((rand() % 10 + 25) * poder);
      inimigo.ataque = 4 * poder;
      inimigo.exp = (int)((rand() % 10 + 10) * poder);
      break;
    case 2: // Slime
      strcpy(inimigo.nome, "Slime");
      inimigo.vida_atual = inimigo.vida_max = (int)((rand() % 10 + 20) * poder);
      inimigo.ataque = 3 * poder;
      inimigo.exp = (int)((rand() % 10 + 10) * poder);
      break;
    case 3: // Lobo
      strcpy(inimigo.nome, "Lobo");
      inimigo.vida_atual = inimigo.vida_max = (int)((rand() % 10 + 20) * poder);
      inimigo.ataque = 6 * poder;
      inimigo.exp = (int)((rand() % 15 + 10) * poder);
      break;
    case 4: // Esqueleto
      strcpy(inimigo.nome, "Esqueleto");
      inimigo.vida_atual = inimigo.vida_max = (int)((rand() % 10 + 30) * poder);
      inimigo.ataque = 4 * poder;
      inimigo.exp = (int)((rand() % 20 + 10) * poder);
      break;
    case 5: // Zumbi
      strcpy(inimigo.nome, "Zumbi");
      inimigo.vida_atual = inimigo.vida_max = (int)((rand() % 10 + 35) * poder);
      inimigo.ataque = 3 * poder;
      inimigo.exp = (int)((rand() % 10 + 10) * poder);
      break;
  }

  return inimigo;
}


// Combate
void combate(Player *player) {
  int opcao_inimigo = rand() % 5 + 1; // Entre 1 e 5
  Inimigo inimigo_atual = criar_inimigo(opcao_inimigo, *player);
  printf("\nVocê encontrou um %s!\n", inimigo_atual.nome);

  while (1) {
    printf("\nSua vida: %.2f/%.2f\n", player->vida_atual, player->vida_max);
    printf("Vida do %s: %.2f/%.2f\n", inimigo_atual.nome, inimigo_atual.vida_atual, inimigo_atual.vida_max);
    printf("\nEscolha uma ação:\n");
    printf("1. Atacar\n");
    printf("2. Defender\n");
    printf("3. Usar Poção (%d)\n", player->pocoes);

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
        printf("Você se defendeu!\n");
        break;
      case 3:
        if (player->pocoes > 0) {
          usar_pocao(player);
          break;
        } else {
          printf("Você não tem poções!\n");
          continue;
        }

      default:
        printf("Ação inválida! Tente novamente.\n");
        continue;
    }

    if (inimigo_atual.vida_atual <= 0) {
      printf("\nVocê derrotou o %s!\n", inimigo_atual.nome);
      printf("EXP ganho: %d\n", inimigo_atual.exp);
      player->exp_atual += inimigo_atual.exp;
      if (player->exp_atual >= player->exp_max) {
        upar_lvl(player);
      } 
      printf("\nEXP atual: %.2f/%.2f\n", player->exp_atual, player->exp_max);
      break;
    }

    if (acao_inimigo == 1) {
      ataque_inim(&inimigo_atual, player, defesa_player);
    } else if (acao_inimigo == 2) {
      printf("O %s defendeu!\n", inimigo_atual.nome);
    }

    if (player->vida_atual <= 0) {
      printf("\nVocê foi derrotado pelo %s!\n", inimigo_atual.nome);
      break;
    }

  }
}

// Atacar
void atacar(Player *jogador, Inimigo *inimigo, int acao_inimigo) {
  int dano_jogador = jogador->ataque + rand() % jogador->ataque + jogador->dano_espada;
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
    dano_inimigo = (int)(dano_inimigo / 1.6);
  }
  player->vida_atual -= dano_inimigo;
  printf("O/A %s atacou você e causou %d de dano!\n", inimigo->nome, dano_inimigo);
}


// Usar Poção
void usar_pocao(Player *player) {
  player->pocoes -= 1;
  player->vida_atual += (int)(player->vida_max * 0.6); // Recupera metade da vida
  if (player->vida_atual > player->vida_max) {
    player->vida_atual = player->vida_max;
  }
  printf("Você usou uma poção e recuperou vida! Vida atual: %.2f/%.2f\n", player->vida_atual, player->vida_max);
}


// ANDARES/ENCONTROS


// Geração de Encontros
int* gerar_encontros(int *total_encontros) {
  int num_combates = rand() % 3 + 4; // Entre 4 e 6
  int num_baus = rand() % 2 + 2;      // Entre 2 e 3
  *total_encontros = num_combates + num_baus;

  // Alocar memória para os encontros
  int *encontros = malloc(*total_encontros * sizeof(int));
  if (!encontros) {
    perror("Erro ao alocar memória para encontros");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < num_combates; i++) {
    encontros[i] = 1; // combate
  }
  for (int i = num_combates; i < *total_encontros; i++) {
    encontros[i] = 2; // baú
  }

  embaralhar(encontros, *total_encontros);
  return encontros;
}


// Embaralhar os Encontros
void embaralhar(int *array, int tamanho) {
    for (int i = tamanho - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
}


// Morte
void funcao_morte() {
  FILE *file = fopen("player.bin", "wb");
  if (file) {
    fclose(file); 
  } else {
    perror("Erro ao abrir o arquivo do jogador para esvaziar");
  }
}


// Baú
void bau(Player *player){
  int opcao, item, nova_espada;
  char lixo;
  printf("\nVocê encontrou um baú!\n");
  item = rand() % 10 + 1;
  if (item > 0 && item <= 6) {
    printf("Você encontrou uma poção de cura!\n");
    player->pocoes++;
  } else if (item <= 10 && item > 6) {
    nova_espada = (int)(rand() % 2 + 4) * pow(1.05, player->andar);
    printf("Você encontrou uma espada! (Dano = %d)\n", nova_espada);
    printf("Deseja trocar sua espada (Dano = %d) por esta?\n1. Sim\n2. Não\n", player->dano_espada);

    while (1) {
      scanf("%d", &opcao);
      scanf("%c", &lixo);
      if (opcao == 1) {
        player->dano_espada = nova_espada;
        printf("Espada trocada com sucesso!\n");
        break;
      }
      else if (opcao == 2) {
        printf("Espada mantida!\n");
        break;
      }
      else {
        printf("Opção inválida!\n");
      }
    }

  }

}


// Upar de Nível
void upar_lvl(Player *player) {
  player->lvl++;
  player->exp_atual -= player->exp_max;
  player->exp_max = (int)(player->exp_max * 1.2);
  player->vida_max += 5;
  player->vida_atual = player->vida_max;
  player->ataque += 1;
  printf("\nParabéns! Você subiu para o nível %d!\n", player->lvl);
}


// BOSS


// Criar Boss
void criar_boss(Player *player) {
  Inimigo inimigo;
  int tipo = rand() % 3 + 1;
  double poder = pow(1.05, player->andar);

  switch (tipo) {
    case 1: // Criatura do Abismo
      strcpy(inimigo.nome, "Criatura do Abismo");
      inimigo.vida_atual = inimigo.vida_max = (int)((rand() % 25 + 100) * poder);
      inimigo.ataque = 2 * poder;
      inimigo.exp = (int)((rand() % 20 + 40) * poder);
      combate_criatura_abismo(inimigo, player);
      break;
    case 2: // Máquina de Combate
      strcpy(inimigo.nome, "Máquina de Combate");
      inimigo.vida_atual = inimigo.vida_max = (int)((rand() % 25 + 150) * poder);
      inimigo.ataque = 4 * poder;
      inimigo.exp = (int)((rand() % 20 + 40) * poder);
      combate_maquina_combate(inimigo, player);
      break;
    case 3: // Colosso Morto-Vivo
      strcpy(inimigo.nome, "Colosso Morto-Vivo");
      inimigo.vida_atual = inimigo.vida_max = (int)((rand() % 25 + 200) * poder);
      inimigo.ataque = 4 * poder;
      inimigo.exp = (int)((rand() % 15 + 10) * poder);
      combate_colosso_mortovivo(inimigo, player);
      break;
  }
}


// Combate da Criatura do Abismo
void combate_criatura_abismo(Inimigo inimigo, Player *player) {
  int ataque_max = 20 + pow(1.05, player->andar);
  float variacao_ataque = inimigo.ataque;
  
  printf("\nVocê encontrou um chefão: A Criatura do Abismo!\n");

  while (1) {
    printf("\nSua vida: %.2f/%.2f\n", player->vida_atual, player->vida_max);
    printf("Vida da %s: %.2f/%.2f\n", inimigo.nome, inimigo.vida_atual, inimigo.vida_max);
    printf("\nEscolha uma ação:\n");
    printf("1. Atacar\n");
    printf("2. Defender\n");
    printf("3. Usar Poção (%d)\n", player->pocoes);

    int acao, acao_inimigo, defesa_player = 0;
    char lixo;
    scanf("%d", &acao);
    scanf("%c", &lixo);

    switch (acao) {
      case 1:
        atacar(player, &inimigo, acao_inimigo);
        break;
      case 2:
        defesa_player = 1;
        printf("Você se defendeu!\n");
        break;
      case 3:
        if (player->pocoes > 0) {
          usar_pocao(player);
          break;
        } else {
          printf("Você não tem poções!\n");
          continue;
        }

      default:
        printf("Ação inválida! Tente novamente.\n");
        continue;
    }

    if (inimigo.vida_atual <= 0) {
      printf("\nVocê derrotou a %s!\n", inimigo.nome);
      printf("EXP ganho: %d\n", inimigo.exp);
      player->exp_atual += inimigo.exp;
      if (player->exp_atual >= player->exp_max) {
        upar_lvl(player);
      } 
      printf("\nEXP atual: %.2f/%.2f\n", player->exp_atual, player->exp_max);
      bau(player);
      bau(player);
      break;
    }

    ataque_inim(&inimigo, player, defesa_player);

    if (variacao_ataque < ataque_max) {
      variacao_ataque = variacao_ataque * 1.10;
      inimigo.ataque = (int)(variacao_ataque);
      printf("A criatura do abismo está crescendo... (ataque aumentado)!\n");
    }
      
    if (player->vida_atual <= 0) {
      printf("\nVocê foi derrotado pelo %s!\n", inimigo.nome);
      break;
    }
  }
}


// Combate da Máquina de Combate
void combate_maquina_combate(Inimigo inimigo, Player *player) {
  int aquecimento = 3;
  int superaquecida = 0;

  printf("\nVocê encontrou um chefão: A Máquina de Combate!\n");

  while (1) {
    printf("\nSua vida: %.2f/%.2f\n", player->vida_atual, player->vida_max);
    printf("Vida da %s: %.2f/%.2f\n", inimigo.nome, inimigo.vida_atual, inimigo.vida_max);
    printf("\nEscolha uma ação:\n");
    printf("1. Atacar\n");
    printf("2. Defender\n");
    printf("3. Usar Poção (%d)\n", player->pocoes);

    int acao, acao_inimigo, defesa_player = 0;
    char lixo;
    scanf("%d", &acao);
    scanf("%c", &lixo);

    if (superaquecida) {
      acao_inimigo = 1;
    } 
    else {
      acao_inimigo = rand() % 2 + 1; // Escolhe entre atacar (1) ou defender (2)
    }
    
    switch (acao) {
      case 1:
        atacar(player, &inimigo, acao_inimigo);
        break;
      case 2:
        defesa_player = 1;
        printf("Você se defendeu!\n");
        break;
      case 3:
        if (player->pocoes > 0) {
          usar_pocao(player);
          break;
        } else {
          printf("Você não tem poções!\n");
          continue;
        }

      default:
        printf("Ação inválida! Tente novamente.\n");
        continue;
    }

    if (acao_inimigo == 1) {
      ataque_inim(&inimigo, player, defesa_player);
    } else if (acao_inimigo == 2) {
      printf("O %s defendeu!\n", inimigo.nome);
    }
    
    if (player->vida_atual <= 0) {
      printf("\nVocê foi derrotado pelo %s!\n", inimigo.nome);
      break;
    }
    
    if (inimigo.vida_atual <= 0) {
      printf("\nVocê derrotou a %s!\n", inimigo.nome);
      printf("EXP ganho: %d\n", inimigo.exp);
      player->exp_atual += inimigo.exp;
      if (player->exp_atual >= player->exp_max) {
        upar_lvl(player);
      } 
      printf("\nEXP atual: %.2f/%.2f\n", player->exp_atual, player->exp_max);
      bau(player);
      bau(player);
      break;
    }

    if (player->vida_atual <= 0) {
      printf("\nVocê foi derrotado pelo %s!\n", inimigo.nome);
      break;
    }

    aquecimento--;
    if (aquecimento == 0) {
      superaquecida = 1;
      inimigo.ataque *= 2.25; 
      printf("A Máquina está superaquecida!\n");
    }
    if (aquecimento == -2) {
      superaquecida = 0;
      inimigo.ataque /= 2;
      aquecimento = rand() % 3 + 2;
      printf("A Máquina esfriou!\n");
    }
  }
}


// Combate do Colosso Morto-Vivo
void combate_colosso_mortovivo(Inimigo inimigo, Player *player) {
  int frenesi = 0;

  printf("\nVocê encontrou um chefão: O Colosso Morto-Vivo!\n");

  while (1) {
    printf("\nSua vida: %.2f/%.2f\n", player->vida_atual, player->vida_max);
    printf("Vida da %s: %.2f/%.2f\n", inimigo.nome, inimigo.vida_atual, inimigo.vida_max);
    printf("\nEscolha uma ação:\n");
    printf("1. Atacar\n");
    printf("2. Defender\n");
    printf("3. Usar Poção (%d)\n", player->pocoes);

    int acao, acao_inimigo, defesa_player = 0;
    char lixo;
    scanf("%d", &acao);
    scanf("%c", &lixo);

    if (frenesi) {
      acao_inimigo = 1;
    } 
    else {
      acao_inimigo = rand() % 2 + 1; // Escolhe entre atacar (1) ou defender (2)
    }

    switch (acao) {
      case 1:
        atacar(player, &inimigo, acao_inimigo);
        break;
      case 2:
        defesa_player = 1;
        printf("Você se defendeu!\n");
        break;
      case 3:
        if (player->pocoes > 0) {
          usar_pocao(player);
          break;
        } else {
          printf("Você não tem poções!\n");
          continue;
        }

      default:
        printf("Ação inválida! Tente novamente.\n");
        continue;
    }

    if (acao_inimigo == 1) {
      ataque_inim(&inimigo, player, defesa_player);
      if (frenesi) {ataque_inim(&inimigo, player, defesa_player);}
    } else if (acao_inimigo == 2) {
      printf("O %s defendeu!\n", inimigo.nome);
    }

    if (player->vida_atual <= 0) {
      printf("\nVocê foi derrotado pelo %s!\n", inimigo.nome);
      break;
    }

    if (inimigo.vida_atual <= 0 && frenesi == 0) {
      inimigo.vida_atual += inimigo.vida_max * 0.5;
      frenesi = 1;
      printf("\nO Colosso Morto-Vivo reviveu e está em frenesi!\n");
    } else if (inimigo.vida_atual <= 0 && frenesi == 1) {
      printf("\nVocê derrotou a %s!\n", inimigo.nome);
      printf("EXP ganho: %d\n", inimigo.exp);
      player->exp_atual += inimigo.exp;
      if (player->exp_atual >= player->exp_max) {
        upar_lvl(player);
      } 
      printf("\nEXP atual: %.2f/%.2f\n", player->exp_atual, player->exp_max);
      bau(player);
      bau(player);
      break;
    }

    if (player->vida_atual <= 0) {
      printf("\nVocê foi derrotado pelo %s!\n", inimigo.nome);
      break;
    }

    
  }
}