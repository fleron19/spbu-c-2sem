#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CSV.h"

void countColumnsAndRows(const char* inp, int* rows, int* columns)
{
    FILE* file = fopen(inp, "r");
    char buf[1024];
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
        for (int j = 0; j < columns; j++) {
            width[j] = ((int)strlen(token) > width[j]) ? (int)strlen(token) : width[j];
            token = strtok(NULL, ",");
        }
    }

    fclose(stream);
    return width;
}
void printRow(FILE* out, char* buffer, int* widths, int columns, bool heading)
{
    fprintf(out, "| ");
    char* endp = NULL;
    char* token = strtok(buffer, ",");
    for (int j = 0; j < columns; j++) {
        endp = NULL;
        double res = strtod(token, &endp);
        if ((*endp != 0 && res == 0.0) || heading) {
            fprintf(out, "%s", token);
            for (int q = 0; q < (int)(widths[j] - strlen(token)) + 1; q++) {
                fprintf(out, " ");
            }
        } else {
            for (int q = 0; q < (int)(widths[j] - strlen(token)) + 1; q++) {
                fprintf(out, " ");
            }
            fprintf(out, "%s", token);
        }
        fprintf(out, "|");
        if (j != columns - 1) {
            fprintf(out, " ");
        }
        token = strtok(NULL, ",");
    }
    fprintf(out, "\n");
    for (int k = 0; k < columns; k++) {
        fprintf(out, "+");
        for (int q = 0; q < widths[k] + 2; q++) {
            if (heading) {
                fprintf(out, "=");
            } else {
                fprintf(out, "-");
            }
        }
    }
    fprintf(out, "+\n");
}
void printRows(const char* inp, const char* out, int* widths, int rows, int columns)
{
    FILE* input = fopen(inp, "r");
    FILE* output = fopen(out, "w");

    for (int k = 0; k < columns; k++) {
        fprintf(output, "+");
        for (int q = 0; q < widths[k] + 2; q++) {
            fprintf(output, "=");
        }
    }
    fprintf(output, "+\n");

    char buffer[1024];
    for (int i = 0; i < rows; i++) {
        fgets(buffer, 1024, input);
        buffer[strcspn(buffer, "\n")] = 0;
        if (i == 0) {
            printRow(output, buffer, widths, columns, true);
        } else {
            printRow(output, buffer, widths, columns, false);
        }
    }

    fclose(output);
    fclose(input);
}

bool prettyPrinter(const char* inp, const char* out)
{
    FILE* input = fopen(inp, "r");
    if (input == NULL) {
        return false;
        printf("%s not found\n", inp);
    }
    fclose(input);
    int columnsNum = 0;
    int rowsNum = 0;
    countColumnsAndRows(inp, &rowsNum, &columnsNum);

    int* width = makeArrayOfWidth(inp, rowsNum, columnsNum);
    printRows(inp, out, width, rowsNum, columnsNum);

    printf("%d columns\n", columnsNum);
    printf("%d rows\n", rowsNum);

    for (int i = 0; i < columnsNum; i++) {
        printf("%d ", width[i]);
    }
    printf("\n");

    free(width);
    return true;
}

int main()
{
    prettyPrinter("input1.csv", "output.txt");
    return 0;
}
