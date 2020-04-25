#include "func.h"


int main(int argn, char* args[]) {
	int tabsize = 0;

	printf("enter the array size\n");
	scanf("%i", &tabsize);
	fseek(stdin, 0, SEEK_END); //flushing the input buffer
	printf("enter %i names\n", tabsize);

	//creating the dynamic array of structures
	DaneOsobowe* tab = (DaneOsobowe*)malloc(sizeof(DaneOsobowe)*tabsize);

	for (int i = 0; i < tabsize; i++) {
		
		//string input with dynamic memory allocation
		char* buffer = (char*)malloc(sizeof(char));
		char c = getchar();
		int iter = 1;
		while (c != '\n') {
			buffer = realloc(buffer, (iter+1) * sizeof(char));
			buffer[iter - 1] = c;
			c = getchar();
			iter++;
		}
		buffer[iter-1] = '\0'; //putting an 'end of string' character to cut the garbage at the end
		tab[i].imie = buffer;
		tab[i].id = i;
	}

	//sorting and printing
	sortnPrint(tab, tabsize);

	printf("\npress any key");
	_getch();

	//cleaning the memory
	for (int i = 0; i < tabsize; i++) {
		free(tab[i].imie);
	}
	free(tab);
	_CrtDumpMemoryLeaks();
	return 0;
}