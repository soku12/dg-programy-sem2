#ifndef GAME_H
#define GAME_H

#include "main.h"

game_state run_game_INIT(game_t* game);

game_state run_game_MAIN(game_t* game);

game_state run_game_LETTER_PICK(game_t* game);

game_state run_game_WORD_GUESS(game_t* game);

game_state run_game_EXIT_PROMPT(game_t* game);

game_state run_game_WIN(game_t* game);

game_state run_game_LOSE(game_t* game);

game_state run_game_EXIT(game_t* game);

game_state game_runstate(game_state wanted_state, game_t* game);

void updateStats(engine_t* engine);



#endif