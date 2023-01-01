#ifndef HUFFMAN_CODE_C
#define HUFFMAN_CODE_C


#include "huffman_code.h"

// Create nodes
struct MinHNode *newNode(char item, unsigned freq)
{
	struct MinHNode *temp = (struct MinHNode *)malloc(sizeof(struct MinHNode));

	temp->left = temp->right = NULL;
	temp->item = item;
	temp->freq = freq;

	return temp;
}

// Create min heap
struct MinHeap *createMinH(unsigned capacity)
{
	struct MinHeap *minHeap = (struct MinHeap *)malloc(sizeof(struct MinHeap));

	minHeap->size = 0;
	minHeap->capacity = capacity;

	minHeap->array = (struct MinHNode **)malloc(minHeap->capacity * sizeof(struct MinHNode *));
	return minHeap;
}


// Function to swap
void swapMinHNode(struct MinHNode **a, struct MinHNode **b)
{
	struct MinHNode *t = *a;
	*a = *b;
	*b = t;
}

// Heapify
void minHeapify(struct MinHeap *minHeap, short idx)
{
	short smallest = idx;
	short left = 2 * idx + 1;
	short right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != idx)
	{
		swapMinHNode(&minHeap->array[smallest], &minHeap->array[idx]);
		minHeapify(minHeap, smallest);
	}
}

// Check if size if 1
short checkSizeOne(struct MinHeap *minHeap)
{
	return (minHeap->size == 1);
}

// Extract min
struct MinHNode *extractMin(struct MinHeap *minHeap)
{
	struct MinHNode *temp = minHeap->array[0];
	minHeap->array[0] = minHeap->array[minHeap->size - 1];

	--minHeap->size;
	minHeapify(minHeap, 0);

	return temp;
}

// Insertion function
void insertMinHeap(struct MinHeap *minHeap, struct MinHNode *minHeapNode)
{
	++minHeap->size;
	short i = minHeap->size - 1;

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
	{
		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	minHeap->array[i] = minHeapNode;
}

void buildMinHeap(struct MinHeap *minHeap)
{
	short n = minHeap->size - 1;
	
	for (short i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);
}

short isLeaf(struct MinHNode *root)
{
	return !(root->left) && !(root->right);
}

struct MinHeap *createAndBuildMinHeap(char item[], short freq[], short size)
{
	struct MinHeap *minHeap = createMinH(size);

	for (short i = 0; i < size; ++i)
		minHeap->array[i] = newNode(item[i], freq[i]);

	minHeap->size = size;
	buildMinHeap(minHeap);

	return minHeap;
}

struct MinHNode *buildHuffmanTree(char item[], short freq[], short size)
{
	struct MinHNode *left, *right, *top;
	struct MinHeap *minHeap = createAndBuildMinHeap(item, freq, size);

	while (!checkSizeOne(minHeap))
	{
		left = extractMin(minHeap);
		right = extractMin(minHeap);

		top = newNode('$', left->freq + right->freq);

		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}
	return extractMin(minHeap);
}


void getHCodes(struct MinHNode *root, short top, struct HCode *codes)
{   
    static short arr[MAX_TREE_HT];
    
	if (root->left)
	{
		arr[top] = 0;
		getHCodes(root->left, top + 1, codes);
	}
	if (root->right)
	{
		arr[top] = 1;
		getHCodes(root->right, top + 1, codes);
	}
	if (isLeaf(root))
	{

		for (short i = 0; i < top; i++)
		{
			codes[root->item].code[i] = arr[i];
		}
		codes[root->item].code_len = top;
	}
}


#endif //HUFFMAN_CODE_C