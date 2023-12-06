typedef struct aux {
    char val;
    struct aux* next;
} node;

typedef struct {
    node* head;
    node* tail;
} pilhaDeCarta;

void append(pilhaDeCarta* li, char elem);

void initList(pilhaDeCarta* li);

void printList(pilhaDeCarta* li);

int listLength(pilhaDeCarta* li);

char removeCarta(pilhaDeCarta* li);