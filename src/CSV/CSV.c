#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CSV.h"

static int* makeArrayOfWidth(char** list, size_t rows, size_t columns)
{
    int* width = NULL;
    if (columns) {
        width = (int*)calloc(columns, sizeof(int));
    }
    char* curr = NULL;
    for (size_t i = 0; i < rows; i++) {
        curr = strdup(list[i]);
        if (curr == NULL)
            continue;
        char* copy = curr;
        copy[strcspn(copy, "\n")] = 0;
        char* token = strtok(copy, ",");
        for (size_t j = 0; j < columns; j++) {
            if (token == NULL)
                break;
            width[j] = ((int)strlen(token) > width[j]) ? (int)strlen(token) : width[j];
            token = strtok(NULL, ",");
        }
        free(curr);
    }

    return width;
}
static void printRow(FILE* out, char* buffer, const int* widths, size_t columns, bool heading)
{
    fprintf(out, "| ");
    char* endp = NULL;
    char* token = strtok(buffer, ",");
    for (size_t j = 0; j < columns; j++) {
        if (token == NULL)
            break;
        endp = NULL;
        double res = strtod(token, &endp);
        if ((*endp != 0 && res == 0.0) || heading) {
            fprintf(out, "%s", token);
            for (size_t q = 0; q < (size_t)(widths[j] - strlen(token)); q++) {
                fprintf(out, " ");
            }
        } else {
            for (size_t q = 0; q < (size_t)(widths[j] - strlen(token)); q++) {
                fprintf(out, " ");
            }
            fprintf(out, "%s", token);
        }
        fprintf(out, " |");
        if (j != columns - 1) {
            fprintf(out, " ");
        }
        token = strtok(NULL, ",");
    }
    fprintf(out, "\n");
    for (size_t k = 0; k < columns; k++) {
        fprintf(out, "+");
        for (size_t q = 0; q < (size_t)(widths[k] + 2); q++) {
            if (heading) {
                fprintf(out, "=");
            } else {
                fprintf(out, "-");
            }
        }
    }
    fprintf(out, "+\n");
}
static void printRows(char** list, FILE* output, int* widths, size_t rows, size_t columns)
{
    for (size_t k = 0; k < columns; k++) {
        fprintf(output, "+");
        for (size_t q = 0; q < (size_t)(widths[k] + 2); q++) {
            fprintf(output, "=");
        }
    }
    if (rows != 0 && columns != 0) {
        fprintf(output, "+\n");
    };

    char* curr = NULL;
    for (size_t i = 0; i < rows; i++) {
        curr = list[i];
        if (i == 0) {
            printRow(output, curr, widths, columns, true);
        } else {
            printRow(output, curr, widths, columns, false);
        }
    }
}

bool prettyPrinter(const char* inp, const char* out)
{

    FILE* input = fopen(inp, "r");
    FILE* output = fopen(out, "w");

    if (input == NULL || output == NULL) {
        if (output != NULL) {
            fclose(output);
        }
        return false;
    }

    size_t listSize = 1024;
    size_t rowsNum = 0;
    size_t columnsNum = 0;
    char** list = malloc(listSize);
    char line[8192];

    while (fgets(line, sizeof(line), input)) {
        list[rowsNum] = malloc(8192 * sizeof(char));
        if (list[rowsNum] == NULL) {
            for (size_t i = 0; i < rowsNum; i++) {
                free(list[i]);
            }
            free(list);
            fclose(input);
            return false;
        }

        for (int i = 0; i < 8192; i++) {
            if (line[i] == '\n') {
                line[i] = 0;
                break;
            }
        }
        strncpy(list[rowsNum], line, 8191);
        list[rowsNum][8191] = '\0';
        rowsNum++;
        if (rowsNum >= listSize) {
            listSize *= 2;
            char** temp = realloc(list, listSize * sizeof(char*));
            if (temp == NULL) {
                for (size_t i = 0; i < rowsNum; i++) {
                    free(list[i]);
                }
                free(list);
                fclose(input);
                fclose(output);
                return false;
            }
            list = temp;
        }
    }

    fclose(input);

    if (rowsNum > 0) {
        for (size_t i = 0; list[0][i] != '\0'; i++) {
            if (list[0][i] == ',') {
                columnsNum++;
            }
        }
    }
    columnsNum++;
    int* width = makeArrayOfWidth(list, rowsNum, columnsNum);
    printRows(list, output, width, rowsNum, columnsNum);

    fclose(output);
    free(width);

    for (size_t i = 0; i < rowsNum; i++) {
        free(list[i]);
    }
    free(list);
    return true;
}
