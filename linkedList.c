#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

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