#ifndef HUFFMAN_ENCODE_H
#define HUFFMAN_ENCODE_H

#include "huffman_code.h"

#define MAX_CHAR 128

void printArray(short characters[], short n)
{
	short i;
	for (i = 0; i < n; ++i)
		printf("%d", characters[i]);

	printf("\n");
}

short encodeFile(char *in_file, char *out_file)
{

	short char_count[MAX_CHAR] = {0};
	short num_unique_chars = 0;
	long int in_file_len = 0;

	FILE *fin = fopen(in_file, "r");
	if (fin == NULL)
	{
		printf("file can't be opened \n");
		exit;
	}

	char ch;
	while ((ch = fgetc(fin)) != EOF)
	{
		num_unique_chars += (char_count[ch] == 0 ? 1 : 0);
		char_count[ch]++;
	}

	char *characters = (char *)malloc(num_unique_chars);
	short *freqs = (short *)malloc(sizeof(short) * num_unique_chars);
	short j = 0;

	for (short i = 0; i < MAX_CHAR; i++)
	{
		if (char_count[i])
		{
			characters[j] = i;
			freqs[j] = char_count[i];
			j++;
		}
	}

	struct HCode huff_codes[MAX_CHAR] = {0};
	struct MinHNode *root = buildHuffmanTree(characters, freqs, num_unique_chars);

	getHCodes(root, 0, huff_codes);

	short bits_to_write = 0;

	FILE *fout = fopen(out_file, "wb");
	fwrite(&num_unique_chars, sizeof(short), 1, fout);

	printf("Num Unique Characters: %d\n", num_unique_chars);

	printf("#  Char: (char_count) Code\n");

	// Writing huffman code information in file
	for (short i = 0; i < num_unique_chars; i++)
	{
		bits_to_write += huff_codes[characters[i]].code_len * freqs[i];
		fwrite(&characters[i], sizeof(char), 1, fout);
		fwrite(&freqs[i], sizeof(short), 1, fout);

		printf("%-3d %3c: (%d) ", i, characters[i], freqs[i]);
		printArray(huff_codes[characters[i]].code, huff_codes[characters[i]].code_len);
	}
	fwrite(&bits_to_write, sizeof(short), 1, fout);

	char cw=0;
	j = 0;
	fseek(fin, 0L, SEEK_SET);
	while ((ch = fgetc(fin)) != EOF)
	{
		in_file_len++;
		for (short i = 0; i < huff_codes[ch].code_len; i++)
		{
			cw |= huff_codes[ch].code[i] << 7 - j;
			j++;
			if (j != 0 && j % 8 == 0)
			{
				fputc(cw, fout);
				j = 0;
				cw = 0;
			}
		}
	}

	fputc(cw, fout);
	fclose(fout);
	fclose(fin);

	printf("Original size: %ld Bytes\n", in_file_len);
	printf("Compressed size: %d Bytes\n", ((bits_to_write + 7) / 8));
}

#endif // HUFFMAN_ENCODE_H