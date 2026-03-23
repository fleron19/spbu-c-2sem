#include "AVLTree.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define RED(string) "\x1b[31m" string "\x1b[0m"

int main(int argc, char** argv)
{
    if (argc == 1) {
        printf(RED("Ошибка - укажите в качестве аргумента путь к файлу с аэропортами\n"));
        return 1;
    }
    FILE* inptxt = fopen(argv[1], "r+");
    if (inptxt == NULL) {
        printf(RED("Ошибка - файл %s не найден\n"), argv[1]);
        return 1;
    }

    int rowsCount = 0;
    AVL* avl = newAVL();
    char buf[1024];
    while (fgets(buf, 1024, inptxt)) {
        char* token1 = strtok(buf, ":");
        char* token2 = strtok(NULL, ":\n");
        //printf("%s %s \n", token1, token2);
        avlInsert(avl, token1, token2);
        rowsCount++;
    }

    printf("Загружено %d аэропортов. Система готова к работе.\n", rowsCount);
    bool end = false;
    char inp[256];
    while (!end) {
        fgets(inp, 256, stdin);
        if (strcmp(inp, "quit\n") == 0) {
            end = true;
        } else if (strcmp(inp, "save") == 0) {
            ;
        } else {
            char* com = strtok(inp, " ");
            const char* arg = strtok(NULL, " \n");
            if (strcmp(com, "find") == 0) {
                const char* res = avlFind(avl, arg);
                if (res != NULL) {
                    printf("%s → %s\n", arg, res);
                }
                else {
                    printf("Аэропорт с кодом '%s' не найден в базе.\n", arg);
                }
            }
        }
    }
    return 0;
}
