#include "struct.h"
#include "func.h"

int main() {
	int* iobuffer = readData2Buffer();
	machine coffee_machine = machineInit(iobuffer);
	
	while (1) {
		coffee_machine.CURRENT_STATE = run_state(coffee_machine.CURRENT_STATE, &coffee_machine);
		if (coffee_machine.CURRENT_STATE = EXIT) {

		}
	}

}