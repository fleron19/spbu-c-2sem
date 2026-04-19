#pragma once

struct Node {
    char key[256];
    char value[256];
    struct Node* next;
};

typedef struct Node Node;

struct LinkedList {
    Node* head;
    int size;
};

typedef struct LinkedList LinkedList;

LinkedList* newList(void);
void listInsert(LinkedList* list, const char key[], const char val[]);
const char* listFind(LinkedList* list, const char key[]);
void listDelete(LinkedList* list, const char key[]);

void listFree(LinkedList* list);
