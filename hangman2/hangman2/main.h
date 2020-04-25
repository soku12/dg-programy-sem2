#ifndef MAIN_H
#define MAIN_H


#ifdef _MSC_VER //if the compiler is Visual C
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#include "struct.h"
#include "engine.h"
#include "editor.h"
#include "manager.h"
#include "game.h"
#include "file_operations.h"
#include "keymaps.h"
#include "assisting_functions.h"
#include "initialisers.h"

#endif