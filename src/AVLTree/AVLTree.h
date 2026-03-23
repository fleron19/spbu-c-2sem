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

typedef struct Node Node;
typedef struct AVL AVL;

void avlInsert(AVL* tree, const char sh[], const char fl[]);
AVL* newAVL(void);
const char* avlFind(AVL* tree, const char sh[]);
// static void freeNode(Node* node);
void avlFree(AVL* tree);

void avlDelete(AVL* tree, const char sh[]);
