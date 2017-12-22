#ifndef pairing_h
#define pairing_h

#include <stdint.h>
#include <cstdlib>
#include <iostream>

using namespace std;

class PairNode
{
    public:
        uint64_t data;
        PairNode *child;
        PairNode *next;
        PairNode *prev;
        PairNode(uint64_t key)
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
        PairingHeap(uint64_t key);
        ~PairingHeap();

        uint64_t size();
        uint64_t getMin();
        void insert(uint64_t key);
        uint64_t extractMin();
};

#endif
