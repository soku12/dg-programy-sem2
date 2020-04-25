#include "main.h"

int main(int argc, char* argv[]) {
	srand(time(NULL));
	
	engine_t engine = engineInit();
	loadStats(&engine);
	engine.managerdata.engine_ptr = &engine;
	engine.editordata.engine_ptr = &engine;
	engine.gamedata.engine_ptr = &engine;

	for (int i = 1; i < argc; i++) {
		loadWordlist(&engine, argv[i]);
	}

	while (engine.current_state != engine_EXIT) {
		engine.current_state = engine_runstate(engine.current_state, &engine);
	}

	//when this boi was in the cleanMemory func it kept crashing (debug assertion error), 
	//when i put him in here the problem magically disappeared, hmmm...
	free(engine.managerdata.filename);

#ifdef _MSC_VER //if the compiler is Visual C
	_CrtDumpMemoryLeaks();
#endif
	return 0;
}