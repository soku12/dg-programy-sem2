#include "struct.h"
#include "func.h"

int* readData2Buffer() {
	FILE* input = fopen("data.txt", "r");
	if (input == NULL) {
		printf("error accessing the data file");
	}
	int* buffer = calloc(6, sizeof(int));
	for (int i = 0; i < 6; i++) {
		fscanf(input, "%d", &buffer[i]);
	}
	fclose(input);
	return buffer;
}

machine machineInit(int* buffer) {
	machine output;

	output.CURRENT_STATE = buffer[0];
	output.coffee = buffer[1];
	output.water = buffer[2];
	output.milk = buffer[3];
	output.coffee_power = buffer[4];
	output.base_drink_size = buffer[5];
	output.iobuffer = buffer;

	output.func_tab[0] = run_OFF;
	output.func_tab[1] = run_MAIN_MENU;
	output.func_tab[2] = run_DRINK_SELECT;
	output.func_tab[3] = run_REFILL;
	output.func_tab[4] = run_SET_POWER;
	output.func_tab[5] = run_SET_SIZE;
	output.func_tab[6] = run_MAKE_SMALL;
	output.func_tab[7] = run_MAKE_BIG;
	output.func_tab[8] = run_MAKE_ESPRESSO;
	output.func_tab[9] = run_MAKE_CAPUCCINO;
	output.func_tab[10] = run_MAKE_MILK;
	output.func_tab[11] = run_EXIT;

	return output;
}

void dumpMachine2Buffer(machine* mach) {
	mach->iobuffer[0] = mach->CURRENT_STATE;
	mach->iobuffer[1] = mach->coffee;
	mach->iobuffer[2] = mach->water;
	mach->iobuffer[3] = mach->milk;
	mach->iobuffer[4] = mach->coffee_power;
	mach->iobuffer[5] = mach->base_drink_size;
}

void saveBuffer2File(int* buffer) {
	FILE* output = fopen("data.txt", "w");
	if (output == NULL) {
		printf("error accessing the data file");
	}
	for (int i = 0; i < 6; i++) {
		fprintf(output, "%d\n", buffer[i]);
	}
	fclose(output);
}