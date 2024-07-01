#include <iostream>
#include <algorithm>
#include <queue>
#include <chrono>
#include <ctime>
using namespace std;
using namespace std::chrono;

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

    void levelorder(Node *node)
    {
        if (node == nullptr)
            return;

        queue<Node *> q;
        q.push(node);

        while (!q.empty())
        {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++)
            {
                Node *node = q.front();
                q.pop();
                cout << node->data << " ";

                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            cout << endl;
        }
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

    void levelorder()
    {
        levelorder(root);
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
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = balanceFactor(node);
        if (balance > 1 && val < node->left->data)
            return rightRotate(node);

        if (balance < -1 && val > node->right->data)
            return leftRotate(node);
        if (balance > 1 && val > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

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

    void levelorder(Node *node)
    {
        if (node == nullptr)
            return;

        queue<Node *> q;
        q.push(node);

        while (!q.empty())
        {
            int levelSize = q.size();
            for (int i = 0; i < levelSize; i++)
            {
                Node *node = q.front();
                q.pop();
                cout << node->data << " ";

                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
            cout << endl;
        }
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

    void levelorder()
    {
        levelorder(root);
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
    AVLTree avl;

    srand(time(0));
    int *average = new int[30];
    int *nums = new int[30];

    for (int i = 0; i < 30; i++)
    {
        auto start = high_resolution_clock::now();

        // 1 - 100
        // for (int i = 1; i <= 100; i++)
        // {
        //     avl.insert(i);
        // }

        // 2-100, 1-99
        // for (int i = 2; i <= 100; i += 2)
        // {
        //     bst.insert(i);
        // }
        // for (int i = 1; i < 100; i += 2)
        // {
        //     bst.insert(i);
        // }

        // 1- 20
        for (int i = 0; i < 30; ++i)
        {
            int random = rand() % 20 + 1;
            nums[i] = random;
            avl.insert(random);
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        average[i] = duration.count();
        avl.inorder();

        cout << "Time taken by function: "
             << duration.count() << " microseconds" << endl;
    }

    int sum = 0;
    for (int i = 0; i < 30; i++)
    {
        sum += average[i];
    }
    double avg = static_cast<double>(sum) / 30;

    cout << "Average time taken by function: "
         << avg << " microseconds" << endl;

    // cout << "Level order BST: \n";
    // bst.levelorder();

    // cout << "Level order AVL: \n";
    // avl.inorder();
    // cout << endl;

    for (int i = 0; i < 30; i++) {
        cout << nums[i] << " ";
    }

    avl.levelorder();

    return 0;
}