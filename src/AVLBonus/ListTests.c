#include "ListTests.h"
#include "LinkedList.h"
#include <stdio.h>
#include <string.h>

#define GREEN(string) "\x1b[32m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"

bool testInsert1(void)
{
    LinkedList* list = newList();
    listInsert(list, "BBB123", "BBB full val");
    listInsert(list, "AAA123", "AAA full val");
    listInsert(list, "CCC123", "CCC full val");
    bool pass1 = strcmp(list->head->value, "BBB full val") == 0;
    bool pass2 = strcmp(list->head->next->value, "AAA full val") == 0;
    bool pass3 = strcmp(list->head->next->next->value, "CCC full val") == 0;
    listFree(list);
    return pass1 && pass2 && pass3;
}

bool testFind1(void)
{
    LinkedList* list = newList();
    listInsert(list, "5", "five");
    listInsert(list, "1", "one");
    listInsert(list, "66", "six");
    listInsert(list, "888", "eight");
    const char* res = listFind(list, "888");
    bool pass = (res != NULL) && (strcmp(res, "eight") == 0);
    listFree(list);
    return pass;
}

bool testFind2(void)
{
    LinkedList* list = newList();
    listInsert(list, "5", "five");
    listInsert(list, "1", "one");
    listInsert(list, "66", "six");
    listInsert(list, "888", "eight");
    const char* res = listFind(list, "12");
    bool pass = (res == NULL);
    listFree(list);
    return pass;
}

bool testDelete1(void)
{
    LinkedList* list = newList();
    listInsert(list, "10", "ten");
    listInsert(list, "5", "five");
    listInsert(list, "155", "fifteen");
    listDelete(list, "155");
    bool pass = (list->size == 2) && (listFind(list, "155") == NULL);
    return pass;
    listFree(list);
}

bool testDelete2(void)
{
    LinkedList* list = newList();
    listInsert(list, "10", "ten");
    listInsert(list, "5", "five");
    listInsert(list, "155", "fifteen");
    listDelete(list, "5");
    bool pass = (list->size == 2) && (listFind(list, "5") == NULL);
    return pass;
    listFree(list);
}

bool testDelete3(void)
{
    LinkedList* list = newList();
    listInsert(list, "10", "ten");
    listInsert(list, "5", "five");
    listInsert(list, "33", "three");
    listInsert(list, "777", "seven");
    listDelete(list, "5");
    bool pass = (list->size == 3) && (listFind(list, "5") == NULL)
        && (listFind(list, "10") != NULL)
        && (listFind(list, "33") != NULL)
        && (listFind(list, "777") != NULL);
    listFree(list);
    return pass;
}

bool testDeleteHead(void)
{
    LinkedList* list = newList();
    listInsert(list, "10", "ten");
    listInsert(list, "5", "five");
    listDelete(list, "10");
    bool pass = (list->size == 1) && (strcmp(list->head->key, "5") == 0);
    listFree(list);
    return pass;
}

bool testDeleteNonExistent(void)
{
    LinkedList* list = newList();
    listInsert(list, "10", "ten");
    listInsert(list, "5", "five");
    listDelete(list, "42");
    bool pass = (list->size == 2) && (listFind(list, "10") != NULL) && (listFind(list, "5") != NULL);
    listFree(list);
    return pass;
}

int test(void)
{
    bool (*tests[])(void) = {
        testInsert1, testFind1, testDelete1,
        testDelete2, testDelete3,
        testDeleteHead, testDeleteNonExistent
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
