#ifndef FUNC_H
#define FUNC_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <crtdbg.h>
#include <string.h>
#include <conio.h>

#include "struct.h"

//sub-function for qsort, compares elements based on their ID
int compID(const void* p1, const void* p2);

//sub-function for qsort, compares elements based on their names (alphabetical order)
int compAB(const void* p1, const void* p2);

//sorts array elements by ID and prints them orderly, then sorts them alphabetically and prints them again
void sortnPrint(DaneOsobowe* tab, int tabsize);

#endif