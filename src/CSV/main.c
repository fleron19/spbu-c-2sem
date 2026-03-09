#include "CSV.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GREEN(string) "\x1b[32m" string "\x1b[0m"
#define RED(string) "\x1b[31m" string "\x1b[0m"

bool compareTxtFiles(const char* fi, const char* se)
{
    FILE* f1 = fopen(fi, "r");
    FILE* f2 = fopen(se, "r");
    if (f1 == NULL || f2 == NULL)
        return false;
    int ch1;
    int ch2;

    while ((ch1 = getc(f1)) != EOF && (ch2 = getc(f2)) != EOF) {
        if (ch1 != ch2) {
            return false;
        }
    }

    fclose(f1);
    fclose(f2);
    return true;
}

int main(int argc, char** argv)
{
    bool testMode = false;
    for (int i = 0; i < argc; ++i) {
        if (strcmp(argv[i], "--test") == 0) {
            testMode = true;
            break;
        }
    }

    if (testMode) {
        int ret = 0;
        const char* ins[5] = {
            "tests/input/input1.csv",
            "tests/input/input2.csv",
            "tests/input/input3.csv",
            "tests/input/input4.csv",
            "tests/input/input5.csv",
        };
        const char* outs[5] = {
            "tests/output/output1.txt",
            "tests/output/output2.txt",
            "tests/output/output3.txt",
            "tests/output/output4.txt",
            "tests/output/output5.txt"
        };
        for (int testNum = 0; testNum < 5; ++testNum) {
            prettyPrinter(ins[testNum], "output.txt");
            bool res = compareTxtFiles("output.txt", outs[testNum]);
            if (res) {
                printf(GREEN("Test %d passed!\n"), testNum + 1);
            } else {
                printf(RED("Test %d failed!\n"), testNum + 1);
                ret = 1;
            }
        }
        return ret;
    }
    bool res = prettyPrinter("input.csv", "output.txt");
    printf("%s", res ? "Done\n" : "File not found\n");
    return 0;
}
