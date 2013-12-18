#include "jnickgio.h"

namespace jnickg { namespace io {

// Uses prompt p to get single character input into char c,
// and also returns it. If input cannot be interpreted as
// a character, the user will be prompted to re-enter
// their input
char getChar(char & c, const char * const p)
{
	bool bad = true;

	while(bad)
	{
		// Display prompt
		std::cout << "\n" << p << std::endl;
		std::cout << "\t>";
		
		std::cin.get(c);
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		if(isalpha(c)) bad = false;
		else std::cout << "\nError: bad input!";
	}

	//std::cin.ignore(256, '\n');
	return c;
}

// Uses prompt p to get string input into string s, of maximum
// buffer size b. If s already contains something, it will be
// deleted. Returns the true length of the string, or -1
// if something went wrong.
int getStr(char *& s, int b, const char * const p)
{
	char* buff = new char[b];
	bool bad = true;

	while(bad)
	{
		// Display prompt
		std::cout << "\n" << p << std::endl;
		std::cout << "\t>";
		
		std::cin.clear();
		std::cin.getline(buff, b, '\n');
		
		// TODO: put a check in to test input
		bad = false;
		//if(CONDITION) bad = false;
		//else std::cout << "\nError: bad input!";
	}

	if(s) delete s;
	
	s = buff;

	//std::cin.ignore(b, '\n');
	return strlen(s);
}

// Uses prompt p to ask for integer input into int i. Also
// returns the value of i. If the input cannot be
// interpreted as a digit, the user will be prompted to re-
// enter their input.
int getInt(int & i, const char * const p)
{
	bool bad = true;

	while(bad)
	{
		std::cout << "\n" << p << std::endl;
		std::cout << "\t>";
		
		std::cin >> i;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		
		//TODO Add a working check for this
		/*if(isdigit(i))*/
		bad=false;
		//else std::cout << "\nError: bad input!";
	}
	return i;
}

}/* End namespace io */ } /* End namespace jnickg */
