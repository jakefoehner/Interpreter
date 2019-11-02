#include "Interpreter.h"
#include <iostream>
using namespace std;


Interpreter::Interpreter(char* input, int s) {
	mem = input;
	pc = 0;
	size = s;
	sp = -1;
	fpsp = -1;
	stop = false;
}

Interpreter::~Interpreter() {}

void Interpreter::run(){
	for(int i =0; i < 21; i++){
		cout << static_cast<unsigned int>(mem[pc]) << endl;
		switch (static_cast<unsigned int>(mem[pc])) {
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
	halt();
}

void Interpreter::cmpe(){
	int result = 0;
	if (rstack[sp].dtype == INT){
		result = rstack[sp].iV == rstack[sp - 1].iV;
	}
	if (rstack[sp].dtype == CHAR){
		result = rstack[sp].cV == rstack[sp - 1].cV;
	}
	if (rstack[sp].dtype == SHORT) {
		result = rstack[sp].sV == rstack[sp - 1].sV;
	}
	if (rstack[sp].dtype == FLOAT) {
		result = rstack[sp].fV == rstack[sp - 1].fV;
	}
	rstack[sp - 1].iV = result;
	rstack[sp - 1].dtype = INT;
	rstack.pop_back();
	sp--;
	pc++;
}

void Interpreter::cmplt(){
	int result = 0;
	if (rstack[sp].dtype == INT) {
		result = rstack[sp].iV > rstack[sp - 1].iV;
	}
	if (rstack[sp].dtype == CHAR) {
		result = rstack[sp].cV > rstack[sp - 1].cV;
	}
	if (rstack[sp].dtype == SHORT) {
		result = rstack[sp].sV > rstack[sp - 1].sV;
	}
	if (rstack[sp].dtype == FLOAT) {
		result = rstack[sp].fV > rstack[sp - 1].fV;
	}
	rstack[sp - 1].iV = result;
	rstack[sp - 1].dtype = INT;
	rstack.pop_back();
	sp--;
	pc++;
}

void Interpreter::cmpgt(){
	int result = 0;
	if (rstack[sp].dtype == INT) {
		result = rstack[sp].iV < rstack[sp - 1].iV;
	}
	if (rstack[sp].dtype == CHAR) {
		result = rstack[sp].cV < rstack[sp - 1].cV;
	}
	if (rstack[sp].dtype == SHORT) {
		result = rstack[sp].sV < rstack[sp - 1].sV;
	}
	if (rstack[sp].dtype == FLOAT) {
		result = rstack[sp].fV < rstack[sp - 1].fV;
	}
	rstack[sp - 1].iV = result;
	rstack[sp - 1].dtype = INT;
	rstack.pop_back();
	sp--;
	pc++;
}

void Interpreter::jmp(){
	data_type type = rstack[sp].dtype;//cant figure out why this wont work
	if (type == INT) {
		pc = rstack[sp].iV;
	}
	if (type == CHAR) {
		pc = rstack[sp].cV;
	}
	if (type == SHORT) {
		pc = rstack[sp].sV;
	}
	if (type == FLOAT) {
		pc = rstack[sp].fV;
	}
	sp--;
}

void Interpreter::jmpc(){
	bool happened = false;
	if (rstack[sp - 1].iV == 1) {
		//pc = rstack[sp];  //IDK how to fix this.
		happened = true;
	}
	if (!happened) {
		pc++;
	}
	sp = sp - 2;
}

void Interpreter::call(){
    if(rstack[sp].dtype == INT){
    	fpstack.push_back(sp - rstack[sp].iV - 1);
    }
    if(rstack[sp].dtype == CHAR){
        fpstack.push_back(sp - rstack[sp].cV - 1);
    }
    if(rstack[sp].dtype == SHORT){
        fpstack.push_back(sp - rstack[sp].sV - 1);
	}
    if(rstack[sp].dtype == FLOAT){
        fpstack.push_back(sp - rstack[sp].fV - 1);
    }
    sp--;
    fpsp++;
    rstack.pop_back();
    pc = rstack[sp--].iV;
    rstack.pop_back();
}

void Interpreter::ret(){

}

void Interpreter::pushc(){
	data_struct c;
	c.dtype = CHAR;
	c.cV = mem[pc+1];
	rstack.push_back(c);
	sp++;
	pc += 2;
}
void Interpreter::pushs(){

}
void Interpreter::pushi(){
	char bytes[4] = {mem[pc+1],mem[pc+2],mem[pc+3],mem[pc+4]};
	int bToI;
	memcpy(&bToI, bytes, 4);
	data_struct i;
	i.dtype = INT;
	i.iV = bToI;
	rstack.push_back(i);
	sp++;
	pc += 5;
}
void Interpreter::pushf(){

}
void Interpreter::pushvc(){
	rstack[sp].cV = rstack[fpstack[fpsp]+rstack[sp].cV+1].cV;
	pc++;
}
void Interpreter::pushvs(){
	rstack[sp].sV = rstack[fpstack[fpsp]+rstack[sp].sV+1].sV;
	pc++;
}
void Interpreter::pushvi(){
	rstack[sp].iV = rstack[fpstack[fpsp]+rstack[sp].iV+1].iV;
	pc++;
}
void Interpreter::pushvf(){
	rstack[sp].fV = rstack[fpstack[fpsp]+rstack[sp].fV+1].fV;
	pc++;
}
void Interpreter::popm(){

}
void Interpreter::popv(){
	rstack[fpstack[fpsp] + rstack[sp].iV + 1].iV = rstack[sp-1].iV;
	sp -= 2;
	rstack.pop_back();
	rstack.pop_back();
	pc++;
}
void Interpreter::popa(){

}
void Interpreter::peekc(){

}
void Interpreter::peeks(){

}
void Interpreter::peeki(){
	pc++;
	rstack[fpstack[fpsp] + rstack[sp-1].iV+1].iV = rstack[fpstack[fpsp]+rstack[sp].iV+1].iV;
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
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
	data_struct temp = rstack[sp - 1];
	rstack[sp - 1] = rstack[sp];
	rstack[sp] = temp;
	pc++;
}

void Interpreter::add(){
	if (rstack[sp].dtype == INT) {
		rstack[sp - 1].iV = rstack[sp - 1].iV + rstack[sp].iV;
	}
	if (rstack[sp].dtype == CHAR) {
		rstack[sp - 1].cV = rstack[sp - 1].cV + rstack[sp].cV;
	}
	if (rstack[sp].dtype == SHORT) {
		rstack[sp - 1].sV = rstack[sp - 1].sV + rstack[sp].sV;
	}
	if (rstack[sp].dtype == FLOAT) {
		rstack[sp - 1].fV = rstack[sp - 1].fV + rstack[sp].fV;
	}
	sp--;
	pc++;
}
void Interpreter::sub(){
	if (rstack[sp].dtype == INT) {
		rstack[sp - 1].iV = rstack[sp - 1].iV - rstack[sp].iV;
	}
	if (rstack[sp].dtype == CHAR) {
		rstack[sp - 1].cV = rstack[sp - 1].cV - rstack[sp].cV;
	}
	if (rstack[sp].dtype == SHORT) {
		rstack[sp - 1].sV = rstack[sp - 1].sV - rstack[sp].sV;
	}
	if (rstack[sp].dtype == FLOAT) {
		rstack[sp - 1].fV = rstack[sp - 1].fV - rstack[sp].fV;
	}
	sp--;
	pc++;
}
void Interpreter::mul(){
	if (rstack[sp].dtype == INT) {
		rstack[sp - 1].iV = rstack[sp - 1].iV * rstack[sp].iV;
	}
	if (rstack[sp].dtype == CHAR) {
		rstack[sp - 1].cV = rstack[sp - 1].cV * rstack[sp].cV;
	}
	if (rstack[sp].dtype == SHORT) {
		rstack[sp - 1].sV = rstack[sp - 1].sV * rstack[sp].sV;
	}
	if (rstack[sp].dtype == FLOAT) {
		rstack[sp - 1].fV = rstack[sp - 1].fV * rstack[sp].fV;
	}
	sp--;
	pc++;
}
void Interpreter::div(){
	if (rstack[sp].dtype == INT) {
		rstack[sp - 1].iV = rstack[sp - 1].iV / rstack[sp].iV;
	}
	if (rstack[sp].dtype == CHAR) {
		rstack[sp - 1].cV = rstack[sp - 1].cV / rstack[sp].cV;
	}
	if (rstack[sp].dtype == SHORT) {
		rstack[sp - 1].sV = rstack[sp - 1].sV / rstack[sp].sV;
	}
	if (rstack[sp].dtype == FLOAT) {
		rstack[sp - 1].fV = rstack[sp - 1].fV / rstack[sp].fV;
	}
	sp--;
	pc++;
}
void Interpreter::printc(){
	if (rstack[sp].dtype == CHAR) {
		cout << rstack[sp--].cV << endl;
	}
	else {
		cout << "printc has invalid input" << endl;
	}
	pc++;
}
void Interpreter::prints(){
	if (rstack[sp].dtype == SHORT) {
		cout << rstack[sp--].sV << endl;
	}
	else {
		cout << "prints has invalid input" << endl;
	}
	pc++;
}
void Interpreter::printi(){
	if (rstack[sp].dtype == INT) {
		cout << rstack[sp--].iV << endl;
	}
	else {
		cout << "printi has invalid input" << endl;
	}
	pc++;
}
void Interpreter::printf(){
	if (rstack[sp].dtype == FLOAT) {
		cout << rstack[sp--].fV << endl;
	}
	else {
		cout << "printf has invalid input" << endl;
	}
	pc++;
}
void Interpreter::halt(){
	cout << "PC:" << pc << endl;
	cout << "SP:" << sp << endl;
	cout << "RSTACK:" << endl;
	if(sp == -1){
		cout << "EMPTY" << endl;
	}
	else{
		for(int i = sp; i > -1; i--){
			if (rstack[i].dtype == INT) {
				cout << rstack[i].iV << endl;
			}
			if (rstack[i].dtype == CHAR) {
				cout << rstack[i].cV << endl;
			}
			if (rstack[i].dtype == SHORT) {
				cout << rstack[i].sV << endl;
			}
			if (rstack[i].dtype == FLOAT) {
				cout << rstack[i].fV << endl;
			}
		}
	}
	cout << "FPSP:" << fpsp << endl;
	cout << "FPSTACK:" << endl;
	if(fpsp == -1){
			cout << "EMPTY" << endl;
	}
	else{
		for(int j = fpsp; j > -1; j--){
			cout << fpstack[j] << endl;
		}
	}
	stop = true;
}
