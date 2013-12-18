#include <iostream>
#include <istream>
#include <cctype>

namespace jnickg { namespace io {
	// Uses prompt p to get single character input into char c,
	// and also returns it. If input cannot be interpreted as
	// a character, the user will be prompted to re-enter
	// their input
	char getChar(char & c, const char * const p);

	// Uses prompt p to get string input into string s, of maximum
	// buffer size b. If s already contains something, it will be
	// deleted. Returns the true length of the string, or -1
	// if something went wrong.
	int getStr(char *& s, int b, const char * const p);
	
	// Uses prompt p to ask for integer input into int i. Also
	// returns the value of i. If the input cannot be
	// interpreted as a digit, the user will be prompted to re-
	// enter their input.
	int getInt(int & i, const char * const p);

}} // end namespace
