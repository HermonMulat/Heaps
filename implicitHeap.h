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

    // ops to restore heap property
    void siftUp(int index);
    void siftDown(int index);

    // parent and child accecsor methods
    int getParent(int index) { return (index-1)/2; }
    int getLeftChild(int index) { return (2*index + 1); }
    int getRightChild(int index) { return (2*index + 2); }

    int pop(); // remove and return min
    int getMin() { return arr[0]; } // return min but don't remove

    void decreaseKey(int index, int new_val);
    void increaseKey(int index, int new_val);

    void deleteKey(int index);
    void insertKey(int key);
};

#endif
