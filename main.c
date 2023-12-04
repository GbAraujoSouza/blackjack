#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedList.h"

typedef struct {
    char nome[100];
    listaDesCartas cartas;
} jogador;

int main() {

    // Gerador de numero aleatório
    time_t t1;
    srand ( (unsigned) time (&t1));

    int qntJogadores;
    printf("Numero de Jogadores ");
    scanf("%d", &qntJogadores);

    jogador* jogadores = (jogador*)malloc(qntJogadores * sizeof(jogador));
    if (!jogadores) {
        puts("Erro de alocação de memoria");
        return -1;
    }

    for (int i = 0; i < qntJogadores; i++) {
        append(&jogadores[i].cartas, rand() % 11 + 1);
        append(&jogadores[i].cartas, rand() % 11 + 1);
    }

    for (int i = 0, j = 1; i < qntJogadores; i++, j++) {
        printf("Jogador %d: ", j);
        printList(&jogadores[i].cartas);
        puts("");
    }



    return 0;
}