#include "func.h"
#include "struct.h"

unsigned char* loadToBuffer(FILE* file) {
	unsigned long int filesize = 0;

	// getting the filesize without pre-allocating the buffer
	fseek(file, 0, SEEK_END);
	filesize = ftell(file);
	rewind(file);

	unsigned char* buffer = calloc(filesize, sizeof(char));
	fread(buffer, sizeof(char), filesize, file);

	return buffer;
}

bitmap readHeaderData(unsigned char* buffer) {
	bitmap bmp;
	bmp.fileSize = byteArray2int(&buffer[2], 4);
	bmp.dataOffset = byteArray2int(&buffer[10], 4);
	bmp.width = byteArray2int(&buffer[18], 4);
	bmp.height = byteArray2int(&buffer[22], 4);
	bmp.pixelDataPointer = &(buffer[bmp.dataOffset]);
	return bmp;
}

pixel** createPixelArray(bitmap bmp) {
	pixel** array = calloc(bmp.height, sizeof(pixel*)); //create <height> rows
	for (unsigned int i = 0; i < bmp.height; i++) { //for each row
		array[i] = calloc(bmp.width, sizeof(pixel)); //create <width> pixels
	}

	int counter = 0;
	for (unsigned int i = 0; i < bmp.height; i++) { //for each row
		for (unsigned int u = 0; u < bmp.width; u++) { //for each pixel in the row
			array[i][u].B = bmp.pixelDataPointer[counter++];
			array[i][u].G = bmp.pixelDataPointer[counter++];
			array[i][u].R = bmp.pixelDataPointer[counter++];
		}
	}
	return array;
}

void makeMonochromatic(bitmap bmp) {
	for (unsigned int i = 0; i < bmp.height; i++) { //for each row
		for (unsigned int u = 0; u < bmp.width; u++) { //for each pixel in the row
			float gray = (bmp.pixelArray[i][u].R + bmp.pixelArray[i][u].G + bmp.pixelArray[i][u].B) / 3;
			bmp.pixelArray[i][u].R = gray;
			bmp.pixelArray[i][u].G = gray;
			bmp.pixelArray[i][u].B = gray;
		}
	}
}

void pixelArray2Buffer(bitmap bmp) {
	int counter = 0;
	for (unsigned int i = 0; i < bmp.height; i++) { //for each row
		for (unsigned int u = 0; u < bmp.width; u++) { //for each pixel in the row
			bmp.pixelDataPointer[counter++] = bmp.pixelArray[i][u].B;
			bmp.pixelDataPointer[counter++] = bmp.pixelArray[i][u].G;
			bmp.pixelDataPointer[counter++] = bmp.pixelArray[i][u].R;
		}
	}
}

void deletePixelArray(bitmap bmp) {
	for (unsigned int i = 0; i < bmp.height; i++) { //for each row
		free(bmp.pixelArray[i]); //delete all pixels in the row
	}
	free(bmp.pixelArray); //delete all the rows
}