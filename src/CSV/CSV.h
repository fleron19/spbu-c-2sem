#pragma once

#include <stdlib.h>

void countColumnsAndRows(const char* inp, int* rows, int* columns);
int* makeArrayOfWidth(const char* inp, int rows, int columns);
void printRow(FILE* out, char* buffer, int* widths, int columns, bool heading);
void printRows(const char* inp, const char* out, int* widths, int rows, int columns);
bool prettyPrinter(const char* inp, const char* out);
