#ifndef ASSIST_H
#define ASSIST_H

#include "main.h"

/**	Standard text input with dynamic memory allocation
	@return Pointer to the read string
*/
char* getstring();

/**	Gets the size of a file
	@param file Pointer to the file
	@return Size of the file
*/
int getFilesize(FILE* file);

/**	Checks is a letter is present in a tab of chars
	@param letter Letter to search for
	@param 
*/
int isLetterPresent(char letter, char* tab, int tab_size);

/**	Counts the amount of unique letters in a string.
	For example for "aabc" it returns 3
	@param word String to count
	@return The count
*/
int uniqueLetterCount(char* word);

/**	Searches for a word in a wordlist
	@param wordlist Wordlist to search in
	@param word Word to search for
	@return Position of the word in the wordlist o -1 if not found
*/
int findWord(wordlist_t* wordlist, char* word);

/**	Cleans the I/O buffer (sets all bytes to 0)
	@param engine Main UI engine pointer
*/
void cleanBuffer(engine_t* engine);

/**	Cleans all allocated memory of the program
	(except one thing which has to be cleaned in main because of a compilation error)
	@param engine Main UI engine pointer
*/
void cleanMemory(engine_t* engine);

/**	Count the '\n' characters in the buffer.
	Required to correctly determine the iobufferWrittenSize on Windows
	@param engine Main UI engine pointer
	@param size Size of the file that is currently sitting in the buffer
	@return Newline count
*/
int getBufferNewlineCount(engine_t* engine, int size);

#endif