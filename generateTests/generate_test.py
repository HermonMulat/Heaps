from heapq import heappush,heappop,heapify
import sys,random

'''
    Command:
        python generate_test.py <n> <infile> <outfile>

    This will generate a list of <n> operations, mix of insert and remove
    ops (roughly 1/3 remove and 2/3 insert). Thus the final heap will have the size
    of roughly 1/3 of n.

    Insert ops will have the format 'I <some number>'extractMin ops will have
    the formate 'D'.

    The <infile> will have 1 operation per line (either 'I <some number>'
    or 'D'.

    The <outfile> will have the final resulting heap, one number per line
    in increasing order (result of extracting min). The output put file is
    generated using python's implementation of a heap

    Note that this test is meant to check only correctness of sequencial heaps
'''

def generate(n):
    heap_q = []
    with open(sys.argv[2],"w+") as infile:
        while(n > 0):
            coin_flip = random.randint(0,2)
            if (coin_flip != 0):
                rand_num = random.randint(0,n)
                infile.write("I " + str(rand_num)+"\n")
                heappush(heap_q, rand_num)
            else:
                try:
                    heappop(heap_q)
                    infile.write("D\n")
                except IndexError:
                    rand_num = random.randint(0,n)
                    infile.write("I " + str(rand_num)+"\n")
                    heappush(heap_q, rand_num)
            n -= 1

    return heap_q

def main():
    n = int(sys.argv[1])
    with open(sys.argv[3],"w+") as outfile:
        heap_q = generate(n)
        for i in xrange(len(heap_q)):
            outfile.write(str(heappop(heap_q))+"\n")

if __name__ == '__main__':
    main()
