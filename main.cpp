#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    ifstream inputF (argv[1], ios::binary);
    unsigned char byte;
    unsigned int * mem;
    int pc = 0;
    int i = 0;


    if (inputF.is_open()){
    	inputF.seekg(0, inputF.end);
    	int size = inputF.tellg();
    	inputF.seekg(0, inputF.beg);
    	mem = new unsigned int [size];
    	while (!inputF.eof()){
        	inputF >> byte;
        	mem[i] = static_cast<unsigned int>(byte);
			i++;
    	}
    	inputF.close();
    }
    else{
    	cout << "File failed to open." << endl;
    	exit(1);
    }

    return 0;
}
