#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedList.h"

#define true 1
#define false 0

typedef int bool;

typedef struct {
    char nome[100];
    listaDesCartas cartas;
    bool jogando;
} jogador;

void printJogadores(jogador* listaJogadores, int qntJogadores) {
    for (int j = 0; j < qntJogadores; j++) {
        printf("%s: ", listaJogadores[j].nome);
        printList(&listaJogadores[j].cartas);
        puts("");
    }
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

    // inicializar jogadores
    for (int i = 0; i < qntJogadores; i++) {
        printf("Jogador %d nome: ", i + 1);
        scanf("%s", jogadores[i].nome);
        jogadores[i].jogando = false;
    }
    for (int i = 0; i < qntJogadores; i++) {
        append(&jogadores[i].cartas, rand() % 11 + 1);
        append(&jogadores[i].cartas, rand() % 11 + 1);
    }

    bool gameOver = false;
    while(!gameOver) {

        // oferecer carta para cada jogador

        // ordenar jogadores

        // display jogadores (printJogadores)

        // verificar se algum jogador esta fora, se sim remove-lo do jogo
    }

    // exibir estado final da partida
    
    // registrar partida em arquivo

    // perguntar se quer jogar novamente

    return 0;
}