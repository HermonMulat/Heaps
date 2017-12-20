#include "pairingHeap.h"
#include <stdlib.h>
#include <vector>
#include <iostream>

#define MALLOC(size) (malloc(size))
#define FREE(pointer) (free(pointer))

using namespace std;

// prototype for an internal helper 
Node_t* combineNodes(vector<Node_t*> &paired);

PairingHeap::PairingHeap(){
    root = NULL;
    heap_size = 0;
}

PairingHeap::PairingHeap(int key){
    root = (Node_t *) MALLOC(sizeof(Node_t));
    if (root == NULL) exit(-1);
    root->next = NULL;
    root->prev = NULL;
    root->child = NULL;
    root->data = key;
    heap_size = 1;
}

void PairingHeap::insertKey(int key){
    PairingHeap p = PairingHeap(key);
    merge(p);
    heap_size += 1;
}

int PairingHeap::extractMin(){
    int min_val = root->data;
    int parity = 0;
    Node_t *current = root->child, *prev = NULL, *temp = NULL;
    vector<Node_t *> paired;
    PairingHeap h1 = PairingHeap(), h2 = PairingHeap();
    // pairing
    while (current){
        if (parity%2){
            h1.root = prev;
            h2.root = current;
            // disconnect prev and current nodes
            temp = current->next;
            prev->prev = NULL; prev->next = NULL;
            current->prev = NULL; current->next = NULL;
            // Pair two in a row and store resulting node to list
            h1.merge(h2);
            paired.push_back(h1.root);
            current = temp;
        }
        else{
            prev = current;
            current = prev->next;
        }
        parity++;
    }
    // if we have one more sibling node (happens if we have odd # of siblings)
    if (parity%2){
        paired.push_back(prev);
    }
    // back merge
    FREE(root);
    root = combineNodes(paired);
    heap_size --;
    return min_val;
}

Node_t* combineNodes(vector<Node_t*> &paired){
    if (paired.size() == 0){
        return NULL;
    }
    PairingHeap h1 = PairingHeap(), h2 = PairingHeap();
    int i = paired.size()-2;
    h1.root = paired[i+1]; // last element
    while (i>=0) {
        h2.root = paired[i];
        h1.merge(h2);
        i--;
    }
    return h1.root;
}

void PairingHeap::merge(PairingHeap p){
    if (p.root == NULL){
        return;
    }
    if (root == NULL){
        root = p.root;
        return;
    }

    Node_t *temp;
    if (p.getMin() > getMin()){
        temp = root->child;
        // insert new sub tree as left child
        root->child = p.root;
        p.root->prev = root;
        // make new left child point to previous left child
        p.root->next = temp;
        if (temp) temp->prev = root->child; // same as p.root
    }

    else{
        temp = p.root->child;
        p.root->child = root;
        root->prev = p.root;
        root->next = temp;
        if (temp) temp->prev = root;
        // now make p root the root of the whole tree
        root = p.root;
    }
}
