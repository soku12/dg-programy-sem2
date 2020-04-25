#include "func.h"
#include "struct.h"

int main() {
	// getting the output and input file names
	printf("input file name (with .bmp):\t");
	char* inputName = getstring();

	printf("output file name (with .bmp):\t");
	char* outputName = getstring();

	// opening the input file for reading
	FILE * input = fopen(inputName, "rb");
	// checking if the file was accessed succesfully
	if (input == NULL) {
		printf("\nerror accessing the input file\n");
		_getch();

		free(inputName);
		free(outputName);

		_CrtDumpMemoryLeaks();
		return 0;
	}

	// loading the input file into the buffer for processing
	unsigned char* buffer = loadToBuffer(input);
	fclose(input);

	// checking if the file is a valid bitmap
	if (buffer[0] != 'B' && buffer[1] != 'M') { // every bitmap file starts with "BM"
		printf("incorrect input file format\n");
		_getch();

		free(buffer);
		free(inputName);
		free(outputName);

		_CrtDumpMemoryLeaks();
		return 0;
	}

	// reading useful data from the file into a bitmap struct
	bitmap bmp = readHeaderData(buffer);
	bmp.pixelArray = createPixelArray(bmp);

	// making the picture monochromatic
	makeMonochromatic(bmp);

	// copying the processed picture into the buffer for saving
	pixelArray2Buffer(bmp);


	// opening the output file and checking if it was accessed succesfully
	FILE* output = fopen(outputName, "wb");
	if (output == NULL) {
		printf("\nerror accessing the output file\n");
		_getch();

		deletePixelArray(bmp);
		free(buffer);
		free(inputName);
		free(outputName);

		_CrtDumpMemoryLeaks();
		return 0;
	}

	// saving the image into the file
	fwrite(buffer, sizeof(char), bmp.fileSize, output);
	fclose(output);

	printf("Operation successful! Press any key");
	_getch();

	// cleaning the memory
	deletePixelArray(bmp);
	free(buffer);
	free(inputName);
	free(outputName);

	_CrtDumpMemoryLeaks();
	return 0;
}