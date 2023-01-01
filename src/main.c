#include "huffman_encode.h"
#include "huffman_decode.h"

void print_help()
{
    printf("Usage: huff_compress [e|d] in_file out_file\n");
    printf("for e option in_file.txt out_file.bin\n");
    printf("for d option in_file.bin out_file.txt\n");
}

int main(int argc, char** argv)
{
    if (argc != 4)
    {
        printf("ERROR: required 3 arguments, %d are given.\n", argc-1);
        print_help();
    }

    if(argv[1][0] == 'e')
    {
        printf("Encoding %s ...\n", argv[2]);
        encodeFile(argv[2], argv[3]);
        printf("Encoded text written to %s\n", argv[3]);
    }
    else if(argv[1][0] == 'd')
    {
        printf("Decoding %s ...\n", argv[2]);
        decodeFile(argv[2], argv[3]);
        printf("Decoded text written to %s\n", argv[3]);
    }
    else
    {
        printf("ERROR: incorrect first argument\nRequired [e|d]. %s was given", argv[1]);
        print_help();
    }
}