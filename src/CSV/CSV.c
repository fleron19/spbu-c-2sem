#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a, b) ((a) > (b) ? (a) : (b))

void countColumnsAndRows(const char* inp, int* rows, int* columns)
{
    FILE* file = fopen(inp, "r");
    char buf[1024];
    char* token = strtok(buf, ",");
    while (fgets(buf, 1024, file)) {
        (*rows)++;
        if ((*rows) == 1) {
            for (int i = 0; buf[i] != '\0'; i++) {
                if (buf[i] == ',') {
                    (*columns)++;
                }
            }
            (*columns)++;
        }
    }

    fclose(file);
}

void makeArray(const char* inp, int* rows, int* columns)
{
    return;
}

bool prettyPrinter(const char* inp, const char* out)
{
    FILE* input = fopen(inp, "r");
    if (input == NULL) {
        return false;
    }
    fclose(input);
    int columnsNum = 0;
    int rowsNum = 0;
    countColumnsAndRows(inp, &rowsNum, &columnsNum);

    printf("%d columns\n", columnsNum);
    printf("%d rows\n", rowsNum);
    printOneColumn("input.csv", "output.txt", 0, rowsNum);
    return true;
}

int main()
{
    prettyPrinter("input.csv", "output.txt");
    return 0;
}
