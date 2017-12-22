#include "pairingHeap.h"
#include <vector>
#define MALLOC(size) (malloc(size))
#define REALLOC(pointer,size) (realloc(pointer,size))
#define FREE(pointer) (free(pointer))

using namespace std;

PairNode* allocateNode(uint64_t key){
    PairNode* n = (PairNode *) MALLOC(sizeof(PairNode));
    if (n == NULL) exit(-1);
    n->next = NULL;
    n->prev = NULL;
    n->child = NULL;
    n->data = key;
    return n;
}

PairingHeap::PairingHeap()
{
    root = NULL;
    heap_size = 0;
}

PairingHeap::PairingHeap(uint64_t key)
{
    root = allocateNode(key);
    heap_size = 1;
}

PairingHeap::~PairingHeap()
{
    PairNode** toFree = (PairNode**) MALLOC(heap_size*sizeof(PairNode*));
    toFree[0] = root;
    int index = 0, lastFree = 1;
    while (index < lastFree)
    {
        if (toFree[index])
        {
            if (toFree[index]->next)
            {
                toFree[lastFree] = toFree[index]->next;
                lastFree++;
            }
            if (toFree[index]->child)
            {
                toFree[lastFree] = toFree[index]->child;
                lastFree++;
            }
            FREE(toFree[index]);
            heap_size--;
        }
        index++;
    }
    FREE(toFree);
}

uint64_t PairingHeap::size()
{
    return heap_size;
}

uint64_t PairingHeap::getMin()
{
    if (root)
        return root->data;
    cout << "Heap is empty!" << endl;
    return -1;
}

void PairingHeap::insert(uint64_t key)
{
    PairNode *p = allocateNode(key);

    if (root == NULL)
        root = p;
    else
        merge(root,p);

    heap_size++;
}

uint64_t PairingHeap::extractMin()
{
    if (heap_size == 0)
    {
        cout << "Heap is empty!" << endl;
        return -1;
    }
    uint64_t minVal = root->data;
    PairNode *oldRoot = root;
    if (root->child != NULL)
        root = combineSiblings(root->child);
    else
        root = NULL;
    heap_size--;
    FREE(oldRoot);
    return minVal;
}

void PairingHeap::merge(PairNode *&first, PairNode* second)
{
    if (second == NULL)
        return;

    if (second->data < first->data)
    {
        first->prev = second;
        first->next = second->child;
        if (second->child)
            second->child->prev = first;
        second->child = first;
        first = second;
    }
    else
    {
        second->prev = first;
        second->next = first->child;
        if (first->child)
            first->child->prev = second;
        first->child = second;
    }
}

// A Helper method to double the size of the array
PairNode** doubleSize(PairNode **array, int &current){
    current *=2;
    PairNode **new_a = (PairNode**)REALLOC(array,current*sizeof(PairNode*));
    if (new_a == NULL) {
        cout << "Realloc failed" << endl;
        exit(-1);
    }
    return new_a;
}

PairNode *PairingHeap::combineSiblings(PairNode *firstSibling)
{
    if (firstSibling->next == NULL)
        return firstSibling;

    PairNode** siblings = (PairNode**) MALLOC(5*sizeof(PairNode*));
    // first count siblings, also disconnect siblings as we go
    int siblingCount = 0, arraySize = 5;
    while (firstSibling)
    {
        if (siblingCount == arraySize)
            siblings = doubleSize(siblings,arraySize);
        siblings[siblingCount] = firstSibling;
        firstSibling->prev->next = NULL;
        firstSibling->prev = NULL;
        firstSibling = firstSibling->next;
        siblingCount++;
    }
    // Forward merge
    for (int i=0; i<(siblingCount/2); i++)
        merge(siblings[2*i],siblings[2*i + 1]);
    // Backward merge
    for (int j=(siblingCount-1)/2; j>0; j--)
        merge(siblings[2*(j-1)],siblings[2*j]);
    return siblings[0];
}
