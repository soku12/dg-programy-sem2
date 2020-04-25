#ifndef FUNC_H
#define FUNC_H

#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <stdio.h>
#include <string.h>
#include <crtdbg.h>
#include <conio.h>
#include <stdlib.h>


// subsid_func.h

// a standard string input function with dynamic memory allocation 
// (though no more realloc after every char)
// returns: the pointer to the string
char* getstring();

// turns a sequence of 4 bytes (little-endian) into an integer
// required to read all sorts of useful info (like image dimensions) from the bitmap file
// params: a pointer to the first element in the byte sequence, reading mode - 2 for reading 2 bytes, 4 for reading 4 bytes
// returns: the created integer
unsigned long int byteArray2int(unsigned char* sequence, int mode);



// file_op_func.h

// reads the file and saves it to a dynamically allocated array of bytes
// params: a pointer to the input file
// returns: a pointer to the array
unsigned char* loadToBuffer(FILE* file);

// creates a bitmap structure, and fills it with data read from the file
// data includes: file size, byte offset the the pixel array, width, height, 
// amount of pixels and a pointer to the pixel array
// params: a byte array read from file using loadToBuffer function
// returns: the created bitmap
struct bitmap readHeaderData(unsigned char* buffer);

// creates a two-dimensional array of individual pixels, with the same dimensions as the input bitmap
// params: the bitmap to process
// returns: the pixel array pointer
struct pixel** createPixelArray(struct bitmap bmp);

// makes the bitmap monochromatic by calculating an arithmetic average of the colors of each pixel
// params: the bitmap to process
void makeMonochromatic(struct bitmap bmp);

// saves the pixel array of the bitmap into the buffer for saving
// params: the bitmap to process
void pixelArray2Buffer(struct bitmap bmp);

// removes the pixel array of the bitmap from memory
// params: the bitmap to process
void deletePixelArray(struct bitmap bmp);


#endif
