#ifndef implicit_h
#define implicit_h

class MinHeap
// This is 4-ary implementation
{
    private:
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
        int parent(int i) { return (i-1)/4; }
        int c1(int i) { return (4*i + 1); }
        int c2(int i) { return (4*i + 2); }
        int c3(int i) { return (4*i + 3); }
        int c4(int i) { return (4*i + 4); }

        int getMin() { return arr[0]; } // return min but don't remove
        int extractMin(); // remove and return min

        void insert(int key);
};

#endif
