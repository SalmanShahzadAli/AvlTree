#include <iostream>
using namespace std;

class Node
{
public:
    int key;
    Node *left;
    Node *right;
    int height;

    Node(int key)
    {
        this->key = key;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AvlTree
{
public:
    Node *root;

    AvlTree()
    {
        root = nullptr;
    }

private:
    // Get the height of a node
    int getHeight(Node *node)
    {
        return node ? node->height : 0;
    }

    // Get the balance factor of a node
    int getBalanceFactor(Node *node)
    {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Right rotate
    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    // Left rotate
    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

public:
    // Insert a node into the AVL tree
    Node *insert(Node *node, int key)
    {
        // Perform normal BST insertion
        if (!node)
            return new Node(key);

        if (key < node->key)
            node->left = insert(node->left, key);
        else if (key > node->key)
            node->right = insert(node->right, key);
        else
            return node; // Duplicate keys not allowed

        // Update height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Get the balance factor
        int bf = getBalanceFactor(node);

        // Balance the tree
        // Left Left Case
        if (bf > 1 && key < node->left->key)
            return rightRotate(node);

        // Right Right Case
        if (bf < -1 && key > node->right->key)
            return leftRotate(node);

        // Left Right Case
        if (bf > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left Case
        if (bf < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Wrapper function to insert a key
    void insert(int key)
    {
        root = insert(root, key);
    }

    // Inorder traversal
    void inorderTraversal(Node *node)
    {
        if (node)
        {
            inorderTraversal(node->left);
            cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }

    // Preorder traversal
    void preorderTraversal(Node *node)
    {
        if (node)
        {
            cout << node->key << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }

    // Public method for inorder traversal
    void inorderTraversal()
    {
        inorderTraversal(root);
        cout << endl;
    }

    // Public method for preorder traversal
    void preorderTraversal()
    {
        preorderTraversal(root);
        cout << endl;
    }
};

int main()
{
    AvlTree avltree;

    // Insert nodes
    avltree.insert(1);
    avltree.insert(2);
    avltree.insert(4);
    avltree.insert(5);
    avltree.insert(6);
    avltree.insert(3);

    // Print preorder traversal
    cout << "Preorder traversal of the AVL tree is:\n";
    avltree.preorderTraversal();

    // Print inorder traversal
    cout << "Inorder traversal of the AVL tree is:\n";
    avltree.inorderTraversal();

    return 0;
}
