#ifndef Interpreter_h
#define Interpreter_h

#include <stdio.h>
#include <vector>
using namespace std;

enum data_type{INT, CHAR, SHORT, FLOAT};
struct data_struct {
	data_type dtype;
	int iV;
	char cV;
	short sV;
	float fV;
};

class Interpreter{
private:
	unsigned char * mem;
	vector<data_struct> rstack;
	vector<int> fpstack;
	int pc;
	int size;
	int sp;
	int fpsp;
	bool stop;

public:
	Interpreter(unsigned char * input, int s);
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
