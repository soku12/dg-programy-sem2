#include "initialisers.h"


editor_t editorInit() {
	editor_t editor;

	editor.current_state = editor_MAIN;

	editor.func_tab[0] = run_editor_MAIN;
	editor.func_tab[1] = run_editor_FILE_SELECT;
	editor.func_tab[2] = run_editor_ADD;
	editor.func_tab[3] = run_editor_REMOVE;
	editor.func_tab[4] = run_editor_EXIT;

	return editor;
}




game_t gameInit() {
	game_t game;

	game.current_state = game_INIT;
	game.errorFlag = 0;

	game.func_tab[0] = run_game_INIT;
	game.func_tab[1] = run_game_MAIN;
	game.func_tab[2] = run_game_LETTER_PICK;
	game.func_tab[3] = run_game_WORD_GUESS;
	game.func_tab[4] = run_game_EXIT_PROMPT;
	game.func_tab[5] = run_game_WIN;
	game.func_tab[6] = run_game_LOSE;
	game.func_tab[7] = run_game_EXIT;

	return game;
}



manager_t managerInit() {
	manager_t manager;

	manager.current_state = manager_MAIN;

	manager.filename = calloc(200, sizeof(char));

	manager.func_tab[0] = run_manager_MAIN;
	manager.func_tab[1] = run_manager_FILE_SELECT;
	manager.func_tab[2] = run_manager_PREVIEW;
	manager.func_tab[3] = run_manager_LOAD;
	manager.func_tab[4] = run_manager_UNLOAD;
	manager.func_tab[5] = run_manager_RELOAD;
	manager.func_tab[6] = run_manager_EXIT;

	return manager;
}




stats_t statsInit() {
	stats_t stats;

	stats.accurateGuesses = 0;
	stats.gamesPlayed = 0;
	stats.gamesWon = 0;
	stats.guessTries = 0;
	stats.playtime = 0;

	return stats;
}




engine_t engineInit() {
	engine_t engine;
	
	engine.current_state = engine_MAIN;

	engine.stats = statsInit();

	engine.iobuffer = calloc(200, sizeof(char));
	engine.iobufferSize = 200;
	engine.iobufferWrittenSize = 0;

	engine.wordlistTab = calloc(10, sizeof(wordlist_t));
	engine.wordlistCount = 0;
	engine.wordlistMemBlocks = 1;

	engine.editordata = editorInit();
	engine.managerdata = managerInit();
	engine.gamedata = gameInit();

	engine.func_tab[0] = run_engine_MAIN;
	engine.func_tab[1] = run_engine_PLAY;
	engine.func_tab[2] = run_engine_STATS;
	engine.func_tab[3] = run_engine_EDITOR;
	engine.func_tab[4] = run_engine_MANAGER;;
	engine.func_tab[5] = run_engine_PRE_EXIT;
	engine.func_tab[6] = run_engine_EXIT;

	return engine;
}