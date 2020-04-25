#include "assisting_functions.h"


char* getstring() {
	char* output = calloc(200, sizeof(char));
	char c = getchar();
	int i = 1, blocks = 1;
	while (c != '\n') {
		if (i % 200 == 0) {
			output = realloc(output, (++blocks)*(200 * sizeof(char)));
		}
		output[i - 1] = c;
		c = getchar();

		i++;
	}
	output[i - 1] = '\0';

	return output;
}




int getFilesize(FILE* file) {
	fseek(file, 0, SEEK_END);
	int filesize = ftell(file);
	rewind(file);
	return filesize;
}




int isLetterPresent(char letter, char* tab, int tab_size) {
	for (int i = 0; i < tab_size; i++) {
		if (tab[i] == letter) {
			return 1;
		}
	}
	return 0;
}




int uniqueLetterCount(char* word) {
	char countedLetters[26]; //there are only 26 possible letters
	memset(countedLetters, 0, 26); //cleaning the table to prevent accidents
	int counter = 0;
	for (int i = 0; i < strlen(word); i++) { //for every char in the word
		if (word[i] == SPACE || word[i] == MINUS || word[i] == APOSTR || word[i] == COMMA || word[i] == AMP) {
			continue;
		}
		else if (isLetterPresent(word[i], countedLetters, i) == 1) { //if the letter has already been counted
			continue; //neeext
		}
		else {
			countedLetters[counter++] = word[i];
		}
	}
	return counter;
}




int findWord(wordlist_t* wordlist, char* word) {
	int word_number = -1;
	for (int i = 0; i < wordlist->wordCount && word_number == -1; i++) {
		if (strcmp(word, wordlist->wordlist[i].word) == 0) {
			word_number = i;
		}
	}
	return word_number;
}




void cleanBuffer(engine_t* engine) {
	memset(engine->iobuffer, 0, engine->iobufferSize);
	engine->iobufferWrittenSize = 0;
}




void cleanMemory(engine_t* engine) {
	for (int i = 0; i < engine->wordlistCount; i++) {
		for (int u = 0; u < engine->wordlistTab[i].initialWordCount; u++) {
			free(engine->wordlistTab[i].wordlist[u].word);
			free(engine->wordlistTab[i].wordlist[u].category);
		}
		free(engine->wordlistTab[i].filename);
		free(engine->wordlistTab[i].wordlist);
	}
	free(engine->wordlistTab);
	free(engine->iobuffer);
}




int getBufferNewlineCount(engine_t* engine, int size) {
	int counter = 0;
	for (int i = 0; i < size; i++) {
		if (engine->iobuffer[i] == '\n') {
			counter++;
		}
	}
	return counter;
}