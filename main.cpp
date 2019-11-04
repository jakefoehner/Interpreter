#include "Interpreter.h"

int main(int argc, char* argv[]) {
    ifstream inputF (argv[1], ios::binary);
    unsigned char * input;
    int size;

    if (!inputF){
    	cout << "File failed to open." << endl;
    	exit(1);
    }

	inputF.seekg(0, inputF.end);
	size = inputF.tellg();
	inputF.seekg(0, inputF.beg);
	input = new unsigned char [size];
    inputF.read((char *) input, size);
	inputF.close();

	Interpreter * interp = new Interpreter(input);
	interp->run();

	delete[] input;

    return 0;
}
