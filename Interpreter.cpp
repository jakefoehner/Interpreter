#include "Interpreter.h"

Interpreter::Interpreter(unsigned char* input) {
	mem = input;
	pc = 0;
	sp = -1;
	fpsp = -1;
	stop = false;
}

Interpreter::~Interpreter() {}

void Interpreter::run(){
	while(!stop){
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
		    case 100:
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
		        halt();
		}
	}
}

void Interpreter::cmpe(){
	int result = 0;
	if (rstack[sp].dtype == INT){
		result = rstack[sp].iV == rstack[sp - 1].iV;
	}
	else if (rstack[sp].dtype == CHAR){
		result = rstack[sp].cV == rstack[sp - 1].cV;
	}
	else if (rstack[sp].dtype == SHORT) {
		result = rstack[sp].sV == rstack[sp - 1].sV;
	}
	else if (rstack[sp].dtype == FLOAT) {
		result = rstack[sp].fV == rstack[sp - 1].fV;
	}
	rstack[--sp].iV = result;
	rstack[sp].all = result;
	rstack[sp].dtype = INT;
	rstack.pop_back();
	pc++;
}

void Interpreter::cmplt(){
	int result = 0;
	if (rstack[sp].dtype == INT) {
		result = rstack[sp].iV > rstack[sp - 1].iV;
	}
	else if (rstack[sp].dtype == CHAR) {
		result = rstack[sp].cV > rstack[sp - 1].cV;
	}
	else if (rstack[sp].dtype == SHORT) {
		result = rstack[sp].sV > rstack[sp - 1].sV;
	}
	else if (rstack[sp].dtype == FLOAT) {
		result = rstack[sp].fV > rstack[sp - 1].fV;
	}
	rstack[--sp].iV = result;
	rstack[sp].all = result;
	rstack[sp].dtype = INT;
	rstack.pop_back();
	pc++;
}

void Interpreter::cmpgt(){
	int result = 0;
	if (rstack[sp].dtype == INT) {
		result = rstack[sp].iV < rstack[sp - 1].iV;
	}
	else if (rstack[sp].dtype == CHAR) {
		result = rstack[sp].cV < rstack[sp - 1].cV;
	}
	else if (rstack[sp].dtype == SHORT) {
		result = rstack[sp].sV < rstack[sp - 1].sV;
	}
	else if (rstack[sp].dtype == FLOAT) {
		result = rstack[sp].fV < rstack[sp - 1].fV;
	}
	rstack[--sp].iV = result;
	rstack[sp].all = result;
	rstack[sp].dtype = INT;
	rstack.pop_back();
	pc++;
}

void Interpreter::jmp(){
	if (rstack[sp].dtype == INT) {
		pc = rstack[sp].iV;
	}
	else if (rstack[sp].dtype == CHAR) {
		pc = rstack[sp].cV;
	}
	else if (rstack[sp].dtype == SHORT) {
		pc = rstack[sp].sV;
	}
	else if (rstack[sp].dtype == FLOAT) {
		pc = rstack[sp].fV;
	}
	rstack.pop_back();
	sp--;
}

void Interpreter::jmpc(){
	if (rstack[sp - 1].all == 1) {
		if (rstack[sp].dtype == INT) {
			pc = rstack[sp].iV;
		}
		else if (rstack[sp].dtype == CHAR) {
			pc = rstack[sp].cV;
		}
		else if (rstack[sp].dtype == SHORT) {
			pc = rstack[sp].sV;
		}
		else if (rstack[sp].dtype == FLOAT) {
			pc = rstack[sp].fV;
		}
	}
	else{
		pc++;
	}
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
}

void Interpreter::call(){
    if(rstack[sp].dtype == INT){
    	fpstack.push_back(sp - rstack[sp].iV - 1);
    }
    else if(rstack[sp].dtype == CHAR){
        fpstack.push_back(sp - rstack[sp].cV - 1);
    }
    else if(rstack[sp].dtype == SHORT){
        fpstack.push_back(sp - rstack[sp].sV - 1);
	}
    else if(rstack[sp].dtype == FLOAT){
        fpstack.push_back(sp - rstack[sp].fV - 1);
    }
    pc = static_cast<int>(rstack[--sp].all);
    rstack.pop_back();
    rstack.pop_back();
    sp--;
    fpsp++;
}

void Interpreter::ret(){
    for(int i = 0; i < sp - fpstack[fpsp]; i++){
    	rstack.pop_back();
    }
    sp = fpstack[fpsp--];
    pc = static_cast<int>(rstack[sp--].all);
    rstack.pop_back();
    fpstack.pop_back();
}

void Interpreter::pushc(){
	unsigned char byte = {mem[pc+1]};
	char bToC;
	memcpy(&bToC, &byte, sizeof(byte));
	Data c;
	c.dtype = CHAR;
	c.cV = bToC;
	c.all = bToC;
	rstack.push_back(c);
	sp++;
	pc += 2;
}

void Interpreter::pushs(){
	char bytes[2] = {mem[pc+1],mem[pc+2]};
	short bToS;
	memcpy(&bToS, bytes, sizeof(bytes));
	Data s;
	s.dtype = SHORT;
	s.sV = bToS;
	s.all = bToS;
	rstack.push_back(s);
	sp++;
	pc += 3;
}

void Interpreter::pushi(){
	char bytes[4] = {mem[pc+1],mem[pc+2],mem[pc+3],mem[pc+4]};
	int bToI;
	memcpy(&bToI, bytes, sizeof(bytes));
	Data i;
	i.dtype = INT;
	i.iV = bToI;
	i.all = bToI;
	rstack.push_back(i);
	sp++;
	pc += 5;
}

void Interpreter::pushf(){
	char bytes[4] = {mem[pc+1],mem[pc+2],mem[pc+3],mem[pc+4]};
	float bToF;
	memcpy(&bToF, bytes, sizeof(bytes));
	Data f;
	f.dtype = FLOAT;
	f.fV = bToF;
	f.all = bToF;
	rstack.push_back(f);
	sp++;
	pc += 5;
}

void Interpreter::pushvc(){
	Data d;
	d.dtype = CHAR;
	d.cV = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1].cV;
	d.all = d.cV;
	rstack.pop_back();
	rstack.push_back(d);
	pc++;
}

void Interpreter::pushvs(){
	Data d;
	d.dtype = SHORT;
	d.sV = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1].sV;
	d.all = d.sV;
	rstack.pop_back();
	rstack.push_back(d);
	pc++;
}

void Interpreter::pushvi(){
	Data d;
	d.dtype = INT;
	d.iV = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1].iV;
	d.all = d.iV;
	rstack.pop_back();
	rstack.push_back(d);
	pc++;
}

void Interpreter::pushvf(){
	Data d;
	d.dtype = FLOAT;
	d.fV = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1].fV;
	d.all = d.fV;
	rstack.pop_back();
	rstack.push_back(d);
	pc++;
}

void Interpreter::popm(){
	int del = static_cast<int>(rstack[sp].all);
	for(int i = 0; i < del; i++){
		rstack.pop_back();
	}
	pc++;
	sp -= del+1;
}

void Interpreter::popv(){
	rstack[fpstack[fpsp] + static_cast<int>(rstack[sp].all) + 1] = rstack[sp-1];
	rstack.pop_back();
	rstack.pop_back();
	pc++;
	sp -= 2;
}

void Interpreter::popa(){
	for(int i = 0; i < static_cast<int>(rstack[sp].all); i++){
		rstack[fpstack[fpsp] + i + 1] = rstack[sp- static_cast<int>(rstack[sp].all) + i];
	}
	for(int i = 0; i < sp - (fpstack[fpsp]+static_cast<int>(rstack[sp].all)); i++){
		rstack.pop_back();
	}
	sp = fpstack[fpsp]+static_cast<int>(rstack[sp].all);
	pc++;
}

void Interpreter::peekc(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1];
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
	pc++;
}

void Interpreter::peeks(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1];
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
	pc++;
}

void Interpreter::peeki(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1];
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
	pc++;
}

void Interpreter::peekf(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1];
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
	pc++;
}

void Interpreter::pokec(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1];
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
	pc++;
}

void Interpreter::pokes(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1];
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
	pc++;
}

void Interpreter::pokei(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1];
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
	pc++;
}

void Interpreter::pokef(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1];
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
	pc++;
}

void Interpreter::swp(){
	Data temp = rstack[sp - 1];
	rstack[sp - 1] = rstack[sp];
	rstack[sp] = temp;
	pc++;
}

void Interpreter::add(){
	if (rstack[sp].dtype == INT) {
		rstack[sp - 1].iV = rstack[sp - 1].iV + rstack[sp].iV;
		rstack[sp-1].all = rstack[sp].iV;
	}
	if (rstack[sp].dtype == CHAR) {
		rstack[sp - 1].cV = rstack[sp - 1].cV + rstack[sp].cV;
		rstack[sp-1].all = rstack[sp].cV;
	}
	if (rstack[sp].dtype == SHORT) {
		rstack[sp - 1].sV = rstack[sp - 1].sV + rstack[sp].sV;
		rstack[sp-1].all = rstack[sp].sV;
	}
	if (rstack[sp].dtype == FLOAT) {
		rstack[sp - 1].fV = rstack[sp - 1].fV + rstack[sp].fV;
		rstack[sp-1].all = rstack[sp].fV;
	}
	rstack.pop_back();
	sp--;
	pc++;
}

void Interpreter::sub(){
	if (rstack[sp].dtype == INT) {
		rstack[sp - 1].iV = rstack[sp - 1].iV - rstack[sp].iV;
		rstack[sp-1].all = rstack[sp].iV;
	}
	if (rstack[sp].dtype == CHAR) {
		rstack[sp - 1].cV = rstack[sp - 1].cV - rstack[sp].cV;
		rstack[sp-1].all = rstack[sp].cV;
	}
	if (rstack[sp].dtype == SHORT) {
		rstack[sp - 1].sV = rstack[sp - 1].sV - rstack[sp].sV;
		rstack[sp-1].all = rstack[sp].sV;
	}
	if (rstack[sp].dtype == FLOAT) {
		rstack[sp - 1].fV = rstack[sp - 1].fV - rstack[sp].fV;
		rstack[sp-1].all = rstack[sp].fV;
	}
	rstack.pop_back();
	sp--;
	pc++;
}

void Interpreter::mul(){
	if (rstack[sp].dtype == INT) {
		rstack[sp - 1].iV = rstack[sp - 1].iV * rstack[sp].iV;
		rstack[sp-1].all = rstack[sp].iV;
	}
	if (rstack[sp].dtype == CHAR) {
		rstack[sp - 1].cV = rstack[sp - 1].cV * rstack[sp].cV;
		rstack[sp-1].all = rstack[sp].cV;
	}
	if (rstack[sp].dtype == SHORT) {
		rstack[sp - 1].sV = rstack[sp - 1].sV * rstack[sp].sV;
		rstack[sp-1].all = rstack[sp].sV;
	}
	if (rstack[sp].dtype == FLOAT) {
		rstack[sp - 1].fV = rstack[sp - 1].fV * rstack[sp].fV;
		rstack[sp-1].all = rstack[sp].fV;
	}
	rstack.pop_back();
	sp--;
	pc++;
}

void Interpreter::div(){
	if (rstack[sp].dtype == INT) {
		rstack[sp - 1].iV = rstack[sp - 1].iV / rstack[sp].iV;
		rstack[sp-1].all = rstack[sp].iV;
	}
	if (rstack[sp].dtype == CHAR) {
		rstack[sp - 1].cV = rstack[sp - 1].cV / rstack[sp].cV;
		rstack[sp-1].all = rstack[sp].cV;
	}
	if (rstack[sp].dtype == SHORT) {
		rstack[sp - 1].sV = rstack[sp - 1].sV / rstack[sp].sV;
		rstack[sp-1].all = rstack[sp].sV;
	}
	if (rstack[sp].dtype == FLOAT) {
		rstack[sp - 1].fV = rstack[sp - 1].fV / rstack[sp].fV;
		rstack[sp-1].all = rstack[sp].fV;
	}
	rstack.pop_back();
	sp--;
	pc++;
}

void Interpreter::printc(){
	if (rstack[sp].dtype == CHAR) {
		cout << static_cast<unsigned int>(rstack[sp--].cV) << endl;
		rstack.pop_back();
	}
	else {
		cout << "printc has invalid input" << endl;
	}
	pc++;
}

void Interpreter::prints(){
	if (rstack[sp].dtype == SHORT) {
		cout << rstack[sp--].sV << endl;
		rstack.pop_back();
	}
	else {
		cout << "prints has invalid input" << endl;
	}
	pc++;
}

void Interpreter::printi(){
	if (rstack[sp].dtype == INT) {
		cout << rstack[sp--].iV << endl;
		rstack.pop_back();
	}
	else {
		cout << "printi has invalid input" << endl;
	}
	pc++;
}

void Interpreter::printf(){
	if (rstack[sp].dtype == FLOAT) {
		cout << rstack[sp--].fV << endl;
		rstack.pop_back();
	}
	else {
		cout << "printf has invalid input" << endl;
	}
	pc++;
}

void Interpreter::halt(){
	cout << endl;
	cout << "Compile Values:" << endl;
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
				cout << static_cast<int>(rstack[i].cV) << endl;
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
