#include "AVLTests.h"
#include "AVLTree.h"
#include <stdio.h>
#include <string.h>

#define GREEN(string) "\x1b[32m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"

bool testInsert1(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "BBB123", "BBB full val");
    avlInsert(avl, "AAA123", "AAA full val");
    avlInsert(avl, "CCC123", "CCC full val");
    if (strcmp(avl->root->key, "BBB123") != 0) {
        avlFree(avl);
        return false;
    }
    if (strcmp(avl->root->leftChild->key, "AAA123") != 0) {
        avlFree(avl);
        return false;
    }
    if (strcmp(avl->root->rightChild->key, "CCC123") != 0) {
        avlFree(avl);
        return false;
    }
    avlFree(avl);
    return true;
}

bool testFind1(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "5", "five");
    avlInsert(avl, "1", "one");
    avlInsert(avl, "66", "six");
    avlInsert(avl, "888", "eight");
    const char* res = avlFind(avl, "888");
    bool pass = (res != NULL) && (strcmp(res, "eight") == 0);
    avlFree(avl);
    return pass;
}

bool testFind2(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "5", "five");
    avlInsert(avl, "1", "one");
    avlInsert(avl, "66", "six");
    avlInsert(avl, "888", "eight");
    const char* res = avlFind(avl, "12");
    bool pass = (res == NULL);
    avlFree(avl);
    return pass;
}

bool testDelete1(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "10", "ten");
    avlInsert(avl, "5", "five");
    avlInsert(avl, "155", "fifteen");
    avlDelete(avl, "155");
    bool pass = (avl->size == 2) && (avlFind(avl, "155") == NULL) && (avl->root->rightChild == NULL);
    avlFree(avl);
    return pass;
}

bool testDelete2(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "10", "ten");
    avlInsert(avl, "5", "five");
    avlInsert(avl, "33", "three");
    avlDelete(avl, "5");
    bool pass = (avl->size == 2) && (avlFind(avl, "5") == NULL) && (avl->root->rightChild == NULL);
    avlFree(avl);
    return pass;
}

bool testDelete3(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "10", "ten");
    avlInsert(avl, "5", "five");
    avlInsert(avl, "33", "three");
    avlInsert(avl, "777", "seven");
    avlDelete(avl, "5");
    bool pass = (avl->size == 3) && (avlFind(avl, "5") == NULL)
        && (avlFind(avl, "10") != NULL)
        && (avlFind(avl, "33") != NULL)
        && (avlFind(avl, "777") != NULL);
    avlFree(avl);
    return pass;
}

bool testDeleteRoot(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "10", "ten");
    avlInsert(avl, "5", "five");
    avlDelete(avl, "10");
    bool pass = (avl->size == 1) && (strcmp(avl->root->key, "5") == 0);
    avlFree(avl);
    return pass;
}

bool testDeleteNonExistent(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "10", "ten");
    avlInsert(avl, "5", "five");
    avlDelete(avl, "42");
    bool pass = (avl->size == 2) && (avlFind(avl, "10") != NULL) && (avlFind(avl, "5") != NULL);
    avlFree(avl);
    return pass;
}

int test(void)
{
    bool (*tests[])(void) = {
        testInsert1, testFind1, testDelete1,
        testDelete2, testDelete3,
        testDeleteRoot, testDeleteNonExistent
    };
    const int TEST_NUM = 7;
    bool good = true;

    for (int i = 0; i < TEST_NUM; ++i) {
        if (tests[i]()) {
            printf(GREEN("Test %d passed!\n"), i + 1);
        } else {
            printf(RED("Test %d failed!\n"), i + 1);
            good = false;
        }
    }

    return good ? 0 : 1;
}
