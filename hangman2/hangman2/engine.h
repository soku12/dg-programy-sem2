#ifndef ENGINE_H
#define ENGINE_H

#include "main.h"

engine_state run_engine_MAIN(engine_t* engine);

engine_state run_engine_PLAY(engine_t* engine);

engine_state run_engine_STATS(engine_t* engine);

engine_state run_engine_EDITOR(engine_t* engine);

engine_state run_engine_MANAGER(engine_t* engine);

engine_state run_engine_LOAD(engine_t* engine);

engine_state run_engine_UNLOAD(engine_t* engine);

engine_state run_engine_PRE_EXIT(engine_t* engine);

engine_state run_engine_EXIT(engine_t* engine);

engine_state engine_runstate(engine_state wanted_state, engine_t* engine);


#endif