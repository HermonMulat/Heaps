#include <stdlib.h>
#include <iostream>
#include <climits>
#include "implicitHeap.h"

#define MALLOC(size) (malloc(size))

using namespace std;

MinHeap::MinHeap(int size){
    capacity = size;
    heap_size = 0;
    arr = (int *) MALLOC(sizeof(int)*capacity);
}

int MinHeap::extractMin(){
    if (heap_size == 0){
        return INT_MAX;
    }

    int min_val = arr[0];
    arr[0] = arr[heap_size - 1];
    heap_size--;
    siftDown(0);
    return min_val;
}

void MinHeap::insertKey(int key){
    if (heap_size == capacity){
        // if we want, we could realloc here, like double size of array
        cout << "Heap capacity exceeded" << '\n';
        return;
    }
    heap_size++;
    arr[heap_size - 1] = key;
    siftUp(heap_size - 1);
}

void MinHeap::siftUp(int i){
    int parent_index = parent(i);
    int curr_val = arr[i];

    while (i!=0 &&  arr[parent_index] > curr_val){
        arr[i] = arr[parent_index];
        arr[parent_index] = curr_val;
        i  = parent_index;
        parent_index = parent(i);
    }
}

void MinHeap::siftDown(int i){
    int curr_val = arr[i];
    int min_val = curr_val,min_index = i;
    while(i<heap_size){
        // First indentify if either child is smaller (and the i)
        if (c1(i)< heap_size && arr[min_index] > arr[c1(i)]){
            min_index = c1(i);
        }
        if (c2(i) < heap_size && arr[min_index] > arr[c2(i)]){
            min_index = c2(i);
        }
        if (c3(i)< heap_size && arr[min_index] > arr[c3(i)]){
            min_index = c3(i);
        }
        if (c4(i) < heap_size && arr[min_index] > arr[c4(i)]){
            min_index = c4(i);
        }
        if (min_index == i){
            return; // Done - minHeap property is repected
        }
        // swap min child and parent
        min_val = arr[min_index];
        arr[min_index] = curr_val;
        arr[i] = min_val;
        i = min_index;
    }
}
