#ifndef Interpreter_h
#define Interpreter_h

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum type{CHAR, SHORT, INT, FLOAT};

struct Data{
	type dtype;
	double all;
};

class Interpreter{
private:
	unsigned char * mem;
	vector<Data> rstack;
	vector<int> fpstack;
	int pc;
	int sp;
	int fpsp;
	bool stop;
public:
	Interpreter(unsigned char * input);
	~Interpreter();

	void run();
	void cmpe();
	void cmplt();
    void cmpgt();
    void jmp();
    void jmpc();
    void call();
    void ret();
    void pushc();
    void pushs();
    void pushi();
    void pushf();
    void pushvc();
    void pushvs();
    void pushvi();
    void pushvf();
    void popm();
    void popv();
    void popa();
    void peekc();
    void peeks();
    void peeki();
    void peekf();
    void pokec();
    void pokes();
    void pokei();
    void pokef();
    void swp();
    void add();
    void sub();
    void mul();
    void div();
    void printc();
    void prints();
    void printi();
    void printf();
    void halt();
};

#endif
