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
	double result = rstack[sp].all == rstack[sp - 1].all;
	rstack[--sp].all = result;
	rstack[sp].dtype = INT;
	rstack.pop_back();
	pc++;
}

void Interpreter::cmplt(){
	double result = rstack[sp].all > rstack[sp - 1].all;
	rstack[--sp].all = result;
	rstack[sp].dtype = INT;
	rstack.pop_back();
	pc++;
}

void Interpreter::cmpgt(){
	double result = rstack[sp].all < rstack[sp - 1].all;
	rstack[--sp].all = result;
	rstack[sp].dtype = INT;
	rstack.pop_back();
	pc++;
}

void Interpreter::jmp(){
	pc = static_cast<int>(rstack[sp].all);
	rstack.pop_back();
	sp--;
}

void Interpreter::jmpc(){
	if (rstack[sp - 1].all == 1) {
		pc = static_cast<int>(rstack[sp].all);
	}
	else{
		pc++;
	}
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
}

void Interpreter::call(){
    fpstack.push_back(sp - static_cast<int>(rstack[sp].all) - 1);
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
	f.all = bToF;
	rstack.push_back(f);
	sp++;
	pc += 5;
}

void Interpreter::pushvc(){
	Data d;
	d.dtype = CHAR;
	d.all = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1].all;
	rstack.pop_back();
	rstack.push_back(d);
	pc++;
}

void Interpreter::pushvs(){
	Data d;
	d.dtype = SHORT;
	d.all = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1].all;
	rstack.pop_back();
	rstack.push_back(d);
	pc++;
}

void Interpreter::pushvi(){
	Data d;
	d.dtype = INT;
	d.all = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1].all;
	rstack.pop_back();
	rstack.push_back(d);
	pc++;
}

void Interpreter::pushvf(){
	Data d;
	d.dtype = FLOAT;
	d.all = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1].all;
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
	int end = static_cast<int>(rstack[sp].all);
	for(int i = 0; i < end; i++){
		rstack[fpstack[fpsp] + i + 1] = rstack[sp-end+i];
	}
	for(int i = 0; i < sp - (fpstack[fpsp]+end); i++){
		rstack.pop_back();
	}
	sp = fpstack[fpsp]+end;
	pc++;
}

void Interpreter::peekc(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1];
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1].dtype = CHAR;
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
	pc++;
}

void Interpreter::peeks(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1];
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1].dtype = SHORT;
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
	pc++;
}

void Interpreter::peeki(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1];
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1].dtype = INT;
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
	pc++;
}

void Interpreter::peekf(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1];
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1].dtype = FLOAT;
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
	pc++;
}

void Interpreter::pokec(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1];
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1].dtype = CHAR;
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
	pc++;
}

void Interpreter::pokes(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1];
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1].dtype = SHORT;
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
	pc++;
}

void Interpreter::pokei(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1];
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1].dtype = INT;
	rstack.pop_back();
	rstack.pop_back();
	sp -= 2;
	pc++;
}

void Interpreter::pokef(){
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1] = rstack[fpstack[fpsp]+static_cast<int>(rstack[sp-1].all)+1];
	rstack[fpstack[fpsp]+static_cast<int>(rstack[sp].all)+1].dtype = FLOAT;
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
	rstack[sp - 1].all = rstack[sp - 1].all + rstack[sp].all;
	rstack.pop_back();
	sp--;
	pc++;
}

void Interpreter::sub(){
	rstack[sp - 1].all = rstack[sp - 1].all - rstack[sp].all;
	rstack.pop_back();
	sp--;
	pc++;
}

void Interpreter::mul(){
	rstack[sp - 1].all = rstack[sp - 1].all * rstack[sp].all;
	rstack.pop_back();
	sp--;
	pc++;
}

void Interpreter::div(){
	rstack[sp - 1].all = rstack[sp - 1].all / rstack[sp].all;
	rstack.pop_back();
	sp--;
	pc++;
}

void Interpreter::printc(){
	if (rstack[sp].dtype == CHAR) {
		cout << static_cast<unsigned int>(rstack[sp--].all) << endl;
		rstack.pop_back();
	}
	else {
		cout << "printc has invalid input" << endl;
	}
	pc++;
}

void Interpreter::prints(){
	if (rstack[sp].dtype == SHORT) {
		cout << static_cast<unsigned int>(rstack[sp--].all) << endl;
		rstack.pop_back();
	}
	else {
		cout << "prints has invalid input" << endl;
	}
	pc++;
}

void Interpreter::printi(){
	if (rstack[sp].dtype == INT) {
		cout << static_cast<unsigned int>(rstack[sp--].all) << endl;
		rstack.pop_back();
	}
	else {
		cout << "printi has invalid input" << endl;
	}
	pc++;
}

void Interpreter::printf(){
	if (rstack[sp].dtype == FLOAT) {
		cout << rstack[sp--].all << endl;
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
			cout << static_cast<unsigned int>(rstack[sp].all) << endl;
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
