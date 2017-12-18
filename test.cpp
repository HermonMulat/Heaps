#include "implicitHeap.h"
#include <iostream>

using namespace std;

int main(){
  MinHeap h(11);
  h.insertKey(3);
  h.insertKey(2);
  h.deleteKey(1);
  h.insertKey(15);
  h.insertKey(5);
  h.insertKey(4);
  h.insertKey(45);
  cout << h.pop() << " ";
  cout << h.getMin() << " ";
  h.decreaseKey(2, 1);
  cout << h.getMin() << "\n";
  return 0;
}
