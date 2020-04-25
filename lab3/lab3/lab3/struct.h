#ifndef STRUCT_H
#define STRUCT_H

struct pixel {
	unsigned char R;
	unsigned char G;
	unsigned char B;
};

typedef struct pixel pixel;

struct bitmap {
	unsigned long int fileSize;
	unsigned int dataOffset; //the index of the first byte of the pixel data array in the buffer
	unsigned int width;
	unsigned int height;
	unsigned char* pixelDataPointer; //a pointer to the start of the pixel data array in the buffer
	pixel** pixelArray;
};

typedef struct bitmap bitmap;

#endif
