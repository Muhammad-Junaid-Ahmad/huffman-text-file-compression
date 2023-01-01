# Huffman Compression of text files
This repository contains code that can encode a given .txt file into huffman code for compression and stores the data into a .bin file.

First build the huff_compress binary using `make build`.

Then you can compress a given file using the huffman coding algorithm. The output binary file contains all the information needed to decode to get the original file.

For Encoding: `huff_compress e in.txt out.bin`

For Decoding: `huff_compress d in.bin out.txt`

You can test the binary with the given `sample.txt` file inside `./test/` directory using `make test_h`