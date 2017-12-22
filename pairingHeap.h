#ifndef pairing_h
#define pairing_h

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class PairNode
{
    public:
        int data;
        PairNode *child;
        PairNode *next;
        PairNode *prev;
        PairNode(int key)
        {
            this->data = key;
            child = NULL;
            next = NULL;
            prev = NULL;
        }
};

class PairingHeap
{
    private:
        PairNode *root;
        int heap_size;
        void merge(PairNode *&first, PairNode* second);
        PairNode *combineSiblings(PairNode *firstSibling);

    public:
        PairingHeap();
        PairingHeap(int key);
        //~PairingHeap();

        int size();
        int getMin();
        void insert(int key);
        int extractMin();
};

#endif
