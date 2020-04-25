#ifndef STRUCT_H
#define STRUCT_H

#include "main.h"

enum engine_state{engine_MAIN, engine_PLAY, engine_STATS, engine_EDITOR, engine_MANAGER, engine_PRE_EXIT, engine_EXIT, engine_STATE_COUNT};
enum editor_state{editor_MAIN, editor_FILE_SELECT, editor_ADD, editor_REMOVE, editor_EXIT, editor_STATE_COUNT};
enum manager_state{manager_MAIN, manager_FILE_SELECT, manager_PREVIEW, manager_LOAD, manager_UNLOAD, manager_RELOAD, manager_EXIT, manager_STATE_COUNT};
enum game_state{game_INIT, game_MAIN, game_LETTER_PICK, game_WORD_GUESS, game_EXIT_PROMPT, game_WIN, game_LOSE, game_EXIT, game_STATE_COUNT};




struct word_t {
	char* word;
	char* category;
	int uniqueLetterCount;
	int removedFlag;
};




struct wordlist_t {
	char* filename;
	struct word_t* wordlist;
	int wordCount;

	/**	Increased when adding, NOT decreased when removed */
	int initialWordCount;

	/** The size of the word_t table in blocks (1 block = 200 words) */
	int wordMemBlocks;
	int modifiedFlag;
	int unloadedFlag;
};




struct stats_t {
	int gamesPlayed;
	int gamesWon;
	int guessTries;
	int accurateGuesses;
	int playtime;
};




struct game_t {
	enum game_state current_state;
	enum game_state(*func_tab[game_STATE_COUNT])(struct game_t*);

	/**	Pointer to the main UI engine, useful for many reasons (eg. no need for data copying) */
	struct engine_t* engine_ptr;
	
	/**	Pointer to the wordlist from which the currently chosen word originates */
	struct wordlist_t* wordlist;
	struct word_t* word;
	
	/**	Contains all the incorrect tried letters 
		Limited to 10 because thats the maximum possible failures before the game is lost
	*/
	char incorrectLetters[10];
	int triesLeft;

	/**	Contains all the correct tried letters.
		Limited to 26 because of the size of the English alphabet
	*/
	char guessedLetters[26];
	int guessedLettersCount;

	int gameWon;
	/** Is set to 1 when the initialisation fails */
	int errorFlag;
	
	clock_t time_start;
	clock_t time_end;

};




struct editor_t {
	enum editor_state current_state;
	enum editor_state(*func_tab[editor_STATE_COUNT])(struct editor_t*);

	/**	Pointer to the main UI engine, useful for many reasons (eg. no need for data copying) */
	struct engine_t* engine_ptr;

	enum editor_state selected_action;
	struct wordlist_t* selected_wordlist;

};




struct manager_t {
	enum manager_state current_state;
	enum manager_state(*func_tab[manager_STATE_COUNT])(struct manager_t*);

	/**	Pointer to the main UI engine, useful for many reasons (eg. no need for data copying) */
	struct engine_t* engine_ptr;

	/**	The number of the selected wordlist in the wordlist tab */
	int selected_wordlist_number;

	enum manager_state selected_action;

	char* filename;

};




struct engine_t {
	enum engine_state current_state;
	enum engine_state(*func_tab[engine_STATE_COUNT])(struct engine_t*);

	struct wordlist_t* wordlistTab;
	int wordlistCount;
	/**	The size of the wordlist tab in blocks (1 block = 10 wordlists) */
	int wordlistMemBlocks;

	unsigned char* iobuffer;
	/**	The total size of the buffer */
	int iobufferSize;
	/**	The size of the part of the buffer containing valid data */
	int iobufferWrittenSize;

	struct editor_t editordata;
	struct manager_t managerdata;
	struct game_t gamedata;

	struct stats_t stats;
};




typedef enum engine_state engine_state;
typedef enum editor_state editor_state;
typedef enum game_state game_state;
typedef enum manager_state manager_state;
typedef struct word_t word_t;
typedef struct wordlist_t wordlist_t;
typedef struct stats_t stats_t;
typedef struct game_t game_t;
typedef struct editor_t editor_t;
typedef struct engine_t engine_t;
typedef struct manager_t manager_t;

#endif
