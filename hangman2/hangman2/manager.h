#ifndef MANAGER_H
#define MANAGER_H

#include "main.h"

manager_state run_manager_MAIN(manager_t* manager);

manager_state run_manager_FILE_SELECT(manager_t* manager);

manager_state run_manager_PREVIEW(manager_t* manager);

manager_state run_manager_LOAD(manager_t* manager);

manager_state run_manager_UNLOAD(manager_t* manager);

manager_state run_manager_RELOAD(manager_t* manager);

manager_state run_manager_EXIT(manager_t* manager);

manager_state manager_runstate(manager_state wanted_state, manager_t* manager);

#endif
