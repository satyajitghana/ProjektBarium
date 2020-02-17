#include <stdio.h>
#include <stdarg.h>
#include <cstring>
#include <iostream>
#include "extern_func.hpp"

extern "C" DECLSPEC void display(char* str, ...) {
    va_list argp;
    va_start(argp, str);
    vprintf(str, argp);
    va_end(argp);
}

extern "C" DECLSPEC void displayln(char* str, ...) {
    char* outstr;
    va_list argp;
    va_start(argp, str);
    outstr = (char*)malloc(strlen(str) + 2);
    strcpy(outstr, str);
    strcat(outstr, "\n");
    vprintf(outstr, argp);
    va_end(argp);
    free(outstr);
}

// TODO: implement read
// extern "C" DECLSPEC void read(char* str, ...) {

// }