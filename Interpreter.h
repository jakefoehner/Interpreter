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
