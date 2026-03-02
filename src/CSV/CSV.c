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

int* makeArrayOfWidth(const char* inp, int rows, int columns)
{
    int* width = (int*)calloc(columns, sizeof(int));

    char buffer[1024];
    FILE* stream = fopen(inp, "r");

    for (int i = 0; i < rows; i++) {
        fgets(buffer, 1024, stream);
        buffer[strcspn(buffer, "\n")] = 0;
        char* token = strtok(buffer, ",");
        width[0] = (strlen(token) > width[0]) ? strlen(token) : width[0];
        for (int j = 1; j < columns; j++) {
            printf("%s\n", token);
            token = strtok(NULL, ",");
            width[j] = (strlen(token) > width[j]) ? strlen(token) : width[j];
        }
    }

    return width;
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

    int* width = makeArrayOfWidth(inp, rowsNum, columnsNum);

    printf("%d columns\n", columnsNum);
    printf("%d rows\n", rowsNum);

    for (int i = 0; i < columnsNum; i++) {
        printf("%d ", width[i]);
    }
    printf("\n");
    return true;
}

int main()
{
    prettyPrinter("input.csv", "output.txt");
    return 0;
}
