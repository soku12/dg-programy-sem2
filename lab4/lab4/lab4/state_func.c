#include "struct.h"
#include "func.h"
#include "keymaps.h"

state run_EXIT(machine* mach) {
	return EXIT;
}

state run_OFF(machine* mach) {
	renderMenu(mach);
	char key;
	while (1) {
		key = _getch();
		switch (key) {
			case ESC:
				dumpMachine2Buffer(mach);
				saveBuffer2File(mach->iobuffer);
				free(mach->iobuffer);
				_CrtDumpMemoryLeaks();
				exit(0);
				break;
			case KEY_1:
				return MAIN_MENU;
				break;
			default:
				break;
		}
	}
}

state run_MAIN_MENU(machine* mach) {
	renderMenu(mach);
	char key;
	while (1) {
		key = _getch();
		switch (key) {
			case ESC:
				dumpMachine2Buffer(mach);
				saveBuffer2File(mach->iobuffer);
				free(mach->iobuffer);
				_CrtDumpMemoryLeaks();
				exit(0);
				break;
			case KEY_1:
				return DRINK_SELECT;
				break;
			case KEY_2:
				return REFILL;
				break;
			case KEY_3:
				return SET_POWER;
				break;
			case KEY_4:
				return SET_SIZE;
				break;
			case KEY_5:
				return OFF;
			default:
				break;
		}
	}
}

state run_DRINK_SELECT(machine* mach) {
	renderMenu(mach);
	char key;
	while (1) {
		key = _getch();
		switch (key) {
		case ESC:
			return MAIN_MENU;
			break;
		case KEY_1:
			return MAKE_SMALL;
			break;
		case KEY_2:
			return MAKE_BIG;
			break;
		case KEY_3:
			return MAKE_ESPRESSO;
			break;
		case KEY_4:
			return MAKE_CAPUCCINO;
			break;
		case KEY_5:
			return MAKE_MILK;
		default:
			break;
		}
	}
}

state run_REFILL(machine* mach) { 
	char key;
	renderMenu(mach);
	while (key = _getch()) {
		switch (key) {
			case SPACE:
				if (mach->coffee < 100) {
					mach->coffee += 1;
				}
				if (mach->water < 200) {
					mach->water += 1;
				}
				if (mach->milk < 100) {
					mach->milk += 1;
				}
				break;
			case ESC:
				return MAIN_MENU;
				break;
		}
		renderMenu(mach);
	}
}
//"not all control paths return a value" yada yada
//they aint supposed to, at least not in this case (3 cases to be precise)

state run_SET_POWER(machine* mach) {
	char key;
	renderMenu(mach);
	while (key = _getch()) {
		if (key == PLUS && mach->coffee_power < 5) {
			mach->coffee_power += 1;
		}
		else if (key == MINUS && mach->coffee_power > 1) {
			mach->coffee_power -= 1;
		}
		else if (key == ESC) {
			return MAIN_MENU;
		}
		renderMenu(mach);
	}
}

state run_SET_SIZE(machine* mach) {
	char key;
	renderMenu(mach);
	while (key = _getch()) {
		if (key == PLUS && mach->base_drink_size < 5) {
			mach->base_drink_size += 1;
		}
		else if (key == MINUS && mach->base_drink_size > 1) {
			mach->base_drink_size -= 1;
		}
		else if (key == ESC) {
			return MAIN_MENU;
		}
		renderMenu(mach);
	}
}

state run_state(state wanted_state, machine * mach)
{
	return mach->func_tab[wanted_state](mach);
}