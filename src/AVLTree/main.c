#include "AVLTree.h"
#include "tests.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define RED(string) "\x1b[31m" string "\x1b[0m"

void save(AVL* tree, char* filename)
{
    Iterator* it = iteratorInit(tree);
    int cnt = 0;
    FILE* out = fopen(filename, "w");
    if (out == NULL) {
        printf(RED("Ошибка - файл %s не найден\n"), filename);
        return;
    }
    while (iteratorHasNext(it)) {
        cnt++;
        Node* curr = iteratorNext(it);
        fprintf(out, "%s:%s\n", curr->shortName, curr->fullName);
    }
    iteratorFree(it);
    fflush(out);
    fclose(out);
    printf("База сохранена: %d аэропортов.\n", cnt);
}

void find(AVL* tree, char* arg)
{
    const char* res = avlFind(tree, arg);
    if (res != NULL) {
        printf("%s → %s\n", arg, res);
    } else {
        printf(RED("Аэропорт с кодом '%s' не найден в базе.\n"), arg);
    }
}

void delete(AVL* tree, char* arg)
{
    avlDelete(tree, arg);
    printf("Аэропорт '%s' удалён из базы.\n", arg);
}

void add(AVL* tree, char* arg)
{
    // printf("%s\n", arg);
    char* token1 = strtok(arg, ":");
    char* token2 = strtok(NULL, "\n");
    // printf("%s\n", token1);
    // printf("%s\n", token2);
    avlInsert(tree, token1, token2);
    printf("Аэропорт '%s' добавлен в базу.\n", arg);
}

int main(int argc, char** argv)
{
    if (argc == 1) {
        printf(RED("Ошибка - укажите в качестве аргумента путь к файлу с аэропортами\n"));
        return 1;
    }

    if (strcmp(argv[1], "--test") == 0) {
        return test();
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
        // printf("%s %s \n", token1, token2);
        avlInsert(avl, token1, token2);
        rowsCount++;
    }

    printf("Загружено %d аэропортов. Система готова к работе.\n", rowsCount);
    fclose(inptxt);

    bool end = false;
    char inp[256];
    while (!end) {
        if (fgets(inp, 256, stdin) == NULL)
            break;
        if (strcmp(inp, "quit\n") == 0) {
            end = true;
        } else if (strcmp(inp, "save\n") == 0) {
            save(avl, argv[1]);
        } else {
            char* com = strtok(inp, " \n");
            if (strcmp(com, "find") == 0) {
                char* arg = strtok(NULL, " \n");
                find(avl, arg);
            }

            if (strcmp(com, "delete") == 0) {
                char* arg = strtok(NULL, " \n");
                delete (avl, arg);
            }

            if (strcmp(com, "add") == 0) {
                char* arg = strtok(NULL, "\n");
                add(avl, arg);
            }
        }
    }

    avlFree(avl);
    return 0;
}
