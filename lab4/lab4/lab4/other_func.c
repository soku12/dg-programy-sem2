#include "struct.h"
#include "func.h"
#include "keymaps.h"

void renderMenu(machine* mach) {
	system("cls");

	switch (mach->CURRENT_STATE) {
		case OFF:
			printf("What do you wanna do?\n");
			printf("1\tTurn ON the coffee machine\n");
			printf("ESC\tQuit\n");
			break;
		case MAIN_MENU:
			printf("What do you wanna do?\n");
			printf("1\tMake a drink\n");
			printf("2\tRefill\n");
			printf("3\tChange the coffee strength (current: %d)\n", mach->coffee_power);
			printf("4\tChange the base drink size (current: %d)\n", mach->base_drink_size);
			printf("5\tTurn OFF the machine\n");
			printf("ESC\tQuit\n");
			break;
		case DRINK_SELECT:
			printf("Pick a drink to make\n");
			printf("1\tSmall coffee\t\t\tFUEL:\n");
			printf("2\tLarge coffee\t\t\tCoffee: %d\n", mach->coffee);
			printf("3\tEspresso\t\t\tWater: %d\n", mach->water);
			printf("4\tCapuccino\t\t\tMilk: %d\n", mach->milk);
			printf("5\tHot milk\n");
			printf("ESC\tBack to main menu\n");
			break;
		case REFILL:
			printf("Hold SPACE to refill the tanks\n");
			printf("Coffee:\t%d\n", mach->coffee);
			printf("Water:\t%d\n", mach->water);
			printf("Milk:\t%d\n", mach->milk);
			printf("ESC\tBack to main menu\n");
			break;
		case SET_POWER:
			printf("Press '-' and '+' (at left to backspace key) to set the coffee strength\n");
			printf("\t%d\n", mach->coffee_power);
			printf("ESC\tBack to main menu\n");
			break;
		case SET_SIZE:
			printf("Press '-' and '+' (at left to backspace key) to set the base drink size\n");
			printf("\t%d\n", mach->base_drink_size);
			printf("ESC\tBack to main menu\n");
			break;

	}
}

state makeCoffee(machine* mach) {
	int coffee_cost = 0,
		water_cost = 0,
		milk_cost = 0;
	switch (mach->CURRENT_STATE) {
		case MAKE_SMALL:
			coffee_cost = mach->base_drink_size * mach->coffee_power;
			water_cost = coffee_cost * 2;
			break;
		case MAKE_BIG:
			coffee_cost = mach->base_drink_size * mach->coffee_power * 2;
			water_cost = coffee_cost * 4;
			break;
		case MAKE_ESPRESSO:
			coffee_cost = (mach->base_drink_size * mach->coffee_power) / 2;
			water_cost = coffee_cost * 2;
			break;
		case MAKE_CAPUCCINO:
			coffee_cost = (mach->base_drink_size * mach->coffee_power);
			water_cost = coffee_cost * 2;
			milk_cost = coffee_cost;
			break;
		case MAKE_MILK:
			milk_cost = mach->base_drink_size * 2;
			break;
	}
	
	char key;
	if (mach->coffee - coffee_cost < 0 || mach->water - water_cost < 0) {
		if (mach->coffee - coffee_cost < 0) {
			printf("Not enough coffee\n");
		}
		if (mach->water - water_cost < 0) {
			printf("Not enough water\n");
		}
		if (mach->milk - milk_cost < 0) {
			printf("Not enough milk\n");
		}
		printf("SPACE\tRefill\n");
		printf("ESC\tChoose a different drink\n");
		while (key = _getch()) {
			switch (key) {
			case SPACE: return REFILL; break;
			case ESC: return DRINK_SELECT; break;
			default: break;
			}
		}
	}
	else {
		mach->coffee -= coffee_cost;
		mach->water -= water_cost;
		mach->milk -= milk_cost;
		if (mach->CURRENT_STATE != MAKE_MILK)
			printf("Enjoy your coffee!\n");
		else
			printf("Enjoy your milk!\n");
		printf("ESC\tMain menu\n");
		while (key = _getch()) {
			if (key == ESC) {
				return MAIN_MENU;
			}
		}
	}
}
