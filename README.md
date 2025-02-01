# Huffman Algorithm Implementation in C++

## Overview
This project implements Huffman coding, a lossless data compression algorithm, using C++. The algorithm calculates the frequency of characters, builds a Huffman tree, and generates binary codes for efficient encoding and decoding of data.

## Features
- **Character Frequency Calculation**: Counts the occurrences of characters in the input data.
- **Huffman Tree Construction**: Builds an optimal binary tree for encoding based on frequency.
- **Encoding and Compression**: Converts input data into a compressed binary format.
- **Decoding and Decompression**: Reconstructs the original data from the compressed format.
- **Binary File Handling**: Reads and writes compressed files for efficient storage.

## File Descriptions
### Main Implementation File
This file contains the core implementation of Huffman coding:
- **`cTnode` Class**: Represents tree nodes for the Huffman tree.
- **`cnode` Class**: Represents linked list nodes for managing frequency and encoding.
- **`clist` Class**: Implements a linked list to store and manipulate nodes.
- **`Frequency()`**: Computes the frequency of characters in the input data.
- **`Huffman_Tree()`**: Constructs the Huffman tree using a sorted linked list.
- **`Huffman_Code()`**: Generates binary codes for each character.
- **`compress()`**: Encodes data into a binary format.
- **`Decompress()`**: Decodes compressed data back to its original form.
- **File handling** for reading input files and storing compressed output.

## How to Use
1. **Compile the program** using a C++ compiler (e.g., `g++ huffman.cpp -o huffman`).
2. **Run the executable** and provide an input file for compression.
3. **Compressed output** will be stored in a binary file.
4. **Decompress the file** to retrieve the original data.

## Example Usage
```cpp
int main() {
    clist L, Encoded;
    cTnode *ptop = NULL;
    ifstream data("INPUT.jpeg", ifstream::binary);
    ofstream compressedFile("COMP_FILE.jpeg", ofstream::binary);
    
    // Read input, compute frequencies, build Huffman tree
    // Compress and store output
    
    return 0;
}
```

## Dependencies
- Standard C++ libraries (`iostream`, `fstream`, `string`)

## Future Improvements
- Improve memory management to prevent leaks.
- Add support for text-based input/output.
- Implement adaptive Huffman coding for dynamic data.

## Author
AmrKhaled @2024 - Implemented Huffman coding algorithm in C++ for efficient data compression.

