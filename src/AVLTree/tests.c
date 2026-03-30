#include "tests.h"
#include "AVLTree.h"
#include <stdio.h>
#include <string.h>

#define GREEN(string) "\x1b[32m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"

bool testInsert1(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "BBB", "BBB full");
    avlInsert(avl, "AAA", "AAA full");
    avlInsert(avl, "CCC", "CCC full");
    if (strcmp(avl->root->shortName, "BBB") != 0) {
        avlFree(avl);
        return false;
    }
    if (strcmp(avl->root->leftChild->shortName, "AAA") != 0) {
        avlFree(avl);
        return false;
    }
    if (strcmp(avl->root->rightChild->shortName, "CCC") != 0) {
        avlFree(avl);
        return false;
    }
    avlFree(avl);
    return true;
}

bool testInsert2(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "001", "one");
    avlInsert(avl, "003", "three");
    avlInsert(avl, "003", "three updated");
    avlInsert(avl, "007", "seven");
    if (avl->size != 3) {
        avlFree(avl);
        return false;
    }
    Iterator* it = iteratorInit(avl);
    Node* n1 = iteratorNext(it);
    Node* n2 = iteratorNext(it);
    Node* n3 = iteratorNext(it);
    bool pass = (n1 != NULL) && (n2 != NULL) && (n3 != NULL)
        && (strcmp(n1->shortName, "001") == 0)
        && (strcmp(n2->shortName, "003") == 0)
        && (strcmp(n3->shortName, "007") == 0);
    avlFree(avl);
    iteratorFree(it);
    return pass;
}

bool testFind1(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "005", "five");
    avlInsert(avl, "001", "one");
    avlInsert(avl, "006", "six");
    avlInsert(avl, "008", "eight");
    const char* res = avlFind(avl, "008");
    bool pass = (res != NULL) && (strcmp(res, "eight") == 0);
    avlFree(avl);
    return pass;
}

bool testFind2(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "005", "five");
    avlInsert(avl, "001", "one");
    avlInsert(avl, "006", "six");
    avlInsert(avl, "008", "eight");
    const char* res = avlFind(avl, "012");
    bool pass = (res == NULL);
    avlFree(avl);
    return pass;
}

bool testIterator1(void)
{
    AVL* avl = newAVL();
    Iterator* it = iteratorInit(avl);
    bool res = !iteratorHasNext(it);
    avlFree(avl);
    iteratorFree(it);
    return res;
}

bool testIterator2(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "003", "three");
    avlInsert(avl, "001", "one");
    avlInsert(avl, "005", "five");
    Iterator* it = iteratorInit(avl);
    Node* n1 = iteratorNext(it);
    Node* n2 = iteratorNext(it);
    Node* n3 = iteratorNext(it);
    bool pass = (n1 != NULL) && (n2 != NULL) && (n3 != NULL)
        && (strcmp(n1->shortName, "001") == 0)
        && (strcmp(n2->shortName, "003") == 0)
        && (strcmp(n3->shortName, "005") == 0);
    avlFree(avl);
    iteratorFree(it);
    return pass;
}

bool testDelete1(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "010", "ten");
    avlInsert(avl, "005", "five");
    avlInsert(avl, "015", "fifteen");
    avlDelete(avl, "015");
    bool pass = (avl->size == 2) && (avlFind(avl, "015") == NULL) && (avl->root->rightChild == NULL);
    avlFree(avl);
    return pass;
}

bool testDelete2(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "010", "ten");
    avlInsert(avl, "005", "five");
    avlInsert(avl, "003", "three");
    avlDelete(avl, "005");
    bool pass = (avl->size == 2) && (avlFind(avl, "005") == NULL) && (strcmp(avl->root->leftChild->shortName, "003") == 0);
    avlFree(avl);
    return pass;
}

bool testDelete3(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "010", "ten");
    avlInsert(avl, "005", "five");
    avlInsert(avl, "003", "three");
    avlInsert(avl, "007", "seven");
    avlDelete(avl, "005");
    bool pass = (avl->size == 3) && (avlFind(avl, "005") == NULL)
        && (avlFind(avl, "010") != NULL)
        && (avlFind(avl, "003") != NULL)
        && (avlFind(avl, "007") != NULL);
    avlFree(avl);
    return pass;
}

bool testDeleteRoot(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "010", "ten");
    avlInsert(avl, "005", "five");
    avlDelete(avl, "010");
    bool pass = (avl->size == 1) && (strcmp(avl->root->shortName, "005") == 0);
    avlFree(avl);
    return pass;
}

bool testDeleteNonExistent(void)
{
    AVL* avl = newAVL();
    avlInsert(avl, "010", "ten");
    avlInsert(avl, "005", "five");
    avlDelete(avl, "042");
    bool pass = (avl->size == 2) && (avlFind(avl, "010") != NULL) && (avlFind(avl, "005") != NULL);
    avlFree(avl);
    return pass;
}

int test(void)
{
    bool (*tests[])(void) = {
        testInsert1, testInsert2,
        testFind1, testFind2,
        testIterator1, testIterator2,
        testDelete1, testDelete2, testDelete3,
        testDeleteRoot, testDeleteNonExistent
    };
    const int TEST_NUM = 11;
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
