#include <bits/stdc++.h>
#define MAX_TREE_HT 256
using namespace std;

// to map each character its huffman value
map<char, string> codes;
// To store the frequency of character of the input data
map<char, int> freq;

// A Huffman tree node
struct Node {
    char data; // One of the input characters
    int freq; // Frequency of the character
    Node *left, *right; // Left and right child

    Node(char data, int freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

// utility function for the priority queue
struct compare {
    bool operator()(Node* l, Node* r)
    {
        return (l->freq > r->freq);
    }
};

// utility function to print characters along with
// there huffman value
void printCodes(struct Node* root, string str)
{
    if (!root)
        return;
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// utility function to store characters along with
// there huffman value in a hash table, here we
// have C++ STL map
void storeCodes(struct Node* root, string str)
{
    if (root == NULL)
        return;
    if (root->data != '$')
        codes[root->data] = str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

// STL priority queue to store heap tree, with respect
// to their heap root node value
priority_queue<Node*, vector<Node*>, compare>
    pq;

// function to build the Huffman tree and store it
// in minHeap
void HuffmanCodes(int size)
{
    struct Node *left, *right, *top;
    for (map<char, int>::iterator v = freq.begin();
         v != freq.end(); v++)
        pq.push(new Node(v->first, v->second));
    while (pq.size() != 1) {
        left = pq.top();
        pq.pop();
        right = pq.top();
        pq.pop();
        top = new Node('$',left->freq + right->freq);
        top->left = left;
        top->right = right;
        pq.push(top);
    }
    storeCodes(pq.top(), "");
}

// utility function to store map each character with its
// frequency in input string
void calcFreq(string str, int n)
{
    for (int i = 0; i < str.size(); i++)
        freq[str[i]]++;
}

// function iterates through the encoded string s
// if s[i]=='1' then move to node->right
// if s[i]=='0' then move to node->left
// if leaf node append the node->data to our output string
string decode_file(struct Node* root, string s)
{
    string ans = "";
    struct Node* curr = root;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0')
            curr = curr->left;
        else
            curr = curr->right;

        // reached leaf node
        if (curr->left == NULL and curr->right == NULL) {
            ans += curr->data;
            curr = root;
        }
    }
    // cout<<ans<<endl;
    return ans + '\0';
}
void comp_decomp( string str)

{
    string encodedString, decodedString;
    calcFreq(str, str.length());
    HuffmanCodes(str.length());
    cout << "Character With there Frequencies:\n";
    for (auto v = codes.begin(); v != codes.end(); v++)
        cout << v->first << ' ' << v->second << endl;

    for (auto i : str)
        encodedString += codes[i];

    cout << "\nEncoded Huffman data:\n"
         << encodedString << endl;

      // Function call
    decodedString = decode_file(pq.top(), encodedString);
    cout << "\nDecoded Huffman Data:\n"
         << decodedString << endl;
}
