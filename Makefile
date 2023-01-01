build: 
	gcc ./src/*.* -o huff_compress

test_h: 
	./huff_compress e ./test/sample.txt ./test/sample_encoded.bin
	./huff_compress d ./test/sample_encoded.bin ./test/sample_decoded.txt 