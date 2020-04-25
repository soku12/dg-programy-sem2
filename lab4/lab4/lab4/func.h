#ifndef FUNC_H
#define FUNC_H

#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
#include <conio.h>
#include "struct.h"


// state_func.c

// these are all state functions, pretty straightforward

state run_EXIT(machine* mach);

state run_OFF(machine* mach);

state run_MAIN_MENU(machine* mach);

state run_DRINK_SELECT(machine* mach);

state run_REFILL(machine* mach);

state run_SET_POWER(machine* mach);

state run_SET_SIZE(machine* mach);

// the main state machine function, runs in a constant loop
state run_state(state wanted_state, machine * mach);


// drinks_func.c

// more state functions, i put these in a separate file to reduce bloat in state_func.c

state run_MAKE_SMALL(machine* mach);

state run_MAKE_BIG(machine* mach);

state run_MAKE_ESPRESSO(machine* mach);

state run_MAKE_CAPUCCINO(machine* mach);

state run_MAKE_MILK(machine* mach);


// file_op_func.c

// reads the machine state data from data.txt file
int* readData2Buffer();

// initialises the machine with data read from the file
machine machineInit(int* buffer);

// dumps the machine variables into the I/O buffer for saving
void dumpMachine2Buffer(machine* mach);

// save the dumped variables into the data.txt file
void saveBuffer2File(int* buffer);


// other_func.c

// universal UI renderer
void renderMenu(machine* mach);

// not a state function per se so i put in here
// function made to minimize code repetition in state functions of every drink
state makeCoffee(machine* mach);

#endif