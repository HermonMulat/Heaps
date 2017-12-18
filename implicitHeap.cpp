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

int MinHeap::pop(){
  if (heap_size == 0){
    return INT_MAX;
  }

  int min_val = arr[0];
  arr[0] = arr[heap_size - 1];
  heap_size--;
  siftDown(0);
  return min_val;
}

void MinHeap::decreaseKey(int index, int new_val){
  arr[index] = new_val;
  siftUp(index);
}

void MinHeap::increaseKey(int index, int new_val){
  arr[index] = new_val;
  siftDown(index);
}


void MinHeap::insertKey(int key){
  if (heap_size == capacity){ // if we want, we could realloc here
    cout << "Heap capacity exceeded" << '\n';
    return;
  }
  heap_size++;
  arr[heap_size - 1] = key;
  siftUp(heap_size - 1);
}

void MinHeap::deleteKey(int index){
  arr[index] = arr[heap_size-1];
  heap_size--;
  siftDown(index);
}

void MinHeap::siftUp(int index){
  int parent = getParent(index);
  int curr_val = arr[index];

  while (index!=0 &&  arr[parent] > curr_val){
    arr[index] = arr[parent];
    arr[parent] = curr_val;
    index  = parent;
    parent = getParent(index);
  }

}

void MinHeap::siftDown(int index){
  int curr_val = arr[index];
  int min_val = 0,min_index = 0;
  while(index<heap_size){
    // First indentify if either child is smaller (and the index)
    min_index = index;
    if (arr[min_index] > arr[getLeftChild(index)]){
      min_index = getLeftChild(index);
    }
    if (arr[min_index] > arr[getRightChild(index)]){
      min_index = getRightChild(index);
    }
    if (min_index == index){
      return; // Done - minHeap property is repected
    }
    // swap min child and parent
    min_val = arr[min_index];
    arr[min_index] = curr_val;
    arr[index] = min_val;
    index = min_index;
  }
}
