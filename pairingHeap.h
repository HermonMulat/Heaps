#ifndef pairing_h
#define pairing_h

#include <stdlib.h>
#include <vector>

typedef struct Node{
    int data;
    struct Node *prev;
    struct Node *next;
    struct Node *child;
} Node_t;

class PairingHeap
{
public:
    Node_t *root;
    int heap_size; // Current number of elements in min heap

    void merge(PairingHeap p);

    // Constructors - for empty heap, or with 1 element
    PairingHeap();
    PairingHeap(int key);
    // TODO: Define and complete A Destructor
    //~PairingHeap();

    // utility functions
    int size(){ return heap_size; }

    int getMin() { return root->data; } // return min but don't remove
    int extractMin(); // remove and return min

    void insertKey(int key);

};

#endif
