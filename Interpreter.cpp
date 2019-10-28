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
		switch (mem[i]) {
			case 132:
				cmpe();
		        break;
		    case 136:
		        cmplt();
		        break;
		    case 140:
		        cmpgt();
		        break;
		    case 36:
		        jmp();
		        break;
		    case 40:
		        jmpc();
		        break;
		    case 44:
		        call();
		        break;
		    case 48:
		        ret();
		        break;
		    case 68:
		        pushc();
		        break;
		    case 69:
		        pushs();
		        break;
		    case 70:
		        pushi();
		        break;
		    case 71:
		        pushf();
		        break;
		    case 72:
		        pushvc();
		        break;
		    case 73:
		        pushvs();
		        break;
		    case 74:
		        pushvi();
		        break;
		    case 75:
		        pushvf();
		        break;
		    case 76:
		        popm();
		        break;
		    case 80:
		        popv();
		        break;
		    case 77:
		        popa();
		        break;
		    case 84:
		        peekc();
		        break;
		    case 85:
		        peeks();
		        break;
		    case 86:
		        peeki();
		        break;
		    case 87:
		        peekf();
		        break;
		    case 88:
		        pokec();
		        break;
		    case 89:
		        pokes();
		        break;
		    case 90:
		        pokei();
		        break;
		    case 91:
		        pokef();
		        break;
		    case 94:
		        swp();
		        break;
		    case 110:
		        add();
		        break;
		    case 104:
		        sub();
		        break;
		    case 108:
		        mul();
		        break;
		    case 112:
		        div();
		        break;
		    case 144:
		        printc();
		        break;
		    case 145:
		        prints();
		        break;
		    case 146:
		        printi();
		        break;
		    case 147:
		        printf();
		        break;
		    case 0:
		        halt();
		        break;
		    default:
		        cout << "Error, Interpreter code does not have a function." << endl;
		}
	}
}

void Interpreter::cmpe(){

}

void Interpreter::cmplt(){

}
void Interpreter::cmpgt(){

}

void Interpreter::jmp(){

}
void Interpreter::jmpc(){

}

void Interpreter::call(){

}
void Interpreter::ret(){

}

void Interpreter::pushc(){

}
void Interpreter::pushs(){

}
void Interpreter::pushi(){

}
void Interpreter::pushf(){

}
void Interpreter::pushvc(){

}
void Interpreter::pushvs(){

}
void Interpreter::pushvi(){

}
void Interpreter::pushvf(){

}
void Interpreter::popm(){

}
void Interpreter::popv(){

}
void Interpreter::popa(){

}
void Interpreter::peekc(){

}
void Interpreter::peeks(){

}
void Interpreter::peeki(){

}
void Interpreter::peekf(){

}
void Interpreter::pokec(){

}
void Interpreter::pokes(){

}
void Interpreter::pokei(){

}
void Interpreter::pokef(){

}
void Interpreter::swp(){

}

void Interpreter::add(){

}
void Interpreter::sub(){

}
void Interpreter::mul(){

}
void Interpreter::div(){

}
void Interpreter::printc(){

}
void Interpreter::prints(){

}
void Interpreter::printi(){

}
void Interpreter::printf(){

}
void Interpreter::halt(){

}
