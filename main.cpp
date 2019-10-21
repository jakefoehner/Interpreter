#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
    ifstream inputF;

    inputF.open(argv[1]);
    if (!inputF) {
        cout << "Input file could not be opened";
        exit(1);
    }

    inputF.close();

    return 0;
}
