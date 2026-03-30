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
        node->balanceFactor = 0;
        return;
    }
    Node* curr = tree->root;
    Node* path[65536] = { NULL };
    int cnum = 0;
    while (true) {
        if (strcmp(sh, curr->shortName) > 0) {
            if (curr->rightChild != NULL) {
                path[cnum] = curr;
                cnum++;
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
                for (int i = cnum - 1; i >= 0; i--) {
                    if (curr->rightChild == node) {
                        curr->balanceFactor--;
                    } else if (curr->leftChild == node) {
                        curr->balanceFactor++;
                    }
                    if (curr->balanceFactor == 0) {
                        break;
                    } else if (curr->balanceFactor == 2) {
                        // rotate();
                        if (curr->balanceFactor == 0) {
                            break;
                        }
                    }
                    node = curr;
                    curr = path[i];
                }
                break;
            }
        } else if (strcmp(sh, curr->shortName) < 0) {
            if (curr->leftChild != NULL) {
                path[cnum] = curr;
                cnum++;
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
                for (int i = cnum - 1; i >= 0; i--) {
                    if (curr->rightChild == node) {
                        curr->balanceFactor--;
                    } else if (curr->leftChild == node) {
                        curr->balanceFactor++;
                    }
                    if (curr->balanceFactor == 0) {
                        break;
                    } else if (curr->balanceFactor == 2) {
                        // rotate();
                        if (curr->balanceFactor == 0) {
                            break;
                        }
                    }
                    node = curr;
                    curr = path[i];
                }
                break;
            }
        } else {
            strncpy(curr->fullName, fl, 256);
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

static Node* findMin(Node* root)
{
    while (root && root->leftChild)
        root = root->leftChild;
    return root;
}

static Node* removeRecursive(Node* root, const char sh[], bool* outShrunk, bool* outDeleted)
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

    int cmp = strcmp(sh, root->shortName);
    if (cmp < 0) {
        bool childShrunk = false, childDeleted = false;
        root->leftChild = removeRecursive(root->leftChild, sh, &childShrunk, &childDeleted);
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
        root->rightChild = removeRecursive(root->rightChild, sh, &childShrunk, &childDeleted);
        if (childDeleted && outDeleted)
            *outDeleted = true;
        if (!childShrunk) {
            if (outShrunk)
                *outShrunk = false;
            return root;
        }
        root->balanceFactor += 1;
    } else {
        // найден узел для удаления
        if (!root->leftChild && !root->rightChild) {
            free(root);
            if (outShrunk)
                *outShrunk = true;
            if (outDeleted)
                *outDeleted = true;
            return NULL;
        } else if (root->leftChild && root->rightChild) {
            Node* succ = findMin(root->rightChild);
            // безопасное копирование shortName/fullName
            memcpy(root->shortName, succ->shortName, sizeof(root->shortName));
            root->shortName[sizeof(root->shortName) - 1] = '\0';
            strncpy(root->fullName, succ->fullName, sizeof(root->fullName) - 1);
            root->fullName[sizeof(root->fullName) - 1] = '\0';

            bool childShrunk = false, childDeleted = false;
            root->rightChild = removeRecursive(root->rightChild, succ->shortName, &childShrunk, &childDeleted);
            if (childDeleted && outDeleted)
                *outDeleted = true;
            if (!childShrunk) {
                if (outShrunk)
                    *outShrunk = false;
                return root;
            }
            root->balanceFactor += 1;
        } else {
            Node* child = root->leftChild ? root->leftChild : root->rightChild;
            Node* tmp = root;
            root = child;
            free(tmp);
            if (outShrunk)
                *outShrunk = true;
            if (outDeleted)
                *outDeleted = true;
            return root;
        }
    }

    if (root->balanceFactor == 1 || root->balanceFactor == -1) {
        if (outShrunk)
            *outShrunk = false;
        return root;
    } else if (root->balanceFactor == 0) {
        if (outShrunk)
            *outShrunk = true;
        return root;
    } else if (root->balanceFactor == 2 || root->balanceFactor == -2) {
        // rotate not implemented per request
        // root = rotate(root);
        if (root->balanceFactor == 0) {
            if (outShrunk)
                *outShrunk = true;
        } else {
            if (outShrunk)
                *outShrunk = false;
        }
        return root;
    }

    if (outShrunk)
        *outShrunk = false;
    return root;
}

void avlDelete(AVL* tree, const char sh[])
{
    if (tree == NULL || tree->root == NULL)
        return;
    bool shrunk = false, deleted = false;
    tree->root = removeRecursive(tree->root, sh, &shrunk, &deleted);
    if (deleted && tree->size > 0)
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
