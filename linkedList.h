typedef struct aux {
    int val;
    struct aux* next;
} node;

typedef struct {
    node* head;
    node* tail;
} listaDesCartas;

void append(listaDesCartas* li, int elem);

void initList(listaDesCartas* li);

void printList(listaDesCartas* li);

int listLength(listaDesCartas* li);