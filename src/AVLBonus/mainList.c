#include "ListTests.h"
#include "LinkedList.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED(string) "\x1b[31m" string "\x1b[0m"

void addAll(LinkedList* tree, FILE* file, char** keys)
{
    char buf[512];
    char valBuf[256];
    int i = 0;
    while (fgets(buf, 512, file)) {
        char* token1 = strtok(buf, ":");
        char* token2 = strtok(NULL, ":");
        if (token1 == NULL || token2 == NULL)
            continue;
        size_t len1 = strlen(token1);
        size_t len2 = strlen(token2);
        if (len1 >= 255 || len2 >= 255)
            continue;
        if (token2[len2 - 1] == '\n')
            token2[len2 - 1] = '\0';
        strncpy(keys[i], token1, 254);
        keys[i][254] = '\0';
        strncpy(valBuf, token2, 254);
        valBuf[254] = '\0';
        listInsert(tree, keys[i], valBuf);
        i++;
    }
}

void first(LinkedList* tree, char* keys[], int keysCnt)
{
    for (int i = 0; i < 50000; i++) {
        int r = rand() % keysCnt;
        listFind(tree, keys[r]);
    }
}

void second(LinkedList* tree, FILE* file, char* keys[], int keysCnt)
{
    char buf[512];
    char valBuf[256];
    char keyBuf[256];
    for (int i = 0; i < 10000; i++) {
        int op = rand();
        if (op % 2) {
            int r = rand() % keysCnt;
            listFind(tree, keys[r]);
        }
        else {
            fgets(buf, 512, file);
            char* token1 = strtok(buf, ":");
            char* token2 = strtok(NULL, ":");
            if (token1 == NULL || token2 == NULL)
                continue;
            size_t len1 = strlen(token1);
            size_t len2 = strlen(token2);
            if (len1 >= 255 || len2 >= 255)
                continue;
            if (token2[len2 - 1] == '\n')
                token2[len2 - 1] = '\0';
            strncpy(keyBuf, token2, 254);
            keyBuf[254] = '\0';
            strncpy(valBuf, token2, 254);
            valBuf[254] = '\0';
            listInsert(tree, keyBuf, valBuf);  
        }

    }
}
int main(int argc, char** argv)
{
    const int AIRPORTS_NUM = 9063;
    if (strcmp(argv[1], "--test") == 0) {
        return test();
    }

    LinkedList* list = newList();
    char** keys = malloc(AIRPORTS_NUM * sizeof(char*));
    for (int i = 0; i < AIRPORTS_NUM; i++) {
        keys[i] = malloc(256);
    }

    FILE* inptxt = fopen(argv[1], "r");
    if (inptxt == NULL) {
        printf(RED("Ошибка - файл %s не найден\n"), argv[1]);
        return 1;
    }

    FILE* codes = fopen(argv[2], "r");
    if (inptxt == NULL) {
        printf(RED("Ошибка - файл %s не найден\n"), argv[1]);
        return 1;
    }

    addAll(list, inptxt, keys);
    fclose(inptxt);

    if (strcmp(argv[3], "-f") == 0 || strcmp(argv[3], "-first") == 0) {
        first(list, keys, AIRPORTS_NUM);
    } else if (strcmp(argv[3], "-s") == 0 || strcmp(argv[3], "-second") == 0) {
        second(list, codes, keys, AIRPORTS_NUM);
    }

    for (int i = 0; i < AIRPORTS_NUM; i++) {
        free(keys[i]);
    }

    listFree(list);
    return 0;
}
