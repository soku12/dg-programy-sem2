#include "func.h"


int compID(const void* p1, const void* p2) {
	return ((DaneOsobowe*)p1)->id - ((DaneOsobowe*)p2)->id;
}

int compAB(const void* p1, const void* p2) {
	return strcmp(((DaneOsobowe*)p1)->imie, ((DaneOsobowe*)p2)->imie);
}

void sortnPrint(DaneOsobowe* tab, int tabsize) {
	
	//sorting by ID
	qsort((void*)tab, tabsize, sizeof(DaneOsobowe), compID);
	
	//printing the sorted array
	printf("sorted by ID:\n");
	for (int i = 0; i < tabsize; i++) {
		printf("%i \t %s \n",tab[i].id, tab[i].imie);
	}
	
	//sorting alphabetically
	qsort((void*)tab, tabsize, sizeof(DaneOsobowe), compAB);

	//printing the sorted array
	printf("sorted by name:\n");
	for (int i = 0; i < tabsize; i++) {
		printf("%i \t %s \n",tab[i].id, tab[i].imie);
	}
}
