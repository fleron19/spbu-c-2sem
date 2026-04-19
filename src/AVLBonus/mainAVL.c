#include "AVLTree.h"
#include "AVLTests.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void first(AVL* tree) {
    
}
int main(int argc, char** argv)
{
    if (strcmp(argv[1], "--test") == 0) {
        return test();
    }

    int rowsCount = 0;
    AVL* avl = newAVL();

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
                avlFind(avl, arg);
            }

            if (strcmp(com, "delete") == 0) {
                char* arg = strtok(NULL, " \n");
                avlDelete(avl, arg);
            }

            if (strcmp(com, "add") == 0) {
                char* arg = strtok(NULL, "\n");
                char* token1 = strtok(arg, ":");
                char* token2 = strtok(NULL, "\n");
                avlInsert(avl, token1, token2);
            }
        }
    }

    avlFree(avl);
    return 0;
}
