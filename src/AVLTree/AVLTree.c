#include "AVLTree.h"
#include "stack.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))

AVL* newAVL(void)
{
    AVL* avl = (AVL*)malloc(sizeof(*avl));
    if (avl == NULL) {
        printf("Allocation error\n");
        return NULL;
    }
    avl->root = NULL;
    avl->size = 0;
    return avl;
}

void avlInsert(AVL* tree, const char sh[], const char fl[])
{
    if (tree->root == NULL) {
        Node* node = (Node*)malloc(sizeof(*node));
        if (node == NULL) {
            printf("Allocation error\n");
            return;
        }
        tree->size++;
        strncpy(node->shortName, sh, 4);
        strncpy(node->fullName, fl, 256);
        node->leftChild = NULL;
        node->rightChild = NULL;
        tree->root = node;
        return;
    }
    Node* curr = tree->root;
    while (true) {
        if (strcmp(sh, curr->shortName) > 0) {
            if (curr->rightChild != NULL) {
                curr = curr->rightChild;
            } else {
                Node* node = (Node*)malloc(sizeof(*node));
                if (node == NULL) {
                    printf("Allocation error\n");
                    return;
                }
                tree->size++;
                strncpy(node->shortName, sh, 4);
                strncpy(node->fullName, fl, 256);
                curr->rightChild = node;
                node->leftChild = NULL;
                node->rightChild = NULL;
                break;
            }
        } else if (strcmp(sh, curr->shortName) < 0) {
            if (curr->leftChild != NULL) {
                curr = curr->leftChild;
            } else {
                Node* node = (Node*)malloc(sizeof(*node));
                if (node == NULL) {
                    printf("Allocation error\n");
                    return;
                }
                tree->size++;
                strncpy(node->shortName, sh, 4);
                strncpy(node->fullName, fl, 256);
                curr->leftChild = node;
                node->leftChild = NULL;
                node->rightChild = NULL;
                break;
            }
        } else {
            break;
        }
    }
}

const char* avlFind(AVL* tree, const char sh[])
{
    if (tree->size == 0) {
        return NULL;
    } else {
        Node* curr = tree->root;
        while (true) {
            // printf("%s\n", curr->shortName);
            if (strcmp(sh, curr->shortName) == 0) {
                return curr->fullName;
            }
            if (strcmp(sh, curr->shortName) > 0) {
                if (curr->rightChild == NULL) {
                    return NULL;
                }
                curr = curr->rightChild;
            } else {
                if (curr->leftChild == NULL) {
                    return NULL;
                }
                curr = curr->leftChild;
            }
        }
    }
}

static void freeNode(Node* node)
{
    if (node == NULL) {
        return;
    }

    freeNode(node->leftChild);
    freeNode(node->rightChild);

    free(node);
}

void avlFree(AVL* tree)
{
    freeNode(tree->root);
    free(tree);
}

void avlDelete(AVL* tree, const char sh[])
{
    if (tree == NULL || tree->root == NULL) {
        return;
    }
    Node* current = tree->root;
    Node* parent = NULL;

    while (current != NULL && strcmp(current->shortName, sh) != 0) {
        parent = current;
        if (strcmp(current->shortName, sh) > 0) {
            current = current->leftChild;
        } else {
            current = current->rightChild;
        }
    }
    if (current == NULL) {
        return;
    }
    if (current->leftChild != NULL && current->rightChild != NULL) {
        Node* successor = current->rightChild;
        Node* successorParent = current;
        while (successor->leftChild != NULL) {
            successorParent = successor;
            successor = successor->leftChild;
        }
        strncpy(current->shortName, successor->shortName, 4);
        strncpy(current->fullName, successor->fullName, 256);
        current = successor;
        parent = successorParent;
    }

    Node* child;
    if (current->leftChild != NULL) {
        child = current->leftChild;
    } else {
        child = current->rightChild;
    }
    if (parent == NULL) {
        tree->root = child;
    } else {
        if (parent->leftChild == current) {
            parent->leftChild = child;
        } else {
            parent->rightChild = child;
        }
    }
    free(current);
    tree->size--;
}

Iterator* iteratorInit(AVL* tree)
{
    Iterator* it = (Iterator*)malloc(sizeof(Iterator));
    int filled = 0;
    it->currIdx = 0;
    it->size = tree->size;
    it->values = (Node**)calloc(it->size, sizeof(Node*));
    if (it->values == NULL) {
        printf("Allocation error\n");
        return it;
    }

    Node* curr = tree->root;
    Stack* stack = newStack();
    while (curr != NULL || !isEmpty(stack)) {
        while (curr != NULL) {
            push(stack, curr);
            curr = curr->leftChild;
        }
        curr = (Node*)pop(stack);
        it->values[filled] = curr;
        filled++;
        curr = curr->rightChild;
    }

    deleteStack(stack);
    return it;
}

bool iteratorHasNext(Iterator* it)
{
    return it->currIdx < it->size;
}

Node* iteratorNext(Iterator* it)
{
    if (!iteratorHasNext(it))
        return NULL;
    Node* res = it->values[it->currIdx];
    it->currIdx++;
    return res;
}

void iteratorFree(Iterator* it)
{
    free(it->values);
    free(it);
}
