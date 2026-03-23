#pragma once
#include <stdbool.h>


struct Node {
    char shortName[4];
    char fullName[256];
    struct Node* leftChild;
    struct Node* rightChild;
};

struct AVL {
    struct Node* root;
    int size;
};

struct Iterator {
    struct Node** values;
    int size;
    int currIdx;
};


typedef struct Node Node;
typedef struct AVL AVL;
typedef struct Iterator Iterator;

void avlInsert(AVL* tree, const char sh[], const char fl[]);
AVL* newAVL(void);
const char* avlFind(AVL* tree, const char sh[]);
// static void freeNode(Node* node);
void avlFree(AVL* tree);

void avlDelete(AVL* tree, const char sh[]);

Iterator* iteratorInit(AVL* tree);
bool iteratorHasNext(Iterator* it);
Node* iteratorNext(Iterator* it); // return -1 if there are no more values
void iteratorFree(Iterator* it);
