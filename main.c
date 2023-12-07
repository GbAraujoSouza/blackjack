#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedList.h"

#define true 1
#define false 0

typedef int bool;

typedef struct {
    char nome[100];
    pilhaDeCarta* cartas;
    int pontos;
    bool jogando;
} jogador;

void verificarJogadores(jogador* listaJogadores, int qntJogadores) {
    // verifica se algum jogador fez mais de 21 pontos e altera seu estado de jogo para false

    for (int i = 0; i < qntJogadores; i++) {
        if (listaJogadores[i].pontos > 21) {
            listaJogadores[i].jogando = false;
        }
    }
}

bool verificarGameOver(jogador* listaJogadores, int qntJogadores) {
    // verifica se todos os jogadores saíram, se todos perderam ou se alguém ganhou
    // retorna true se o jogo acabou

    // verifica ganhador
    for (int i = 0; i < qntJogadores; i++) {
        if (listaJogadores[i].pontos == 21) {
            return true;
        }
    }

    // verifica se todos saíram ou perderam
    int jogadoresRestantes = 0;
    for (int i = 0; i < qntJogadores; i++) {
        if (listaJogadores[i].jogando) {
            jogadoresRestantes++;
        }
    }
    if (jogadoresRestantes == 0){
        return true;
    }

    return false;
}

void printJogadores(jogador* listaJogadores, int qntJogadores) {
    // mostra os jogadores na tela
    // se o jogador fez mais de 21 pontos, será mostrado seu status de perdedor

    for (int j = 0; j < qntJogadores; j++) {
        printf("%s: ", listaJogadores[j].nome);
        printList(listaJogadores[j].cartas);
        printf("  Pontos --> %d", listaJogadores[j].pontos);
        // mostrar status de perdedor
        if (!listaJogadores[j].jogando && listaJogadores[j].pontos > 21) {
            printf("  [PERDEU]");
        } else if(!listaJogadores[j].jogando && listaJogadores[j].pontos < 21) {
            printf("  [PAROU]");
        }

        puts("");
    }
}

pilhaDeCarta* constroiBaralho() {
    char template[] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'D', 'J', 'Q', 'K' };
    char cartas[52];
    
    int i = 0;
    for (int j = 0; j < 13; j++) {
        for (int k = 0; k < 4; k++) {
            cartas[i] = template[j];
            i++;
        }
    }

    pilhaDeCarta* baralho = (pilhaDeCarta*)malloc(sizeof(pilhaDeCarta));
    initList(baralho);
    for (int carta = 51; carta > 0; carta--)
    {
        int indexAleatorio = rand() % carta + 1;
        append(baralho, cartas[indexAleatorio]);
        cartas[indexAleatorio] = cartas[carta];
    }
    return baralho;
}

int valorCarta(char carta) {
    int value;
    switch (carta) {
        case 'D':
        case 'J':
        case 'Q':
        case 'K':
            value = 10;
            break;
        case 'A':
            value = 1;
            break;
        default:
            value = (int)carta - '0';
            break;
    }
    return value;
}

void atualizarPontuacao(jogador* j) {
    if (listLength(j->cartas) == 2) {
        j->pontos += valorCarta(j->cartas->head->val);
    }
    j->pontos += valorCarta(j->cartas->tail->val);
}

int main() {

    // Gerador de numero aleatório
    time_t t1;
    srand ( (unsigned) time (&t1));

    // criar jogadores
    int qntJogadores;
    printf("Numero de Jogadores ");
    scanf("%d", &qntJogadores);
    while (qntJogadores < 2) {
        puts("Mínimo de 2 jogadores!");
        printf("Numero de Jogadores ");
        scanf("%d", &qntJogadores);
    }

    jogador* jogadores = (jogador*)malloc(qntJogadores * sizeof(jogador));
    if (!jogadores) {
        puts("Erro de alocação de memoria");
        return -1;
    }

    // inicializar baralho
    pilhaDeCarta* baralho = constroiBaralho();
    
    // inicializar jogadores
    for (int i = 0; i < qntJogadores; i++) {
        printf("Jogador %d nome: ", i + 1);
        scanf("%s", jogadores[i].nome);
        jogadores[i].jogando = true;
        jogadores[i].cartas = malloc(sizeof(pilhaDeCarta));
        initList(jogadores[i].cartas);
    }
    // cartas iniciais
    for (int i = 0; i < qntJogadores; i++) {
        append(jogadores[i].cartas, removeCarta(baralho));
        append(jogadores[i].cartas, removeCarta(baralho));
        atualizarPontuacao(&jogadores[i]);
    }

    bool gameOver = false;
    printJogadores(jogadores, qntJogadores);
    while(!gameOver) {

        // oferecer carta para cada jogador
        for (int i = 0; i < qntJogadores; i++) {
            if (jogadores[i].jogando) {
                char querNovaCarta;
                getchar();
                printf("%s quer mais uma carta? [s/n]: ", jogadores[i].nome);
                scanf("%c", &querNovaCarta);
                // checar input
                while (querNovaCarta != 's' && querNovaCarta != 'S' && querNovaCarta != 'n' && querNovaCarta != 'N') {
                    printf("Responda [s/n]: ");
                    scanf("%c", &querNovaCarta);
                }
                if (querNovaCarta == 's' || querNovaCarta == 'S') {
                    append(jogadores[i].cartas, removeCarta(baralho));
                    atualizarPontuacao(&jogadores[i]);
                } else {
                    jogadores[i].jogando = false;
                }
            }
        }

        // ordenar jogadores
        jogador aux;
        for(int ult = qntJogadores - 1; ult > 0; ult--) {
            for(int i=0; i < ult; i++) {
                if (jogadores[i].pontos < jogadores[i+1].pontos) {
                    aux = jogadores[i];
                    jogadores[i] = jogadores [i+1];
                    jogadores[i+1] = aux;
                }
            }
        }

        // verificar se algum jogador esta fora, se sim remove-lo do jogo
        verificarJogadores(jogadores, qntJogadores);
        
        // display jogadores (printJogadores)
        printJogadores(jogadores, qntJogadores);

        // verificar se todos os jogadores saíram ou se alguém fez 21 -> gameOver
        if (verificarGameOver(jogadores, qntJogadores)) {
            gameOver = !gameOver;
            // displayGanhador();
        }
    }

    // exibir estado final da partida
    
    // registrar partida em arquivo

    // perguntar se quer jogar novamente

    return 0;
}