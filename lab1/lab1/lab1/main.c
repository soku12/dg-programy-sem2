#define _CRT_SECURE_NO_WARNINGS
#include "funkcje.h"

int main(int argn, char* args[]) {
	char pesel[12];
	char znak;

	while (1) {
		znak = 0;
		printf("pesel please\n");
		//receiving the pesel number from the input stream
		for (int i = 0; i < 11; i++) {
			scanf("%c", &znak);
			pesel[i] = znak;
		}
		printf("thank you\n");

		//checking if the provided number is correct
		if (check(pesel) == pesel[10]-'0') {
			printDateAndSex(pesel);
		}
		else {
			printf("the provided pesel number is incorrect\n");
		}
		printf("press esc to exit or any other button to enter another pesel\n");
		if (_getch() == 27) {
			return 0;
		}
		//a function to clear the input buffer i found on stackoverflow; i have no idea how it works but it works
		fseek(stdin, 0, SEEK_END);
	}
}