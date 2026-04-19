#include "AVLTree.h"
#include "stack.h"
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define USE_ROTATIONS true // initilization with rotations is 15 times faster than without!!!

static Node* rotateRight(Node* n)
{
    Node* c = n->leftChild;
    Node* gc = c->rightChild;

    c->rightChild = n;
    n->leftChild = gc;

    if (c->balanceFactor == 1) {
        n->balanceFactor = 0;
        c->balanceFactor = 0;
    } else {
        n->balanceFactor = 1;
        c->balanceFactor = -1;
    }

    return c;
}

static Node* rotateLeft(Node* n)
{
    Node* c = n->rightChild;
    Node* gc = c->leftChild;

    c->leftChild = n;
    n->rightChild = gc;

    if (c->balanceFactor == -1) {
        n->balanceFactor = 0;
        c->balanceFactor = 0;
    } else {
        n->balanceFactor = -1;
        c->balanceFactor = 1;
    }

    return c;
}

static Node* rotateLeftRight(Node* n)
{
    Node* c = n->leftChild;
    Node* gc = c->rightChild;

    if (gc->balanceFactor == 1) {
        n->balanceFactor = -1;
        c->balanceFactor = 0;
    } else if (gc->balanceFactor == -1) {
        n->balanceFactor = 0;
        c->balanceFactor = 1;
    } else {
        n->balanceFactor = 0;
        c->balanceFactor = 0;
    }
    gc->balanceFactor = 0;

    c->rightChild = gc->leftChild;
    gc->leftChild = c;
    n->leftChild = gc->rightChild;
    gc->rightChild = n;

    return gc;
}

static Node* rotateRightLeft(Node* n)
{
    Node* c = n->rightChild;
    Node* gc = c->leftChild;

    if (gc->balanceFactor == 1) {
        n->balanceFactor = 0;
        c->balanceFactor = -1;
    } else if (gc->balanceFactor == -1) {
        n->balanceFactor = 1;
        c->balanceFactor = 0;
    } else {
        n->balanceFactor = 0;
        c->balanceFactor = 0;
    }
    gc->balanceFactor = 0;

    c->leftChild = gc->rightChild;
    gc->rightChild = c;
    n->rightChild = gc->leftChild;
    gc->leftChild = n;

    return gc;
}

static Node* rebalance(Node* n)
{
    if (USE_ROTATIONS) {
        if (n->balanceFactor == 2) {
            if (n->leftChild->balanceFactor == -1) {
                return rotateLeftRight(n);
            } else {
                return rotateRight(n);
            }
        } else {
            if (n->rightChild->balanceFactor == 1) {
                return rotateRightLeft(n);
            } else {
                return rotateLeft(n);
            }
        }
    }
    return n;
}

static Node* createNode(const char key[], const char val[])
{
    Node* newNode = (Node*)malloc(sizeof(*newNode));
    if (newNode == NULL) {
        printf("Allocation error\n");
        return NULL;
    }
    strncpy(newNode->key, key, 255);
    newNode->key[255] = '\0';
    strncpy(newNode->value, val, 255);
    newNode->value[255] = '\0';
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->balanceFactor = 0;
    return newNode;
}

static void updateAncestorsAndRebalance(AVL* tree, PathEntry path[], int pathTop)
{
    for (int i = pathTop - 1; i >= 0; i--) {
        Node* parent = path[i].node;
        if (path[i].dir == -1) {
            parent->balanceFactor++;
        } else {
            parent->balanceFactor--;
        }

        if (parent->balanceFactor == 0) {
            break;
        }

        if (parent->balanceFactor == 2 || parent->balanceFactor == -2) {
            Node* newRoot = rebalance(parent);
            if (i == 0) {
                tree->root = newRoot;
            } else {
                Node* grandparent = path[i - 1].node;
                if (grandparent->leftChild == parent) {
                    grandparent->leftChild = newRoot;
                } else {
                    grandparent->rightChild = newRoot;
                }
            }
            break;
        }
    }
}

static bool findAndInsert(AVL* tree, const char key[], const char val[], Node* newNode, PathEntry path[], int* pathTop)
{
    Node* curr = tree->root;
    while (true) {
        int cmp = strcmp(key, curr->key);
        if (cmp == 0) {
            strncpy(curr->value, val, 255);
            curr->value[255] = '\0';
            free(newNode);
            tree->size--;
            return false;
        }

        if (cmp > 0) {
            path[*pathTop].node = curr;
            path[*pathTop].dir = 1;
            (*pathTop)++;
            if (curr->rightChild == NULL) {
                curr->rightChild = newNode;
                return true;
            }
            curr = curr->rightChild;
        } else {
            path[*pathTop].node = curr;
            path[*pathTop].dir = -1;
            (*pathTop)++;
            if (curr->leftChild == NULL) {
                curr->leftChild = newNode;
                return true;
            }
            curr = curr->leftChild;
        }
    }
}

void avlInsert(AVL* tree, const char key[], const char val[])
{
    Node* newNode = createNode(key, val);
    if (newNode == NULL) {
        return;
    }
    tree->size++;

    if (tree->root == NULL) {
        tree->root = newNode;
        return;
    }

    const int MAX_HEIGHT = (int)(1.44 * log2(tree->size + 2) - 0.328) + 5;
    PathEntry path[MAX_HEIGHT];
    int pathTop = 0;

    if (!findAndInsert(tree, key, val, newNode, path, &pathTop)) {
        return;
    }

    updateAncestorsAndRebalance(tree, path, pathTop);
}

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

const char* avlFind(AVL* tree, const char key[])
{
    if (tree->size == 0 || tree->root == NULL) {
        return NULL;
    }
    Node* curr = tree->root;
    while (curr != NULL) {
        if (strcmp(key, curr->key) == 0) {
            return curr->value;
        }
        if (strcmp(key, curr->key) > 0) {
            curr = curr->rightChild;
        } else {
            curr = curr->leftChild;
        }
    }
    return NULL;
}

static void freeNode(Node* node)
{
    if (node == NULL)
        return;
    freeNode(node->leftChild);
    freeNode(node->rightChild);
    free(node);
}

void avlFree(AVL* tree)
{
    if (tree == NULL)
        return;
    freeNode(tree->root);
    free(tree);
}

static Node* findMin(Node* root)
{
    while (root && root->leftChild)
        root = root->leftChild;
    return root;
}

static Node* deleteLeaf(Node* root, bool* outShrunk, bool* outDeleted)
{
    free(root);
    *outShrunk = true;
    *outDeleted = true;
    return NULL;
}

static Node* removeRecursive(Node* root, const char key[], bool* outShrunk, bool* outDeleted);

static Node* deleteNodeWithTwoChildren(Node* root, bool* outShrunk, bool* outDeleted)
{
    Node* succ = findMin(root->rightChild);

    strncpy(root->key, succ->key, 255);
    root->key[255] = '\0';
    strncpy(root->value, succ->value, 255);
    root->value[255] = '\0';

    bool childShrunk = false, childDeleted = false;
    root->rightChild = removeRecursive(root->rightChild, succ->key, &childShrunk, &childDeleted);
    if (childDeleted && outDeleted)
        *outDeleted = true;
    if (!childShrunk) {
        *outShrunk = false;
        return root;
    }
    root->balanceFactor += 1;
    return root;
}

static Node* deleteNodeWithOneChild(Node* root, bool* outShrunk, bool* outDeleted)
{
    Node* child = root->leftChild ? root->leftChild : root->rightChild;
    Node* tmp = root;
    root = child;
    free(tmp);
    *outShrunk = true;
    *outDeleted = true;
    return root;
}

static Node* handlePostDeletionBalance(Node* root, bool* outShrunk)
{
    if (root->balanceFactor == 1 || root->balanceFactor == -1) {
        *outShrunk = false;
        return root;
    }
    if (root->balanceFactor == 0) {
        *outShrunk = true;
        return root;
    }
    if (root->balanceFactor == 2 || root->balanceFactor == -2) {
        root = rebalance(root);
        *outShrunk = (root->balanceFactor == 0);
        return root;
    }
    *outShrunk = false;
    return root;
}

static Node* removeRecursive(Node* root, const char key[], bool* outShrunk, bool* outDeleted)
{
    if (!root) {
        if (outShrunk)
            *outShrunk = false;
        if (outDeleted)
            *outDeleted = false;
        return NULL;
    }

    if (outDeleted)
        *outDeleted = false;

    int cmp = strcmp(key, root->key);
    if (cmp < 0) {
        bool childShrunk = false, childDeleted = false;
        root->leftChild = removeRecursive(root->leftChild, key, &childShrunk, &childDeleted);
        if (childDeleted && outDeleted)
            *outDeleted = true;
        if (!childShrunk) {
            if (outShrunk)
                *outShrunk = false;
            return root;
        }
        root->balanceFactor -= 1;
    } else if (cmp > 0) {
        bool childShrunk = false, childDeleted = false;
        root->rightChild = removeRecursive(root->rightChild, key, &childShrunk, &childDeleted);
        if (childDeleted && outDeleted)
            *outDeleted = true;
        if (!childShrunk) {
            if (outShrunk)
                *outShrunk = false;
            return root;
        }
        root->balanceFactor += 1;
    } else {
        if (!root->leftChild && !root->rightChild) {
            return deleteLeaf(root, outShrunk, outDeleted);
        } else if (root->leftChild && root->rightChild) {
            return deleteNodeWithTwoChildren(root, outShrunk, outDeleted);
        } else {
            return deleteNodeWithOneChild(root, outShrunk, outDeleted);
        }
    }

    return handlePostDeletionBalance(root, outShrunk);
}

void avlDelete(AVL* tree, const char key[])
{
    if (tree == NULL || tree->root == NULL)
        return;
    bool shrunk = false, deleted = false;
    tree->root = removeRecursive(tree->root, key, &shrunk, &deleted);
    if (deleted && tree->size > 0)
        tree->size--;
}
