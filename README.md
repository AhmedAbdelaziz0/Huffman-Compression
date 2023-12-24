# Huffman-Compression
An impelementation of huffman compression algorithm

## TODO
- write a function/class that takes text and prefix table, then compress it
    it should substitute each number with only single bit.
    should I use vector of bit? and collect every 8 bits into single character
    write all bits to a vector of bits, take every 8 bits and make a char, 
    save it to a string of characters then write that string to a file
- write save string to file function save(file_path, data);
- save prefix table to the output file
- save the compressed dat to the file
- read the compressed data from the file
- make an array of bits from the compressed data
- match table with compressed text to decompress
