#ifndef STRUCT_H
#define STRUCT_H

enum state {OFF, MAIN_MENU, DRINK_SELECT, REFILL, SET_POWER, SET_SIZE, MAKE_SMALL, MAKE_BIG, MAKE_ESPRESSO, MAKE_CAPUCCINO, MAKE_MILK, STATE_COUNT, EXIT};

struct machine {
	enum state CURRENT_STATE;
	int coffee,
		water,
		milk,
		coffee_power,
		base_drink_size;
	int* iobuffer;
	enum state(*func_tab[STATE_COUNT])(struct machine*);
};

typedef enum state state;
typedef struct machine machine;

#endif