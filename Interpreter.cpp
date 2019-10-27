#include "Interpreter.h"
#include <iostream>
using namespace std;

Interpreter::Interpreter(unsigned int* input, int s) {
	mem = input;
	pc = 0;
	size = s;
}

Interpreter::~Interpreter() {}

void Interpreter::run(){
	for(int i = 0; i < size; i++){
		cout << mem[i] << endl;
	}
}
