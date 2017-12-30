#include "bplus.h"

int binarySearch(uint64_t *array, uint64_t key, int high){
    // return index of exact match, or closest smaller value
    int low = 0, mid = high/2;
    while ((high - low) > -1)
    {
        if (array[mid] == key)
            return mid;
        else if (array[mid] > key)
            high = mid-1;
        else
            low = mid+1;
        mid = (high + low)/2;
    }
    if (high == -1)
        return -1;
    return mid;
}

BplusN_t* Bplus::allocateBplusN(bool isLeaf)
{
    BplusN_t * node = (BplusN_t *) MALLOC(sizeof(BplusN_t));
    node->keys = (uint64_t *) MALLOC(NODE_SIZE*sizeof(uint64_t));
    for (int i=0; i<NODE_SIZE; i++)
        node->keys[i] = -1;
    node->next = NULL;
    node->parent = NULL;
    node->keyCount = 0;
    if (not isLeaf)
        node->pointers = (BplusN_t **)MALLOC((NODE_SIZE+1)*sizeof(BplusN_t*));
    else
        node->pointers = NULL;
    nodeCount++;
    return node;
}

Bplus::Bplus(){
    root = NULL;
    size = 0;
    nodeCount = 0;
}

Bplus::~Bplus(){
    BplusN_t** toFree = (BplusN_t **) MALLOC(nodeCount*sizeof(BplusN_t*));
    toFree[0] = root;
    int index = 0, lastFree = 1;
    while (nodeCount)
    {
        if (toFree[index])
        {
            if (toFree[index]->pointers != NULL)
            {
                for (int i=0; i<=toFree[index]->keyCount; i++)
                {
                    toFree[lastFree] = toFree[index]->pointers[i];
                    lastFree++;
                }
                FREE(toFree[index]->pointers);
            }
            FREE(toFree[index]->keys);
            FREE(toFree[index]);
            nodeCount--;
        }
        index++;
    }
    FREE(toFree);
    cout << "Remaining nodes -- " << nodeCount << endl;
}

uint64_t Bplus::getSize()
{
    return size;
}

BplusN_t *Bplus::search(uint64_t key)
{
    if (root == NULL)
        return NULL;

    BplusN_t *current = root;
    int index = 0;
    while(current->pointers!=NULL)
    {
        index = binarySearch(current->keys,key,current->keyCount-1)+1;
        current = current->pointers[index];
    }
    return current;
}

void *Bplus::redistributeLeaf(BplusN_t *full, BplusN_t *empty,uint64_t key)
{
    empty->next = full->next;
    full->next = empty;
    // redistribute values between the old and new leaf nodes
    int index = binarySearch(full->keys,key,NODE_SIZE-1)+1;
    int half = NODE_SIZE/2;
    if (index < half)
    {
        memcpy(empty->keys, full->keys+(half - 1),(half + 1)*sizeof(uint64_t));
        memmove(full->keys+(index+1),full->keys+index,(half-index-1)*sizeof(uint64_t));
        full->keys[index] = key;
    }
    else
    {
        memcpy(empty->keys,full->keys+half,(index-half)*sizeof(uint64_t));
        empty->keys[index-half] = key;
        memcpy(empty->keys+(index - half + 1),full->keys+(index),(NODE_SIZE-index)*sizeof(uint64_t));
    }
    full->keyCount = half;
    empty->keyCount = half + 1;
}

void Bplus::insert(uint64_t key)
{
    BplusN_t *leafNode = search(key);
    if (leafNode == NULL)
    {
        root = allocateBplusN(true);
        root->keys[0] = key;
        root->keyCount++;
    }
    else if (leafNode->keyCount < NODE_SIZE)
    {
        int index = leafNode->keyCount-1;
        while (index >= 0 && leafNode->keys[index] > key)
        {
            leafNode->keys[index+1] = leafNode->keys[index];
            index--;
        }
        leafNode->keys[index+1] = key;
        leafNode->keyCount++;
    }
    else
    {
        insertOnFull(leafNode,key);
    }
}

uint64_t Bplus::split(BplusN_t *newNode, BplusN_t *parent, BplusN_t* right,uint64_t currKey)
{
    int index = binarySearch(parent->keys,currKey,NODE_SIZE-1)+1;
    int half = NODE_SIZE/2;
    uint64_t splitKey;
    newNode->next = parent->next;
    parent->next = newNode->next;
    if (index < half)
    {
        splitKey = parent->keys[half-1];
        memcpy(newNode->keys, parent->keys+half,half*sizeof(uint64_t));
        memcpy(newNode->pointers, parent->pointers+half,(half+1)*sizeof(BplusN_t*));
        memmove(parent->keys+(index+1),parent->keys+index,(half-index-1)*sizeof(uint64_t));
        memmove(parent->pointers+(index+2),parent->pointers+(index+1),(half-index-1)*sizeof(BplusN_t*));
        parent->keys[index] = currKey;
        parent->pointers[index+1] = right;
        right->parent = parent;
    }
    else if (index > half)
    {
        splitKey = parent->keys[half];
        memcpy(newNode->keys,parent->keys+half+1,(index-half-1)*sizeof(uint64_t));
        memcpy(newNode->pointers,parent->pointers+half+1,(index-half)*sizeof(BplusN_t*));
        newNode->keys[index-half-1] = currKey;
        newNode->pointers[index-half] = right;
        memcpy(newNode->keys+index-half,parent->keys+index,(NODE_SIZE-index)*sizeof(uint64_t));
        memcpy(newNode->pointers+index-half+1,parent->pointers+index+1,(NODE_SIZE-index)*sizeof(BplusN_t*));
    }
    else
    {
        splitKey = currKey;
        memcpy(newNode->keys, parent->keys+half, half*sizeof(uint64_t));
        memcpy(newNode->pointers+1, parent->pointers+half+1,half*sizeof(BplusN_t*));
        newNode->pointers[0] = right;
    }
    // correct parent pointers
    for (int i=0; i<=half; i++)
        newNode->pointers[i]->parent = newNode;

    // correct keyCount, and next pointers
    newNode->keyCount = half;
    parent->keyCount = half;
    newNode->next = parent->next;
    parent->next = newNode;
    return splitKey;
}

void Bplus::insertOnFull(BplusN_t* fullLeaf, uint64_t key)
{
    BplusN_t *newNode = allocateBplusN(true);
    redistributeLeaf(fullLeaf,newNode,key);
    BplusN_t *parent = fullLeaf->parent,*prevParent=fullLeaf,*right = newNode;
    uint64_t currKey = right->keys[0];
    while( parent != NULL && parent->keyCount == NODE_SIZE )
    {
        newNode = allocateBplusN(false);
        currKey = split(newNode,parent,right,currKey);
        prevParent = parent;
        parent = parent->parent;
        right = newNode;
    }
    // Final step
    if (parent == NULL)
    {
        parent = allocateBplusN(false);
        parent->keys[0] = currKey;
        parent->pointers[0] = prevParent;
        prevParent->parent = parent;
        parent->pointers[1] = right;
        right->parent = parent;
        parent->keyCount++;
        root = parent;
    }
    else
    {
        int index = binarySearch(parent->keys,currKey,parent->keyCount-1)+1;
        int i = parent->keyCount-1;
        while (i >= index)
        {
            parent->keys[i+1] = parent->keys[i];
            parent->pointers[i+2] = parent->pointers[i+1];
            i--;
        }
        parent->keys[index] = currKey;
        parent->keyCount++;
        parent->pointers[index+1] = right;
        right->parent = parent;
    }
}

void Bplus::remove(uint64_t key)
{

}
