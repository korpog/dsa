#include <iostream>
#include <algorithm>
using namespace std;

class BST
{
private:
    struct Node
    {
        int data;
        Node *left;
        Node *right;
        Node(int val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node *root;

    Node *insert(Node *node, int val)
    {
        if (node == nullptr)
            return new Node(val);
        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        return node;
    }

    void inorder(Node *node)
    {
        if (node == nullptr)
            return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    Node *search(Node *node, int val)
    {
        if (node == nullptr || node->data == val)
            return node;
        if (val < node->data)
            return search(node->left, val);
        return search(node->right, val);
    }

public:
    BST() : root(nullptr) {}

    void insert(int val)
    {
        root = insert(root, val);
    }

    void inorder()
    {
        inorder(root);
        cout << endl;
    }

    bool search(int val)
    {
        return search(root, val) != nullptr;
    }
};

class AVLTree
{
private:
    struct Node
    {
        int data;
        Node *left;
        Node *right;
        int height;
        Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node *root;

    int height(Node *N)
    {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    int balanceFactor(Node *N)
    {
        if (N == nullptr)
            return 0;
        return height(N->left) - height(N->right);
    }

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node *insert(Node *node, int val)
    {
        if (node == nullptr)
            return new Node(val);
        if (val < node->data)
            node->left = insert(node->left, val);
        else if (val > node->data)
            node->right = insert(node->right, val);
        else
            return node; // Duplicate values not allowed

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = balanceFactor(node);

        // Left Left Case
        if (balance > 1 && val < node->left->data)
            return rightRotate(node);

        // Right Right Case
        if (balance < -1 && val > node->right->data)
            return leftRotate(node);

        // Left Right Case
        if (balance > 1 && val > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && val < node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(Node *node)
    {
        if (node == nullptr)
            return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    Node *search(Node *node, int val)
    {
        if (node == nullptr || node->data == val)
            return node;
        if (val < node->data)
            return search(node->left, val);
        return search(node->right, val);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(int val)
    {
        root = insert(root, val);
    }

    void inorder()
    {
        inorder(root);
        cout << endl;
    }

    bool search(int val)
    {
        return search(root, val) != nullptr;
    }
};

int main()
{
    BST bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(1);
    bst.insert(9);

    cout << "Inorder traversal: ";
    bst.inorder();

    cout << "Search 7: " << (bst.search(7) ? "Found" : "Not Found") << endl;
    cout << "Search 6: " << (bst.search(6) ? "Found" : "Not Found") << endl;

    // AVLTree avl;
    // avl.insert(10);
    // avl.insert(20);
    // avl.insert(30);
    // avl.insert(40);
    // avl.insert(50);
    // avl.insert(25);

    // cout << "Inorder traversal of AVL tree: ";
    // avl.inorder();

    // cout << "Search 30: " << (avl.search(30) ? "Found" : "Not Found") << endl;
    // cout << "Search 35: " << (avl.search(35) ? "Found" : "Not Found") << endl;

    return 0;
}