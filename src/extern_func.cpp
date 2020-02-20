#include <stdio.h>
#include <stdarg.h>
#include "extern_func.hpp"

extern "C" DECLSPEC void display(char* str, ...) {
    va_list argp;
    va_start(argp, str);
    vprintf(str, argp);
    va_end(argp);
}