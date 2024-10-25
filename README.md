# RPG em C

## Descrição

Este é um jogo de RPG simples desenvolvido em C, onde o jogador pode criar um personagem, explorar andares, enfrentar inimigos, coletar itens e lutar contra chefes. O jogo utiliza conceitos de combate, exploração e gerenciamento de recursos, como vida e poções.

## Funcionalidades

* **Criação de Personagem:** O jogador pode criar um novo personagem, definindo seu nome e iniciando sua jornada.
* **Exploração:** O jogador pode explorar andares, onde encontrará inimigos e baús com itens.
* **Combate:** Sistema de combate por turnos com inimigos variados, incluindo chefes.
* **Uso de Itens:** O jogador pode usar poções para recuperar vida e também pode trocar sua arma com as encontradas em baús.
* **Salvamento de Jogo:** O progresso do jogador é salvo em um arquivo ao parar em um andar, permitindo continuar a jornada posteriormente.
* **Histórico de Combate:** O jogo registra o histórico de partidas, mostrando dados do jogador (como nome, level e andar) e o inimigo que o derrotou.

## Tecnologias Utilizadas

- Linguagem C
- Bibliotecas padrão: 
  - **stdio.h:** Usada para entrada e saída, permitindo interações com o usuário através de `printf` e `scanf`.
  - **string.h:** Utilizada para manipulação de strings, essencial na criação e gerenciamento do personagem e inimigos.
  - **stdlib.h:** Empregada para alocação de memória e geração de números aleatórios, fundamental para a lógica de combate e eventos do jogo.
  - **time.h:** Utilizada para semear a geração de números aleatórios, garantindo diversidade em cada execução do jogo.
  - **math.h:** Usada para funções matemáticas, como cálculos de dano e vida, essenciais para a mecânica do combate.

## Compilação

O jogo é compilado usando o software do Replit a partir do arquivo `./main`.

## Como Executar

1. Siga as instruções na tela para criar um personagem e explorar.
2. Use as opções do menu para interagir com o jogo, iniciando uma nova jornada, continuando uma jornada salva, vendo o histórico de outras partidas ou saindo do jogo.

## Estrutura do Código

* **main.c:** Contém a lógica principal do jogo, incluindo o loop de jogo e opções de interação do usuário.
* **funcoes.h:** Declarações das funções utilizadas no jogo.
* **funcoes.c:** Implementações das funções que gerenciam a lógica do jogo, como combate, exploração e salvamento de fase.

## Dependências

Este jogo não possui dependências externas além do compilador C padrão.

## Membros

* Leonardo Bezzi Elias; RA: 24.124.045-6
* Murilo Gonçalves Nascimento; RA: 24.124.042-3

---

Divirta-se jogando e explorando!
