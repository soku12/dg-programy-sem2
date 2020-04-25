#include "funkcje.h"

int check(char pesel[]) {
	int work[11];
	int sum = 0;
	
	//copying the pesel into an int table for processing
	for (int i = 0; i < 11; i++) {
		work[i] = pesel[i]-'0';
	}
	
	//multiplying the digits by their corresponding weights
	work[1] = work[1] * 3;
	work[2] = work[2] * 7;
	work[3] = work[3] * 9;
	work[5] = work[5] * 3;
	work[6] = work[6] * 7;
	work[7] = work[7] * 9;
	work[9] = work[9] * 3;

	//summing the last digits of the multiplication results
	for (int i = 0; i < 10; i++) {
		sum += (work[i] % 10);
	}
	//returning the calculated control number
	return 10 - (sum % 10);
}

void printDateAndSex(char pesel[]) {
	int year = 0,
		month = 0,
		day = 0;

	//the day and the last 2 digits of the year are straight-forward
	year = ((pesel[0]-'0') * 10) + (pesel[1]-'0');
	day = ((pesel[4]-'0') * 10) + (pesel[5]-'0');

	//the first 2 digits of the year depend on the month
	switch (pesel[2]-'0') {
		case 0: year += 1900; month = pesel[3]-'0'; break;
		case 1: year += 1900; month = 10 + pesel[3]-'0'; break;
		case 2: year += 2000; month = pesel[3]-'0'; break;
		case 3: year += 2000; month = 10 + pesel[3]-'0'; break;
		case 4: year += 2100; month = pesel[3]-'0'; break;
		case 5: year += 2100; month = 10 + pesel[3]-'0'; break;
		case 6: year += 2200; month = pesel[3]-'0'; break;
		case 7: year += 2200; month = 10 + pesel[3]-'0'; break;
		case 8: year += 1800; month = pesel[3]-'0'; break;
		case 9: year += 1800; month = 10 + pesel[3]-'0'; break;
	}

	//odd digit - male, even digit - female
	if ((pesel[9]-'0') % 2 == 1) {
		printf("the person is a male, born ");
	}
	else {
		printf("the person is a female, born ");
	}
	
	printf("%i%c%i%c%i \n", day, '.', month, '.', year);

}