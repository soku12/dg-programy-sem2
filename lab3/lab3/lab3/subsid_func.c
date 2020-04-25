#include "func.h"
#include "struct.h"

char* getstring() {
	char* output = calloc(201, sizeof(char));
	char c = getchar();
	int i = 1, blocks = 2;
	while (c != '\n') {
		if (i % 200 == 0) {
			output = realloc(output, (blocks++)*(200 * sizeof(char)));
		}
		output[i - 1] = c;
		c = getchar();

		i++;
	}
	output[i - 1] = '\0';

	return output;
}

unsigned long int byteArray2int(unsigned char* sequence, int mode) {
	switch (mode) {
	case 2: return sequence[0] + (sequence[1] * 256); 
			break;
	case 4:	return sequence[0] + (sequence[1] * 256) + (sequence[2] * 65536) + (sequence[3] * 16777216); 
			break;
	default: return 0; break;
	}
}
