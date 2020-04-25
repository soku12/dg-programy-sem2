#ifndef FILE_OPS_H
#define FILE_OPS_H

#include "main.h"

/**	Reads a wordlist file into a buffer for processing (sets iobufferWrittenSize to filesize)
	@param engine Main UI engine pointer
	@param filename Name of the file to load
	@return 1 if successful, 0 if an error occured
	*/
int loadFileToBuffer(engine_t* engine, char* filename);

/**	Saves the valid part of the buffer (iobufferWrittenSize) into a file 
	@param engine Main UI engine pointer
	@param filename Name of a file to save to
	@return 1 if successful, 0 if an error occured
*/
int saveBufferToFile(engine_t* engine, char* filename);

/**	Loads a wordlist from file to the main wordlist tab char by char.
	@param engine Main UI engine pointer
	@param filename Name of the file to load
	@return 1 if successful, 0 if an error occured
*/
int loadWordlist(engine_t* engine, char* filename);

/**	Loads a wordlist from the wordlist tab into a buffer (sets iobufferWrittenSize to charcounter)
	@param wordlist Pointer to the wordlist
	@param engine Main UI engine pointer
	@return 1 if successful, 0 if an error occured
*/
int wordlistToBuffer(wordlist_t* wordlist, engine_t* engine);

/**	Saves all modified wordlists into their respective files
	@param engine Main UI engine pointer
	@return 1 if successful, 0 if an error occured
*/
int saveWordlists(engine_t* engine);

/**	Loads user's stats from the "stats" binary file
	@param engine Main UI engine pointer
	@return 1 if successful, 0 if an error occured
*/
int loadStats(engine_t* engine);

/**	Saves user's stats into the "stats" binary file
	@param engine Main UI engine pointer
	@return 1 if successful, 0 if an error occured
*/
int saveStats(engine_t* engine);

#endif
