#pragma once
#include <stdbool.h>

struct Node {
    char shortName[4];
    char fullName[256];
    int balanceFactor;
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

struct PathEntry {
    struct Node* node;
    int dir;
};

typedef struct PathEntry PathEntry;
typedef struct Node Node;
typedef struct AVL AVL;
typedef struct Iterator Iterator;

void avlInsert(AVL* tree, const char sh[], const char fl[]); // inserts new node into tree
AVL* newAVL(void); // creates new empty tree
const char* avlFind(AVL* tree, const char sh[]); // returns full name or NULL if short name is not represented
void avlFree(AVL* tree); // frees all tree memory

void avlDelete(AVL* tree, const char sh[]); // removes node by short name

Iterator* iteratorInit(AVL* tree); // creates in-order iterator
bool iteratorHasNext(Iterator* it);
Node* iteratorNext(Iterator* it); // return NULL if there are no more values
void iteratorFree(Iterator* it);
