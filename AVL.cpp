#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class avl_node
{
public:
    string word, meaning;
    avl_node *left;
    avl_node *right;
    int height;
    avl_node(string w, string m) : word(w), meaning(m), left(NULL), right(NULL), height(1) {}
    friend class AVL;
};

class AVL
{
    avl_node *root;

public:
    AVL();
    void insert(string, string);
    avl_node* create(avl_node *, avl_node *);
    void display();
    void inorder(avl_node *);
    int height(avl_node *);
    int diff(avl_node *);
    avl_node* getRoot();
    avl_node* LL(avl_node *);
    avl_node* RR(avl_node *);
    avl_node* LR(avl_node *);
    avl_node* RL(avl_node *);
    avl_node* balance(avl_node *);
};

AVL::AVL()
{
    root = NULL;
}

int AVL::height(avl_node *node)
{
    if (!node)
        return 0;
    return node->height;
}

int AVL::diff(avl_node *node)
{
    if (!node)
        return 0;
    return height(node->left) - height(node->right);
}

avl_node* AVL::LL(avl_node *node)
{
    avl_node *temp = node->left;
    node->left = temp->right;
    temp->right = node;

    // Update heights
    node->height = max(height(node->left), height(node->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;

    return temp;
}

avl_node* AVL::RR(avl_node *node)
{
    avl_node *temp = node->right;
    node->right = temp->left;
    temp->left = node;

    // Update heights
    node->height = max(height(node->left), height(node->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;

    return temp;
}

avl_node* AVL::LR(avl_node *node)
{
    node->left = RR(node->left);
    return LL(node);
}

avl_node* AVL::RL(avl_node *node)
{
    node->right = LL(node->right);
    return RR(node);
}

avl_node* AVL::balance(avl_node *node)
{
    if (!node) return node;

    // Calculate balance factor
    int balanceFactor = diff(node);

    // Left Heavy (LL or LR)
    if (balanceFactor > 1)
    {
        if (diff(node->left) >= 0) // LL Case
            return LL(node);
        else // LR Case
            return LR(node);
    }
    // Right Heavy (RR or RL)
    else if (balanceFactor < -1)
    {
        if (diff(node->right) <= 0) // RR Case
            return RR(node);
        else // RL Case
            return RL(node);
    }

    // Update height before returning
    node->height = max(height(node->left), height(node->right)) + 1;

    return node;
}

avl_node* AVL::create(avl_node *node, avl_node *temp)
{
    if (!node)
        return temp;
    
    if (temp->word < node->word)
        node->left = create(node->left, temp);
    else if (temp->word > node->word)
        node->right = create(node->right, temp);
    else
        return node;  // Duplicate words are ignored

    // Update height before balancing
    node->height = max(height(node->left), height(node->right)) + 1;

    // Balance the node
    return balance(node);
}

void AVL::insert(string word, string meaning)
{
    avl_node *temp = new avl_node(word, meaning);
    root = create(root, temp);
}

void AVL::inorder(avl_node *node)
{
    if (node)
    {
        inorder(node->left);
        cout << node->word << " : " << node->meaning;
        cout << " (Balance Factor: " << diff(node) << ")" << endl;
        inorder(node->right);
    }
}

void AVL::display()
{
    inorder(root);
}

avl_node* AVL::getRoot()
{
    return root;
}

int main()
{
    AVL dictionary;
    char ch;
    do
    {
        string word, meaning;
        cout << "Enter word: ";
        cin >> word;
        cin.ignore();
        cout << "Enter meaning: ";
        getline(cin, meaning);
        dictionary.insert(word, meaning);
        cout << "Do you want to enter more words? (y/n): ";
        cin >> ch;
    } while (ch == 'y');

    cout << "\nDictionary (Inorder Traversal with Balance Factor):\n";
    dictionary.display();
    
    cout << "\nBalance factor of root: " << dictionary.diff(dictionary.getRoot()) << endl;

    return 0;
}
