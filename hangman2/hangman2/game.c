#include "game.h"


game_state run_game_INIT(game_t* game) {
	if (game->engine_ptr->wordlistCount < 1) {
		printf("No wordlists loaded! Press any key");
		_getch();
		game->errorFlag = 1;
		return game_EXIT;
	}

	int valid_wordlists = 0;
	for (int i = 0; i < game->engine_ptr->wordlistCount; i++) {
		if (game->engine_ptr->wordlistTab[i].wordCount > 0 && game->engine_ptr->wordlistTab[i].unloadedFlag != 1) {
			valid_wordlists++;
		}
	}
	if (valid_wordlists < 1) {
		printf("All loaded worldlists are empty or unloaded! Press any key");
		_getch();
		game->errorFlag = 1;
		return game_EXIT;
	}
	
	int wordlist_number = rand() % game->engine_ptr->wordlistCount;
	//if the wordlist was unloaded roll until you find a not unloaded one
	while (game->engine_ptr->wordlistTab[wordlist_number].unloadedFlag == 1 || game->engine_ptr->wordlistTab[wordlist_number].wordCount < 1) {
		wordlist_number = rand() % game->engine_ptr->wordlistCount;
	}
	int word_number = rand() % game->engine_ptr->wordlistTab[wordlist_number].wordCount;
	//if the word was deleted roll until you find a not deleted one
	while (game->engine_ptr->wordlistTab[wordlist_number].wordlist[word_number].removedFlag == 1) {
		word_number = rand() % game->engine_ptr->wordlistTab[wordlist_number].wordCount;
	}

	game->wordlist = &(game->engine_ptr->wordlistTab[wordlist_number]);
	game->word = &(game->engine_ptr->wordlistTab[wordlist_number].wordlist[word_number]);
	game->word->uniqueLetterCount = uniqueLetterCount(game->word->word);

	memset(game->incorrectLetters, 0, 10);
	memset(game->incorrectLetters, 0, 26);
	game->triesLeft = 10;
	game->guessedLettersCount = 0;

	game->gameWon = 0;

	game->time_start = clock();

	return game_MAIN;

}

game_state run_game_MAIN(game_t* game) {
	system("cls");
	printf("Wordlist: %s\n\n", game->wordlist->filename);
	for (int i = 0; i < strlen(game->word->word); i++) {
		if (game->word->word[i] == SPACE || game->word->word[i] == MINUS || game->word->word[i] == APOSTR || game->word->word[i] == COMMA || game->word->word[i] == AMP) {
			printf("%c ", game->word->word[i]);
		}
		else if (isLetterPresent(game->word->word[i], game->guessedLetters, game->guessedLettersCount)) {
			printf("%c ", game->word->word[i] - SPACE);
		}
		else {
			printf("_ ");
		}
	}
	printf("\n\nCategory: %s\n", game->word->category);
	printf("Tries left: %i\n", game->triesLeft);
	printf("Incorrect letters: ");
	for (int i = 0; i < (10 - game->triesLeft); i++) {
		printf("%c, ", game->incorrectLetters[i]);
	}
	printf("\n\n1\tPick a letter\n");
	printf("2\tGuess the word\n");
	printf("ESC\tQuit\n");

	char key;
	while (key = _getch()) {
		switch (key) {
			case KEY_1: return game_LETTER_PICK; break;
			case KEY_2: return game_WORD_GUESS; break;
			case ESC: return game_EXIT_PROMPT; break;
			default: break;
		}
	}
}

game_state run_game_LETTER_PICK(game_t* game) {
	printf("Press a letter (or ESC to cancel)");

	char letter = _getch();
	while (letter < 'a' || letter > 'z' || isLetterPresent(letter, game->incorrectLetters, 10) == 1 || isLetterPresent(letter, game->guessedLetters, game->guessedLettersCount) == 1){
		if (letter == ESC) {
			return game_MAIN;
		}
		letter = _getch();
	}
	if (isLetterPresent(letter, game->word->word, strlen(game->word->word)) == 1) {
		game->guessedLetters[game->guessedLettersCount++] = letter;
		if (game->guessedLettersCount >= game->word->uniqueLetterCount) {
			return game_WIN;
		}
	}
	else {
		if (game->triesLeft == 1) {
			game->triesLeft--;
			return game_LOSE;
		}
		else {
			game->incorrectLetters[10 - (game->triesLeft--)] = letter;
		}
	}
	return game_MAIN;
}

game_state run_game_WORD_GUESS(game_t* game) {
	printf("Try guessing the word!\n");

	char* attempt = getstring();
	if (strcmp(attempt, game->word->word) == 0) {
		free(attempt);
		return game_WIN;
	}
	else {
		if (game->triesLeft == 1) {
			game->triesLeft--;
			free(attempt);
			return game_LOSE;
		}
		else {
			game->triesLeft--;
			free(attempt);
			return game_MAIN;
		}
	}
}

game_state run_game_EXIT_PROMPT(game_t* game) {
	system("cls");
	printf("Quitting the game is equal to losing.\nAre you sure?\n");
	printf("ENTER\tYES\n");
	printf("ESC\tNO\n");

	char key;
	while (key = _getch()) {
		switch (key) {
			case ENTER: 
				game->time_end = clock();
				return game_EXIT; 
				break;
			case ESC: return game_MAIN; break;
			default: break;
		}
	}
}

game_state run_game_WIN(game_t* game) {
	game->gameWon = 1;
	game->time_end = clock();
	
	system("cls");
	printf("VICTORY!\n");
	printf("The word was: %s\n", game->word->word);
	printf("Press any key");

	_getch();
	return game_EXIT;
}

game_state run_game_LOSE(game_t* game) {
	game->time_end = clock();
	
	system("cls");
	printf("DEFEAT!\n");
	printf("The word was: %s\n", game->word->word);
	printf("Press any key");

	_getch();
	return game_EXIT;
}

game_state run_game_EXIT(game_t* game) {
	return game_EXIT;
}

game_state game_runstate(game_state wanted_state, game_t* game) {
	return game->func_tab[wanted_state](game);
}

void updateStats(engine_t* engine) {
	if (engine->gamedata.errorFlag == 0) {
		engine->stats.accurateGuesses += engine->gamedata.guessedLettersCount;
		engine->stats.guessTries += engine->gamedata.guessedLettersCount + (10 - engine->gamedata.triesLeft);
		engine->stats.gamesPlayed++;
		engine->stats.gamesWon += engine->gamedata.gameWon;
		engine->stats.playtime += (engine->gamedata.time_end - engine->gamedata.time_start)/CLOCKS_PER_SEC;
	}
}

