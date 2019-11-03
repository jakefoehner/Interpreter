#include <iostream>
#include <fstream>
#include <string>
#include "Interpreter.h"
using namespace std;

int main(int argc, char* argv[]) {
    ifstream inputF (argv[1], ios::binary);
    unsigned char * input;
    int size;

    //check if file opened correctly
    if (!inputF){
    	cout << "File failed to open." << endl;
    	exit(1);
    }

    //fill memory with the input
	inputF.seekg(0, inputF.end);
	size = inputF.tellg();
	inputF.seekg(0, inputF.beg);
	input = new unsigned char [size];
    inputF.read((char *) input, size);
	inputF.close();

	//build, and run interpreter
	Interpreter interp = Interpreter(input, size);
	interp.run();

    return 0;
}
