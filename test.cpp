//#include "implicitHeap.h"
#include "pairingHeap.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <math.h>


/*
command:
    ./<test_executable> <n> <infile> <outfile>

This will generate a heap based on a list of <n> insert and delete operations.
The resulting heap is checked against the <outfile>

Pass a dummy value of <n> for testing a pairing heap, since <n> is not needed
for pairing heap
*/

using namespace std;

int main(int argc, char *argv[]){
    //MinHeap h(atoi(argv[1]));
    PairingHeap h;
    //PairingHeap h = PairingHeap();
    ifstream operations(argv[2]);
    char op;
    int num;
    while(operations >> op){
        if (op == 'I'){
            operations >> num;
            h.insert(num);
        }
        else{
            h.extractMin();
        }
    }

    ifstream expected(argv[3]);
    num = -1;
    int n = 0;
    //cout << "Heap size - " << h.size() << endl;
    while (h.size()){
        expected >> num;
        n = h.extractMin();
        if (n != num){
            cout << "Expected "<<num << " got " << n << endl;
            cout << "Doesn't match. Test Failed!\n";
            return -1;
        }
    }
    cout << "Mission Accomplished!" << endl ;
    return 0;
}
