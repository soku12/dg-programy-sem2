#ifndef EDITOR_H
#define EDITOR_H

#include "main.h"

editor_state run_editor_MAIN(editor_t* editor);

editor_state run_editor_FILE_SELECT(editor_t* editor);

editor_state run_editor_ACTION_SELECT(editor_t* editor);

editor_state run_editor_ADD(editor_t* editor);

editor_state run_editor_REMOVE(editor_t* editor);

editor_state run_editor_EXIT(editor_t* editor);

editor_state editor_runstate(editor_state wanted_state, editor_t* editor);

#endif