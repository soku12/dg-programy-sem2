#include "manager.h"


manager_state run_manager_MAIN(manager_t* manager) {
	system("cls");
	printf("WORDLIST MANAGER\n");
	printf("Loaded wordlists:\n");
	if (manager->engine_ptr->wordlistCount != 0) {
		for (int i = 0; i < manager->engine_ptr->wordlistCount; i++) {
			if (manager->engine_ptr->wordlistTab[i].unloadedFlag == 0) {
				printf("%s  ", manager->engine_ptr->wordlistTab[i].filename);
			}
		}
	}
	printf("\n1\tPreview the contents of a wordlist\n");
	printf("2\tLoad a wordlist from file\n");
	printf("3\tUnload a loaded wordlist\n");
	printf("4\tReload wordlists (applies all the changes from the editor to the files)\n");
	printf("ESC\tMain menu\n");

	char key;
	while (key = _getch()) {
		switch (key) {
		case KEY_1: manager->selected_action = manager_PREVIEW; return manager_FILE_SELECT; break;
		case KEY_2: manager->selected_action = manager_LOAD; return manager_FILE_SELECT; break;
		case KEY_3: manager->selected_action = manager_UNLOAD; return manager_FILE_SELECT; break;
		case KEY_4: return manager_RELOAD; break;
		case ESC: return manager_EXIT; break;
		default: break;
		}
	}
}




manager_state run_manager_FILE_SELECT(manager_t* manager) {
	char key;
	system("cls");
	printf("WORDLIST MANAGER -> ");
	switch (manager->selected_action) {
		case manager_PREVIEW: printf("Preview -> "); break;
		case manager_LOAD: printf("Load -> "); break;
		case manager_UNLOAD: printf("Unload -> "); break;
		default: break;
	}
	printf("File selection\n");
	printf("Loaded wordlists:\n");
	for (int i = 0; i < manager->engine_ptr->wordlistCount; i++) {
		if (manager->engine_ptr->wordlistTab[i].unloadedFlag == 0) {
			printf("%s  ", manager->engine_ptr->wordlistTab[i].filename);
		}
	}
	printf("\nType in the name of the wordlist (with extension)\n");
	char* filename = getstring();
	int wordlist_number = -1;
	for (int i = 0; i < manager->engine_ptr->wordlistCount && wordlist_number == -1; i++) {
		if (strcmp(filename, manager->engine_ptr->wordlistTab[i].filename) == 0) {
			wordlist_number = i;
		}
	}
	manager->selected_wordlist_number = wordlist_number;
	strcpy(manager->filename, filename);
	free(filename);
	return manager->selected_action;
}




manager_state run_manager_PREVIEW(manager_t* manager) {
	char key;
	if (manager->selected_wordlist_number == -1) {
		printf("Selected wordlist has not been loaded\n");
		printf("1\tTry a different wordlist\n");
		printf("ESC\tCancel\n");
		while (key = _getch()) {
			switch (key) {
			case KEY_1: return manager_FILE_SELECT; break;
			case ESC: return manager_MAIN; break;
			default: break;
			}
		}
	}
	else {
		system("cls");
		printf("WORDLIST MANAGER -> Preview\n");
		printf("ESC\tBack\n\n");
		printf("Wordlist: %s\n", manager->engine_ptr->wordlistTab[manager->selected_wordlist_number].filename);
		printf("WORD\tCATEGORY\n");
		for (int i = 0; i < manager->engine_ptr->wordlistTab[manager->selected_wordlist_number].wordCount; i++) {
			printf("%s\t%s", manager->engine_ptr->wordlistTab[manager->selected_wordlist_number].wordlist[i].word, manager->engine_ptr->wordlistTab[manager->selected_wordlist_number].wordlist[i].category);
			if (manager->engine_ptr->wordlistTab[manager->selected_wordlist_number].wordlist[i].removedFlag == 1) {
				printf("\t[deleted]");
			}
			printf("\n");
		}
		while (key = _getch()) {
			if (key == ESC) {
				return manager_MAIN;
			}
		}
	}
}




manager_state run_manager_LOAD(manager_t* manager) {
	char key;
	if (manager->selected_wordlist_number != -1) {
		printf("This wordlist has already been loaded\n");
		printf("1\tTry a different wordlist\n");
		printf("ESC\tCancel\n");
		while (key = _getch()) {
			switch (key) {
				case KEY_1: return manager_FILE_SELECT; break;
				case ESC: return manager_MAIN; break;
				default: break;
			}
		}
	}
	else if (loadWordlist(manager->engine_ptr, manager->filename) == 0) {
		printf("1\tTry a different wordlist\n");
		printf("ESC\tCancel\n");
		while (key = _getch()) {
			switch (key) {
			case KEY_1: return manager_FILE_SELECT; break;
			case ESC: return manager_MAIN; break;
			default: break;
			}
		}
	}
	else {
		printf("Worldist loaded succesfully. Press any key\n");
		_getch();
		return manager_MAIN;
	}
}




manager_state run_manager_UNLOAD(manager_t* manager) {
	char key;
	if (manager->selected_wordlist_number == -1) {
		printf("This wordlist has not been loaded\n");
		printf("1\tTry a different wordlist\n");
		printf("ESC\tCancel\n");
		while (key = _getch()) {
			switch (key) {
			case KEY_1: return manager_FILE_SELECT; break;
			case ESC: return manager_MAIN; break;
			default: break;
			}
		}
	}
	else {
		manager->engine_ptr->wordlistTab[manager->selected_wordlist_number].unloadedFlag = 1;
		printf("Wordlist unloaded succesfully. Press any key\n");
		_getch();
		return manager_MAIN;
	}
}




manager_state run_manager_RELOAD(manager_t* manager) {
	
	//creating a list of all not-unloaded wordlists
	char** filenameList = calloc(200, sizeof(char*));
	int filenameListMemBlocks = 1;
	int filenameList_count = 0;

	for (int i = 0; i < manager->engine_ptr->wordlistCount; i++) {
		if (manager->engine_ptr->wordlistTab[i].unloadedFlag == 1) {
			continue;
		}
		if (++filenameList_count > filenameListMemBlocks * 200) {
			realloc(filenameList, ++filenameListMemBlocks * 200 * sizeof(char*));
		}
		filenameList[filenameList_count - 1] = calloc(strlen(manager->engine_ptr->wordlistTab[i].filename) + 1, sizeof(char));
		strcpy(filenameList[filenameList_count-1], manager->engine_ptr->wordlistTab[i].filename);
	}

	//saving all the eventual changes in the wordlists
	saveWordlists(manager->engine_ptr);

	//cleaning the old wordlist tab and creating a new one
	cleanMemory(manager->engine_ptr);
	manager->engine_ptr->wordlistCount = 0;
	manager->engine_ptr->wordlistMemBlocks = 1;
	manager->engine_ptr->wordlistTab = calloc(10, sizeof(wordlist_t));
	manager->engine_ptr->iobuffer = calloc(200, sizeof(char));
	manager->engine_ptr->iobufferSize = 200;
	manager->engine_ptr->iobufferWrittenSize = 0;

	for (int i = 0; i < filenameList_count; i++) {
		loadWordlist(manager->engine_ptr, filenameList[i]);
	}
	
	printf("Wordlists have been reloaded\nPress any key\n");
	_getch();
	for (int i = 0; i < filenameList_count; i++) {
		free(filenameList[i]);
	}
	free(filenameList);
	return manager_MAIN;
}




manager_state run_manager_EXIT(manager_t* manager) {
	return manager_EXIT;
}




manager_state manager_runstate(manager_state wanted_state, manager_t* manager) {
	return manager->func_tab[wanted_state](manager);
}