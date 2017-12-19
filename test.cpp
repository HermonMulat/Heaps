#include "implicitHeap.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <math.h>

/*
command:
    ./<test_executable> <n> <infile> <outfile>

This will generate a heap based on a list of <n> insert and delete operations. The
resulting heap is checked against the <outfile>
*/

using namespace std;

int main(int argc, char *argv[]){
    MinHeap h(atoi(argv[1]));
    ifstream operations(argv[2]);
    char op;
    int num;
    while(operations >> op){
        if (op == 'I'){
            operations >> num;
            h.insertKey(num);
        }
        else{
            h.extractMin();
        }
    }

    ifstream expected(argv[3]);
    num = -1;
    int n = 0;
    cout << "Heap size - " << h.size() << endl;
    while (h.size()){
        expected >> num;
        n = h.extractMin();
        if (n != num){
            cout << "Expected "<<num << " got " << n << endl;
            cout << "Doesn't match. Test Failed\n";
            return -1;
        }
    }
    cout << "Mission Accomplished" << endl ;
    return 0;
}
