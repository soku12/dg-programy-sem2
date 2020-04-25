#include "file_operations.h"

int loadFileToBuffer(engine_t* engine, char* filename) {
	cleanBuffer(engine);
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		return 0;
	}

	int filesize = getFilesize(file);

	if (filesize > engine->iobufferSize) {
		realloc(engine->iobuffer, filesize * sizeof(char));
		memset(engine->iobuffer, 0, filesize * sizeof(char));
		engine->iobufferSize = filesize;
	}

	fread(engine->iobuffer, sizeof(char), filesize, file);
	fclose(file);

#ifdef _WIN32
	engine->iobufferWrittenSize = filesize - getBufferNewlineCount(engine, filesize);
#else
	engine->iobufferWrittenSize = filesize;
#endif

	return 1;
}




int saveBufferToFile(engine_t* engine, char* filename) {
	FILE* file = fopen(filename, "w");

	if (file == NULL) {
		printf("Error accessing file %s\n", filename);
		return 0;
	}

	fwrite(engine->iobuffer, sizeof(char), engine->iobufferWrittenSize, file);
	fclose(file);
	return 1;
}




int loadWordlist(engine_t* engine, char* filename) {
	if (loadFileToBuffer(engine, filename) == 0) {
		printf("Wordlist from file %s couldn't be loaded\n", filename);
		return 0;
	}
	if (engine->iobuffer[0] == '\n') {
		printf("Incorrect wordlist file format: %s\n", filename);
	}
	if (engine->iobuffer[engine->iobufferWrittenSize - 1] != '\n') {
		printf("Incorrect wordlist file format: %s\n", filename);
		return 0;
	}
	else if (engine->iobuffer[engine->iobufferWrittenSize - 2] == '\n') {
		printf("Incorrect wordlist file format: %s\n", filename);
		return 0;
	}

	//expanding the wordlist tab
	if (++(engine->wordlistCount) > engine->wordlistMemBlocks * 10) {
		realloc(engine->wordlistTab, ++(engine->wordlistMemBlocks) * 10 * sizeof(wordlist_t));
	}

	//allocating memory for the wordlist
	engine->wordlistTab[engine->wordlistCount - 1].wordlist = calloc(200, sizeof(word_t));

	//copying the filename and setting the flags to 0
	engine->wordlistTab[engine->wordlistCount - 1].filename = calloc(strlen(filename) + 1, sizeof(char));
	strcpy(engine->wordlistTab[engine->wordlistCount - 1].filename, filename);
	engine->wordlistTab[engine->wordlistCount - 1].modifiedFlag = 0;
	engine->wordlistTab[engine->wordlistCount - 1].unloadedFlag = 0;

	int word_mem_blocks = 1; //word_t memory blocks
	int word_iter = 0; 
	int string_mem_blocks = 1; 
	int string_iter = 0;
	int input_mode = 0; //0 - word, 1 - category

	engine->wordlistTab[engine->wordlistCount - 1].wordlist[0].word = calloc(200, sizeof(char));

	for (int i = 0; i < engine->iobufferSize; i++) { //for each character in the buffer
		if (word_iter > word_mem_blocks * 200) { //if out of memory for more words
			realloc(engine->wordlistTab[engine->wordlistCount - 1].wordlist, ++word_mem_blocks * 200 * sizeof(word_t));
		}
		if (string_iter > string_mem_blocks * 200) { //if out of memory for more letters
			if (input_mode == 0) {
				realloc(engine->wordlistTab[engine->wordlistCount - 1].wordlist[word_iter].word, ++string_mem_blocks * 200 * sizeof(char));
			}
			else if (input_mode == 1) {
				realloc(engine->wordlistTab[engine->wordlistCount - 1].wordlist[word_iter].category, ++string_mem_blocks * 200 * sizeof(char));
			}

		}

		if (engine->iobuffer[i] == TAB) { //end of word, start reading into category
			engine->wordlistTab[engine->wordlistCount - 1].wordlist[word_iter].word[string_iter] = '\0';
			engine->wordlistTab[engine->wordlistCount - 1].wordlist[word_iter].removedFlag = 0;
			string_iter = -1;
			input_mode = 1;
			string_mem_blocks = 1;
			engine->wordlistTab[engine->wordlistCount - 1].wordlist[word_iter].category = calloc(200, sizeof(char));
		}
		else if (engine->iobuffer[i] == '\n') { //end of category, start reading into a new word
			engine->wordlistTab[engine->wordlistCount - 1].wordlist[word_iter].category[string_iter] = '\0';
			word_iter++;
			string_iter = -1;
			input_mode = 0;
			string_mem_blocks = 1;
			engine->wordlistTab[engine->wordlistCount - 1].wordlist[word_iter].word = calloc(200, sizeof(char));
		}
		else if (input_mode == 0) { //read a char into the word
			engine->wordlistTab[engine->wordlistCount - 1].wordlist[word_iter].word[string_iter] = engine->iobuffer[i];
		}
		else if (input_mode == 1) { //read a char into the category
			engine->wordlistTab[engine->wordlistCount - 1].wordlist[word_iter].category[string_iter] = engine->iobuffer[i];
		}

		string_iter++;
	}

	engine->wordlistTab[engine->wordlistCount - 1].wordCount = word_iter;
	engine->wordlistTab[engine->wordlistCount - 1].initialWordCount = word_iter;
	engine->wordlistTab[engine->wordlistCount - 1].wordMemBlocks = word_mem_blocks;
	free(engine->wordlistTab[engine->wordlistCount - 1].wordlist[word_iter].word);
	
	return 1;
}




int wordlistToBuffer(wordlist_t* wordlist, engine_t* engine) {
	int charcounter = 0;
	for (int i = 0; i < wordlist->wordCount; i++) {
		if (wordlist->wordlist[i].removedFlag == 1) { //checking if the word has been removed
			continue;
		}
		for (int u = 0; u < strlen(wordlist->wordlist[i].word); u++) {
			if (++charcounter > engine->iobufferSize) {
				realloc(engine->iobuffer, engine->iobufferSize + 200);
				engine->iobufferSize += 200;
			}
			engine->iobuffer[charcounter - 1] = wordlist->wordlist[i].word[u];
		}
		if (++charcounter > engine->iobufferSize) { //safety buffer size check - ik its just one char but things tend to happen
			realloc(engine->iobuffer, engine->iobufferSize + 200);
			engine->iobufferSize += 200;
		}
		engine->iobuffer[charcounter - 1] = TAB;

		for (int u = 0; u < strlen(wordlist->wordlist[i].category); u++) {
			if (++charcounter > engine->iobufferSize) {
				realloc(engine->iobuffer, engine->iobufferSize + 200);
				engine->iobufferSize += 200;
			}
			engine->iobuffer[charcounter - 1] = wordlist->wordlist[i].category[u];
		}
		if (++charcounter > engine->iobufferSize) {
			realloc(engine->iobuffer, engine->iobufferSize + 200);
			engine->iobufferSize += 200;
		}
		engine->iobuffer[charcounter - 1] = '\n';
	}
	engine->iobufferWrittenSize = charcounter;
	return 1;
}




int saveWordlists(engine_t* engine) {
	for (int i = 0; i < engine->wordlistCount; i++) {
		if (engine->wordlistTab[i].modifiedFlag == 1) {
			wordlistToBuffer(&(engine->wordlistTab[i]), engine);
			if (saveBufferToFile(engine, engine->wordlistTab[i].filename) == 0) {
				printf("Wordlist %s could not been saved. Press any key\n", engine->wordlistTab[i].filename);
				_getch();
			}
			cleanBuffer(engine);
		}
	}
	return 1;
}




int loadStats(engine_t* engine) {
	FILE* file = fopen("stats", "rb");
	if (file == NULL) {
		return 0;
	}
	int* intbuffer = calloc(5, sizeof(int));
	
	fread(intbuffer, sizeof(int), 5, file);
	fclose(file);

	engine->stats.gamesPlayed = intbuffer[0];
	engine->stats.gamesWon = intbuffer[1];
	engine->stats.guessTries = intbuffer[2];
	engine->stats.accurateGuesses = intbuffer[3];
	engine->stats.playtime = intbuffer[4];
	
	free(intbuffer);

	return 1;
}




int saveStats(engine_t* engine) {
	FILE* file = fopen("stats", "wb");
	if (file == NULL) {
		return 0;
	}

	int* intbuffer = calloc(5, sizeof(int));

	intbuffer[0] = engine->stats.gamesPlayed;
	intbuffer[1] = engine->stats.gamesWon;
	intbuffer[2] = engine->stats.guessTries;
	intbuffer[3] = engine->stats.accurateGuesses;
	intbuffer[4] = engine->stats.playtime;

	fwrite(intbuffer, sizeof(int), 5, file);
	fclose(file);

	free(intbuffer);

	return 1;
}
