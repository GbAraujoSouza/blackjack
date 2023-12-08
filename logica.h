#define true 1
#define false 0

typedef int bool;

typedef struct {
    char nome[100];
    pilhaDeCarta* cartas;
    int pontos;
    bool jogando;
} jogador;

void displayGanhador(jogador* listaJogadores, int qntJogadores);

void verificarJogadores(jogador* listaJogadores, int qntJogadores);

int valorCarta(char carta);

void atualizarPontuacao(jogador* j);

void printJogadores(jogador* listaJogadores, int qntJogadores);

void ordenaJogadores(jogador* listaJogadores, int qntJogadores);

void pedeCarta(jogador* listaJogadores, int qntJogadores, pilhaDeCarta* baralho);

bool verificarGameOver(jogador* listaJogadores, int qntJogadores);

pilhaDeCarta* constroiBaralho();

void jogarPartida();