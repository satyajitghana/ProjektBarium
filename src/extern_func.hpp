#pragma once

#define DECLSPEC

extern "C" DECLSPEC void display(char* str, ...);

extern "C" DECLSPEC void displayln(char* str, ...);

extern "C" DECLSPEC void read(char* str, ...) {