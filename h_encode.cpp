#include <iostream>
#include <queue>
#include <unordered_map>
using namespace std;

struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Comparator for min-heap
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Recursive function to print codes
void printCodes(Node* root, string code) {
    if (!root) return;
    if (root->ch != '$') cout << root->ch << ": " << code << "\n";
    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}

void huffmanCoding(unordered_map<char, int> freqMap) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    for (auto& pair : freqMap)
        pq.push(new Node(pair.first, pair.second));

    while (pq.size() > 1) {
        Node* l = pq.top(); pq.pop();
        Node* r = pq.top(); pq.pop();
        Node* merged = new Node('$', l->freq + r->freq);
        merged->left = l;
        merged->right = r;
        pq.push(merged);
    }

    Node* root = pq.top();
    cout << "Huffman Codes:\n";
    printCodes(root, "");
}

int main() {
    unordered_map<char, int> freqMap;
    int n;
    cout << "Enter number of characters: ";
    cin >> n;
    cout << "Enter each character and its frequency:\n";
    for (int i = 0; i < n; ++i) {
        char c;
        int f;
        cin >> c >> f;
        freqMap[c] = f;
    }

    huffmanCoding(freqMap);
    return 0;
}
