#include <stdio.h>
#include <conio.h>

#ifndef FUNKCJE_H
#define FUNKCJE_H

//Calculates and returns the control digit of the PESEL
int check(char pesel[]);

//Shows the birth date and sex on the screen based on the PESEL number
void printDateAndSex(char pesel[]);

#endif