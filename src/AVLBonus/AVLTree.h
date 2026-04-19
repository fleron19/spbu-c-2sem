#pragma once
#include <stdbool.h>

struct Node {
    char key[256];
    char value[256];
    int balanceFactor;
    struct Node* leftChild;
    struct Node* rightChild;
};

struct AVL {
    struct Node* root;
    int size;
};

struct PathEntry {
    struct Node* node;
    int dir;
};

typedef struct PathEntry PathEntry;
typedef struct Node Node;
typedef struct AVL AVL;

AVL* newAVL(void); // creates new empty tree
void avlInsert(AVL* tree, const char key[], const char val[]); // inserts new node into tree
const char* avlFind(AVL* tree, const char key[]); // returns value or NULL if key is not represented
void avlDelete(AVL* tree, const char key[]); // removes node by key name

void avlFree(AVL* tree); // frees all tree memory
