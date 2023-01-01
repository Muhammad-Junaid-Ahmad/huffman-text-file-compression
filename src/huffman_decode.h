#ifndef HUFFMAN_DECODE_H
#define HUFFMAN_DECODE_H

#include "huffman_code.h"


short decodeFile(char * in_file, char* out_file)
{
	
    short num_unique_chars;
	short bits_to_decode;

    FILE *fin = fopen(in_file, "rb");
    FILE *fout = fopen(out_file, "w");

	fread(&num_unique_chars, sizeof(short), 1, fin);
	
    char *arr = (char *)malloc(num_unique_chars);
	short *freq = (short *)malloc(sizeof(short) * num_unique_chars);

    for (short i =0; i< num_unique_chars;i++)
	{
		fread(&arr[i], sizeof(char), 1, fin);
		fread(&freq[i], sizeof(short), 1, fin);
		
	}

    fread(&bits_to_decode, sizeof(short), 1, fin);
	
	
	struct MinHNode *root = buildHuffmanTree(arr, freq, num_unique_chars);

    
    struct MinHNode* cur = root;
    long int chars_written = 0;

    for (char code = fgetc(fin); !feof(fin); code = fgetc(fin))
    {
        for (short i=0;i<8 && bits_to_decode;i++)
        {	
			bits_to_decode--;
            cur = (code & (0b10000000 >>  i))? cur->right : cur->left;
            
            if(isLeaf(cur))
            {
                fputc(cur->item, fout);
                cur = root;
                chars_written++;
            }
        }
    }

    printf("%ld Bytes decoded\n", chars_written);
    fclose(fout);
    fclose(fin);
}

#endif //HUFFMAN_DECODE_H