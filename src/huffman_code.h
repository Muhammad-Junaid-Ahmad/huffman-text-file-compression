// Huffman Coding in C
#ifndef HUFFMAN_CODE_H
#define HUFFMAN_CODE_H

#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HT 16

struct HCode
{
	short code[MAX_TREE_HT];
	short code_len;
};

struct MinHNode
{
	char item;
	unsigned freq;
	struct MinHNode *left, *right;
};

struct MinHeap
{
	unsigned size;
	unsigned capacity;
	struct MinHNode **array;
};

// Create nodes
struct MinHNode *newNode(char item, unsigned freq);
// Create min heap
struct MinHeap *createMinH(unsigned capacity);
// Function to swap
void swapMinHNode(struct MinHNode **a, struct MinHNode **b);
// Heapify
void minHeapify(struct MinHeap *minHeap, short idx);
// Check if size if 1
short checkSizeOne(struct MinHeap *minHeap);
// Extract min
struct MinHNode *extractMin(struct MinHeap *minHeap);
// Insertion function
void insertMinHeap(struct MinHeap *minHeap, struct MinHNode *minHeapNode);
// Min Head builder
void buildMinHeap(struct MinHeap *minHeap);
// checking is given node is leaf
short isLeaf(struct MinHNode *root);
struct MinHeap *createAndBuildMinHeap(char item[], short freq[], short size);
// Huffman tree builder
struct MinHNode *buildHuffmanTree(char item[], short freq[], short size);
// getting codes for all characters from huffman tree
void getHCodes(struct MinHNode *root, short top, struct HCode *codes);

#endif //HUFFMAN_CODE_H