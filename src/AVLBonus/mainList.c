#include "LinkedList.h"
#include "ListTests.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (strcmp(argv[1], "--test") == 0) {
        return test();
    }

    int rowsCount = 0;
    LinkedList* list = newList();

    bool end = false;
    char inp[256];
    while (!end) {
        if (fgets(inp, 256, stdin) == NULL)
            break;
        if (strcmp(inp, "quit\n") == 0) {
            end = true;
        } else {
            char* com = strtok(inp, " \n");
            if (strcmp(com, "find") == 0) {
                char* arg = strtok(NULL, " \n");
                listFind(list, arg);
            }

            if (strcmp(com, "delete") == 0) {
                char* arg = strtok(NULL, " \n");
                listDelete(list, arg);
            }

            if (strcmp(com, "add") == 0) {
                char* arg = strtok(NULL, "\n");
                char* token1 = strtok(arg, ":");
                char* token2 = strtok(NULL, "\n");
                listInsert(list, token1, token2);
            }
        }
    }

    listFree(list);
    return 0;
}
