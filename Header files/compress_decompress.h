#ifndef _compress_decompress_
#define _compress_decompress_

#include <bits/stdc++.h>
#define MAX_TREE_HT 256

using namespace std;

// A Huffman tree node
struct MinHeapNode {
    char data; // One of the input characters
    int freq; // Frequency of the character
    MinHeapNode *left, *right; // Left and right child

    MinHeapNode(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

// utility function for the priority queue
struct compare {
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};

void printCodes(struct MinHeapNode* root, string str);
void storeCodes(struct MinHeapNode* root, string str);
void HuffmanCodes(int size);
void calcFreq(string str, int n);
string decode_file(struct MinHeapNode* root, string s);

#endif
