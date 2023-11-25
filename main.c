#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linkedList.h"

typedef struct {
    char nome[100];
    listaDesCartas cartas;
} jogador;

int cartaAleatoria() {
    // Gera um numero aleatório a partir de um vetor de cartas 
    // O elemento 'D' representa o numero 10
    int cartas[] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'D', 'J', 'Q', 'K' };

    int randomIndex = rand() % 13;
    int randomCard = cartas[randomIndex];

    // os números retornados sao contados a partir da tabela ascii
    switch (randomCard)
    {
    case 74:  //J
    case 75:  //K
    case 81:  //Q
    case 68:  //D
        return 10;
        break;

    case 65:  //A
        return 11;
        break;
    
    default:  //2-9
        return randomCard - 48;
        break;
    }
}

int main() {

    // Gerador de numero aleatório
    time_t t1;
    srand ((unsigned) time (&t1));

    int qntJogadores;
    printf("Numero de Jogadores ");
    scanf("%d", &qntJogadores);

    jogador* jogadores = (jogador*)malloc(qntJogadores * sizeof(jogador));
    if (!jogadores) {
        puts("Erro de alocação de memoria");
        return -1;
    }

    for (int i = 0; i < qntJogadores; i++) {
        append(&jogadores[i].cartas, cartaAleatoria());
        append(&jogadores[i].cartas, cartaAleatoria());
    }

    for (int i = 0, j = 1; i < qntJogadores; i++, j++) {
        printf("Jogador %d: ", j);
        printList(&jogadores[i].cartas);
        puts("");
    }



    return 0;
}