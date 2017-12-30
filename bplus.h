#ifndef bplus_h
#define bplus_h

#include <cstdlib>
#include <stdint.h>
#include <iostream>
#include <string.h>

#define NODE_SIZE 14
#define MALLOC(size) (malloc(size))
#define REALLOC(pointer,size) (realloc(pointer,size))
#define FREE(pointer) (free(pointer))

using namespace std;

typedef struct BplusNode
{
    uint64_t *keys;
    struct BplusNode *next;
    struct BplusNode *parent;
    struct BplusNode **pointers;
    int keyCount;
} BplusN_t;

class Bplus
{
    private:
        BplusN_t *root;
        uint64_t size;
        uint64_t nodeCount;
        void *redistributeLeaf(BplusN_t *full, BplusN_t *empty,uint64_t key);
        uint64_t split(BplusN_t *newNode, BplusN_t *parent, BplusN_t* right,uint64_t currKey);
        void insertOnFull(BplusN_t* fullLeaf, uint64_t key);
        BplusN_t* allocateBplusN(bool isLeaf);

    public:
        Bplus();
        ~Bplus();

        uint64_t getSize();
        BplusN_t *search(uint64_t key);
        void insert(uint64_t key);
        void remove(uint64_t key);
};

#endif
