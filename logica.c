#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "logica.h"
#include "linkedList.h"

void displayGanhador(jogador* listaJogadores, int qntJogadores) {

    int qntGanhadores = (listaJogadores[0].pontos) > 21 ? 0 : 1;
    int pontuacaoMaxima = listaJogadores[0].pontos;
    int i = 1;
    while (listaJogadores[i].pontos == pontuacaoMaxima && i < qntJogadores) {
        qntGanhadores++;
        i++;
    }

    // imprimir empate
    if (qntGanhadores > 1) {
        printf("##### EMPATE #####\n");
        printf("Ganhadores: \n");
        for (int i = 0; i < qntGanhadores; i++) {
            if (listaJogadores[i].pontos == pontuacaoMaxima) {
                printf("%s\n", listaJogadores[i].nome);
            }
        }
    } else if (qntGanhadores == 0) { 
        // todos perderam
        printf("##### NAO HOUVE VENCEDORES #####\n");
    } else { 
        // imprimir vencedor
        printf("##### VITORIA DE %s #####\n", listaJogadores[0].nome);
        printf("Pontos: %d\n", listaJogadores[0].pontos);
    }
    
}

void verificarJogadores(jogador* listaJogadores, int qntJogadores) {
    // verifica se algum jogador fez mais de 21 pontos e altera seu estado de jogo para false

    for (int i = 0; i < qntJogadores; i++) {
        if (listaJogadores[i].pontos > 21) {
            listaJogadores[i].jogando = false;
        }
    }
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

void ordenaJogadores(jogador* listaJogadores, int qntJogadores) {
    // ordena todos os jogadores utilizando o bubble sort
    // Os jogadores com mais de 21 pontos são jogados para o final do array
    // para que sejam mostrados por ultimo no terminal

    
    jogador aux;
    for(int ult = qntJogadores - 1; ult > 0; ult--) {
        for (int i=0; i < ult; i++) {
            if (listaJogadores[i].pontos < listaJogadores[i+1].pontos) {
                aux = listaJogadores[i];
                listaJogadores[i] = listaJogadores[i+1];
                listaJogadores[i+1] = aux;
            }
        }
    }

    int j=0, cont=0;
	jogador v2[qntJogadores];
    jogador v3[qntJogadores];

    for (int i=0; i<qntJogadores; i++){
		if (listaJogadores[i].pontos > 21){
			v2[cont]=listaJogadores[i];
			cont++;
		}
		else {
			v3[j]=listaJogadores[i];
			j++;
		}
	}

    for (int i=0; i<cont; i++){
		v3[j]=v2[i];
		j++;
	}

    for (int i = 0; i < qntJogadores; i++) {
        listaJogadores[i] = v3[i];
    }
}

void pedeCarta(jogador* listaJogadores, int qntJogadores, pilhaDeCarta* baralho) {
    for (int i = 0; i < qntJogadores; i++) {
            if (listaJogadores[i].jogando) {
                char querNovaCarta;
                getchar();
                printf("%s quer mais uma carta? [s/n]: ", listaJogadores[i].nome);
                scanf("%c", &querNovaCarta);
                // checar input
                while (querNovaCarta != 's' && querNovaCarta != 'S' && querNovaCarta != 'n' && querNovaCarta != 'N') {
                    printf("Responda [s/n]: ");
                    scanf("%c", &querNovaCarta);
                }
                if (querNovaCarta == 's' || querNovaCarta == 'S') {
                    append(listaJogadores[i].cartas, removeCarta(baralho));
                    atualizarPontuacao(&listaJogadores[i]);
                } else {
                    listaJogadores[i].jogando = false;
                }
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

void jogarPartida() {

    // Gerador de numero aleatório
    time_t t1;
    srand ((unsigned) time (&t1));

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
        return;
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
    ordenaJogadores(jogadores, qntJogadores);
    system("clear");
    printJogadores(jogadores, qntJogadores);
    while(!gameOver) {

        // oferecer carta para cada jogador
        pedeCarta(jogadores, qntJogadores, baralho);

        // ordenar jogadores
        ordenaJogadores(jogadores, qntJogadores);

        // verificar se algum jogador esta fora, se sim remove-lo do jogo
        verificarJogadores(jogadores, qntJogadores);
        
        // display jogadores (printJogadores)
        system("clear");
        printJogadores(jogadores, qntJogadores);

        // verificar se todos os jogadores saíram ou se alguém fez 21 -> gameOver
        if (verificarGameOver(jogadores, qntJogadores)) {
            gameOver = !gameOver;
            displayGanhador(jogadores, qntJogadores);
        }

    }
}