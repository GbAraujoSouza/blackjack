#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define true 1
#define false 0

typedef struct aux {
    char val;
    struct aux* next;
} node;

typedef struct {
    node* head;
    node* tail;
} pilhaDeCarta;

typedef int bool;

typedef struct {
    char nome[100];
    pilhaDeCarta* cartas;
    int pontos;
    bool jogando;
} jogador;

typedef struct{
    char nome[20];
    int pontuacao;
    int hr;
    int min;
    int seg;
    int dia;
    int mes;
    int ano;
} jReg;

int listLength(pilhaDeCarta* li) {
    node* p = li->head;
    int size = 0;
    while (p != NULL) {
        p = p->next;
        size++;
    }
    return size;
}

void initList(pilhaDeCarta* li) {
    li->head = NULL;
    li->tail = NULL;
}

void append(pilhaDeCarta* li, char elem) {
    node* new = (node*)malloc(sizeof(node));
    new->val = elem;
    new->next = NULL;
    if (listLength(li) == 0) {
        li->head = new;
        li->tail = li->head;
    } else {
        li->tail->next = new;
        li->tail = new;
    }
}

char removeCarta(pilhaDeCarta* li) {
    // remover e retornar o ultimo elemento
    node* p = li->head;
    // chegar no penultimo elemento
    while (p->next != li->tail) {
        p = p->next;
    }
    li->tail = p;
    p = p->next;
    li->tail->next = NULL;
    return p->val;
}

void printList(pilhaDeCarta* li) {
    node* p = li->head;
    while (p != NULL) {
        printf("%3c |", p->val);
        p = p->next;
    }
}





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

void gravarNoArquivo(jogador j){
    struct tm* reg_data_hora;
    time_t segundos;
    time(&segundos);
    reg_data_hora = localtime(&segundos);
    FILE* f = fopen("log.txt", "a");
    if(!f){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    fprintf(f, "%s\n", j.nome);
    fprintf(f, "%d ", j.pontos);
    fprintf(f, "%d %d %d ", reg_data_hora -> tm_mday, reg_data_hora -> tm_mon + 1, reg_data_hora -> tm_year - 100);
    fprintf(f, "%d %d %d\n", reg_data_hora -> tm_hour - 3, reg_data_hora -> tm_min, reg_data_hora -> tm_sec);
    fclose(f);
}

void jogarPartida() {

    // Gerador de numero aleatório
    time_t t1;
    srand ((unsigned) time (&t1));

    // criar jogadores
    int qntJogadores;
    printf("Numero de Jogadores ");
    scanf("%d", &qntJogadores);
    while (qntJogadores < 2 || qntJogadores > 8) {
        system("clear");
        puts("Minimo de 2 e maximo de 8 jogadores!");
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
    // registrar vencedor
    int maxPontos = jogadores[0].pontos;
    for (int i = 0; i < qntJogadores; i++) {
        if (jogadores[i].pontos == maxPontos) {
            gravarNoArquivo(jogadores[i]);
        }
    }
}

void pegarUltimoRegistro(){
    jReg jr;
    FILE* f = fopen("log.txt", "r");
    if(!f){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    while(!feof(f)){
        fscanf(f, "%[^\n]", jr.nome);
        fscanf(f, "%d %d %d %d %d %d %d", &jr.pontuacao, &jr.hr, &jr.min, &jr.seg, &jr.dia, &jr.mes, &jr.ano);
    }
    printf("Nome - %s Pontuação - %d Data - %2d/%2d/%2d Hora - %2d:%2d:%2d\n", jr.nome, jr.pontuacao, jr.hr, jr.min, jr.seg, jr.dia, jr.mes, jr.ano);
}

void pegarMaiorPontuacao(){
    jReg maiorReg, auxReg;
    FILE* f = fopen("log.txt", "r");
    if(!f){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }
    fscanf(f, "%s", maiorReg.nome);
    fscanf(f, "%d %d %d %d %d %d %d", &maiorReg.pontuacao, &maiorReg.hr, &maiorReg.min, &maiorReg.seg, &maiorReg.dia, &maiorReg.mes, &maiorReg.ano);
    while(!feof(f)){
        fscanf(f, "%s", auxReg.nome);
        fscanf(f, "%d %d %d %d %d %d %d", &auxReg.pontuacao, &auxReg.hr, &auxReg.min, &auxReg.seg, &auxReg.dia, &auxReg.mes, &auxReg.ano);
        if(auxReg.pontuacao > maiorReg.pontuacao){
            strcpy(maiorReg.nome, auxReg.nome);
            maiorReg.pontuacao = auxReg.pontuacao;
            maiorReg.hr = auxReg.hr;
            maiorReg.min = auxReg.min;
            maiorReg.seg = auxReg.seg;
            maiorReg.dia = auxReg.dia;
            maiorReg.mes = auxReg.mes;
            maiorReg.ano = auxReg.ano;
        }
    }
    printf("Nome - %s Pontuação - %d Data - %2d/%2d/%2d Hora - %2d:%2d:%2d\n", maiorReg.nome, maiorReg.pontuacao, maiorReg.hr, maiorReg.min, maiorReg.seg, maiorReg.dia, maiorReg.mes, maiorReg.ano);
}

void limparRegistros(){
    FILE* f = fopen("log.txt", "w");
    fclose(f);
}

bool retornarAoLobby();

int main(){
    int opcao = 0;

    while (opcao != 3) {

        do{
            system("clear");
            printf("Olá, seja bem-vindo ao lobby de BlackJack"
                "\n1. Iniciar uma nova partida"
                "\n2. Acessas os registros de partidas anteriores."
                "\n3. Sair do lobby."
                "\nDigite uma das opcoes anteriores para continuar: ");
            scanf("%d", &opcao);
            getchar();
        }while(opcao !=1 && opcao != 2 && opcao != 3);
        
        switch(opcao){
        case 1:
            system("clear");
            jogarPartida();
            if (retornarAoLobby()) {
                continue;
            }
            opcao = 3;
            break;
        case 2:
           do{
                system("clear");
                printf("O que voce deseja acessar?"
                    "\n1. Acessar a ultima pontuação."
                    "\n2. Acessar a maior pontuação."
                    "\n3. Limpar os registros."
                    "\nDigite uma das opcoes anteriores para continuar: ");
                scanf("%d", &opcao);
                getchar();
            } while(opcao !=1 && opcao != 2 && opcao != 3);
            switch(opcao){
                case 1:
                    pegarUltimoRegistro();
                    break;
                case 2:
                    pegarMaiorPontuacao();
                    break;
                case 3:
                    limparRegistros();
                    break;
            }
            if (retornarAoLobby()) {
                continue;
            }
            opcao = 3;
        }

    }
    

    // switch(opcao){
    //     case 1:
    //         jogarPartida();
    //         retornarAoLobby();
    //         break;
    //     case 2:
    //         printf("O quê você deseja acessar?\n");
    //         printf("1. Acessar a última pontuação\n2. Acessar a maior pontuação\n3. Limpar os registros\n");
    //         scanf("%d", &opcao);
    //         getchar();
    //         switch(opcao){
    //             case 1:
    //                 pegarUltimoRegistro();
    //                 break;
    //             case 2:
    //                 pegarMaiorPontuacao();
    //                 break;
    //             case 3:
    //                 limparRegistros();
    //                 break;
    //         }
    //         retornarAoLobby();
    //         break;
    //     case 3:
    //         break;
    //     default:
    //         printf("Digite uma opcao válida (main)\n");
    //         main();
    // }
    system("clear");
    printf("Você deixou o lobby\n");
    return 0;
}

bool retornarAoLobby(){
    char c;
    getchar();
    printf("Deseja voltar ao Lobby(s/n): ");
    scanf("%c", &c);
    getchar();

    while (tolower(c) != 's' && tolower(c) != 'n')
    {
        printf("Digite uma opção válida: ");
        scanf("%c", &c);
    }
    
    if (tolower(c) == 's')
        return true;
    return false;
}
