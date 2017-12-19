#ifndef implicit_h
#define implicit_h

class MinHeap
{
    int *arr; // pointer to array of elements in heap
    int capacity; // maximum possible size of min heap
    int heap_size; // Current number of elements in min heap
public:
    // Constructor
    MinHeap(int capacity);
    // utility functions
    int size(){ return heap_size; }

    // ops to restore heap property
    void siftUp(int i);
    void siftDown(int i);

    // parent and child accecsor methods
    int parent(int i) { return (i-1)/2; }
    int left(int i) { return (2*i + 1); }
    int right(int i) { return (2*i + 2); }

    int getMin() { return arr[0]; } // return min but don't remove
    int extractMin(); // remove and return min

    void insertKey(int key);
};

#endif
