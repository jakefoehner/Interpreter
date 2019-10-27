#ifndef Interpreter_h
#define Interpreter_h

#include <stdio.h>
using namespace std;


class Interpreter{
private:
	unsigned int * mem;
	int pc;
	int size;
public:
	Interpreter(unsigned int * input, int s);
	~Interpreter();
	void run();
};

#endif
