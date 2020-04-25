#include "editor.h"

editor_state run_editor_MAIN(editor_t* editor) {
	system("cls");
	printf("EDITOR\n");
	printf("1\tAdd a word to a wordlist\n");
	printf("2\tRemove a word from a wordlist\n");
	printf("ESC\tMain menu\n");

	char key;
	while (key = _getch()) {
		switch (key) {
			case KEY_1: editor->selected_action = editor_ADD; return editor_FILE_SELECT; break;
			case KEY_2: editor->selected_action = editor_REMOVE; return editor_FILE_SELECT; break;
			case ESC: return editor_EXIT; break;
			default: break;
		}
	}
}




editor_state run_editor_FILE_SELECT(editor_t* editor) {
	char key;
	system("cls");
	printf("EDITOR -> File selection\n");
	printf("Loaded wordlists: ");
	for (int i = 0; i < editor->engine_ptr->wordlistCount; i++) {
		if (editor->engine_ptr->wordlistTab[i].unloadedFlag == 0) {
			printf("%s  ", editor->engine_ptr->wordlistTab[i].filename);
		}
	}
	printf("\nEnter the name of the wordlist to edit\n");
	char* filename = getstring();

	int wordlist_number = -1;
	for (int i = 0; i < editor->engine_ptr->wordlistCount; i++) {
		if (strcmp(filename, editor->engine_ptr->wordlistTab[i].filename) == 0) {
			wordlist_number = i;
		}
	}
	if (wordlist_number == -1) {
		printf("Wordlist %s has not been loaded\n", filename);
		printf("1\tTry a different wordlist\n");
		printf("ESC\tBack to main menu\n");
		free(filename);
		while (key = _getch()) {
			switch (key) {
			case KEY_1: return editor_FILE_SELECT; break;
			case ESC: return editor_MAIN; break;
			default: break;
			}
		}
	}
	else {
		free(filename);
		editor->selected_wordlist = &(editor->engine_ptr->wordlistTab[wordlist_number]);
	}
	return editor->selected_action;
}




editor_state run_editor_ADD(editor_t* editor) {
	char key;
	system("cls");
	printf("EDITOR -> Add\n");
	printf("Wordlist: %s\n", editor->selected_wordlist->filename);
	printf("Type a word to add\n");
	char* word = getstring();

	if (findWord(editor->selected_wordlist, word) > -1) {
		printf("Word %s already exists in this wordlist\n", word);
		printf("1\tTry a different word\n");
		printf("ESC\tCancel\n");
		free(word);
		
		while (key = _getch()) {
			switch (key) {
				case KEY_1: return editor_ADD; break;
				case ESC: return editor_MAIN; break;
				default: break;
			}
		}
	}
	else {
		if (editor->selected_wordlist->wordCount + 1 > editor->selected_wordlist->wordMemBlocks * 200) {
			realloc(editor->selected_wordlist, (++editor->selected_wordlist->wordMemBlocks) * 200 * sizeof(word_t));
		}
		editor->selected_wordlist->wordlist[editor->selected_wordlist->wordCount].word = calloc(strlen(word) + 1, sizeof(char));
		strcpy(editor->selected_wordlist->wordlist[editor->selected_wordlist->wordCount].word, word);
		editor->selected_wordlist->wordlist[editor->selected_wordlist->wordCount].removedFlag = 0;

		printf("Type the category of the word\n");
		editor->selected_wordlist->wordlist[editor->selected_wordlist->wordCount].category = getstring();
		editor->selected_wordlist->wordCount++;
		editor->selected_wordlist->initialWordCount++;
		editor->selected_wordlist->modifiedFlag = 1;
		free(word);
		printf("Word added successfully\n");
		printf("1\tAdd another word to this wordlist\n");
		printf("ESC\tBack\n");
		while (key = _getch()) {
			switch (key) {
				case KEY_1: return editor_ADD; break;
				case ESC: return editor_MAIN; break;
				default: break;
			}
		}
	}
}




editor_state run_editor_REMOVE(editor_t* editor) {
	char key;
	system("cls");
	printf("EDITOR -> Remove\n");
	printf("Wordlist: %s\n", editor->selected_wordlist->filename);
	printf("Type a word to remove\n");
	char* word = getstring();
	int word_number = findWord(editor->selected_wordlist, word);
	if (word_number < 0) {
		printf("Word %s could not be found in this wordlist\n", word);
		printf("1\tTry a different word\n");
		printf("ESC\tCancel\n");
		free(word);

		while (key = _getch()) {
			switch (key) {
				case KEY_1: return editor_REMOVE; break;
				case ESC: return editor_MAIN; break;
				default: break;
			}
		}
	}
	else {
		free(word);
		editor->selected_wordlist->modifiedFlag = 1;
		editor->selected_wordlist->wordlist[word_number].removedFlag = 1;
		printf("Word removed successfully\n");
		printf("1\tRemove another word from this wordlist\n");
		printf("ESC\tBack\n");
		while (key = _getch()) {
			switch (key) {
			case KEY_1: return editor_REMOVE; break;
			case ESC: return editor_MAIN; break;
			default: break;
			}
		}
	}
}

editor_state run_editor_EXIT(editor_t* editor) {
	return editor_EXIT;
}

editor_state editor_runstate(editor_state wanted_state, editor_t* editor) {
	return editor->func_tab[wanted_state](editor);
}