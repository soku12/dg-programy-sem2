#include "engine.h"

engine_state run_engine_MAIN(engine_t* engine) {
	system("cls");
	printf("HANGMAN (build ");
	printf(__DATE__);
	printf(" ");
	printf(__TIME__);
	printf(")\n");
	printf("1\tPlay\n");
	printf("2\tStats\n");
	printf("3\tEditor\n");
	printf("4\tWordlist manager\n");
	printf("ESC\tExit\n");

	char key;
	while (key = _getch()) {
		switch (key) {
			case KEY_1: return engine_PLAY; break;
			case KEY_2: return engine_STATS; break;
			case KEY_3: return engine_EDITOR; break;
			case KEY_4: return engine_MANAGER; break;
			case ESC: return engine_PRE_EXIT; break;
			default: break;
		}
	}
}




engine_state run_engine_PLAY(engine_t* engine) {
	while (engine->gamedata.current_state != game_EXIT) {
		engine->gamedata.current_state = game_runstate(engine->gamedata.current_state, &(engine->gamedata));
	}
	updateStats(engine);
	engine->gamedata.current_state = game_INIT;
	engine->gamedata.errorFlag = 0;
	return engine_MAIN;
}




engine_state run_engine_STATS(engine_t* engine) {
	float winratio = (engine->stats.gamesWon / (engine->stats.gamesPlayed + 0.00001)) * 100;
	float accuracy = (engine->stats.accurateGuesses / (engine->stats.guessTries + 0.00001)) * 100;
	
	int time_hours, time_mins, time_secs, remaining_secs;

	time_hours = engine->stats.playtime / 3600;
	remaining_secs = engine->stats.playtime - (time_hours * 3600);
	time_mins = remaining_secs / 60;
	remaining_secs = engine->stats.playtime - (time_mins * 60);
	time_secs = remaining_secs;

	system("cls");
	printf("STATS\n");
	printf("Games played:\t%i\n", engine->stats.gamesPlayed);
	printf("Games won:\t%i\n", engine->stats.gamesWon);
	printf("Games won percentage:\t%.2f%%\n\n", winratio);
	printf("Letter guesses:\t%i\n", engine->stats.guessTries);
	printf("Accurate guesses:\t%i\n", engine->stats.accurateGuesses);
	printf("Accuracy :\t%.2f%%\n\n", accuracy);
	printf("Total playtime:\t%ih %im %is\n\n", time_hours, time_mins, time_secs);
	printf("ESC\t Main menu");

	char key;
	while (key = _getch()) {
		if (key == ESC) {
			return engine_MAIN;
		}
	}
}




engine_state run_engine_EDITOR(engine_t* engine) {
	while (engine->editordata.current_state != editor_EXIT) {
		engine->editordata.current_state = editor_runstate(engine->editordata.current_state, &(engine->editordata));
	}
	engine->editordata.current_state = editor_MAIN;
	return engine_MAIN;
}




engine_state run_engine_MANAGER(engine_t* engine) {
	while (engine->managerdata.current_state != manager_EXIT) {
		engine->managerdata.current_state = manager_runstate(engine->managerdata.current_state, &(engine->managerdata));
	}
	engine->managerdata.current_state = manager_MAIN;
	return engine_MAIN;
}





engine_state run_engine_PRE_EXIT(engine_t* engine) {
	saveWordlists(engine);
	saveStats(engine);
	cleanMemory(engine);
	return engine_EXIT;
}




engine_state run_engine_EXIT(engine_t* engine) {
	return engine_EXIT;
}




engine_state engine_runstate(engine_state wanted_state, engine_t* engine) {
	return engine->func_tab[wanted_state](engine);
}