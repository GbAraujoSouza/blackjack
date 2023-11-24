#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

int listLength(listaDesCartas* li) {
    node* p = li->head;
    int size = 0;
    while (p != NULL) {
        p = p->next;
        size++;
    }
    return size;
}

void initList(listaDesCartas* li) {
    li->head = NULL;
    li->tail = NULL;
}

void append(listaDesCartas* li, int elem) {
    node* new = (node*)malloc(sizeof(node));
    new->val = elem;
    new->next = NULL;
    if (listLength(li) == 0) {
        li->head = new;
        li->tail = li->head;
    } else {
        li->tail->next = new;
    }
}

void printList(listaDesCartas* li) {
    node* p = li->head;
    while (p != NULL) {
        printf("%3d |", p->val);
        p = p->next;
    }
}