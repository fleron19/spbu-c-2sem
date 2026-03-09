#pragma once
#include <stdbool.h>

// static void countColumnsAndRows(const char* inp, int* rows, int* columns);
// static int* makeArrayOfWidth(const char* inp, int rows, int columns);
// static void printRow(FILE* out, char* buffer, const int* widths, int columns, bool heading);
// static void printRows(const char* inp, const char* out, int* widths, int rows, int columns);
bool prettyPrinter(const char* inp, const char* out);
