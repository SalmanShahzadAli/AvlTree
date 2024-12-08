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
    int getHeight(Node *node)
    {
        return node ? node->height : 0;
    }

    int getBalanceFactor(Node *node)
    {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node *rightRotate(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    Node *leftRotate(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node *findMin(Node *node)
    {
        Node *current = node;
        while (current->left)
        {
            current = current->left;
        }
        return current;
    }

    Node *deleteNode(Node *node, int key)
    {
        if (!node)
            return node;

        // Perform standard BST deletion
        if (key < node->key)
        {
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = deleteNode(node->right, key);
        }
        else
        {
            // Node with only one child or no child
            if (!node->left || !node->right)
            {
                Node *temp = node->left ? node->left : node->right;
                if (!temp)
                {
                    temp = node;
                    node = nullptr;
                }
                else
                {
                    *node = *temp;
                }
                delete temp;
            }
            else
            {
                // Node with two children: get the inorder successor
                Node *temp = findMin(node->right);
                node->key = temp->key;
                node->right = deleteNode(node->right, temp->key);
            }
        }

        if (!node)
            return node;

        // Update height
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Rebalance the node
        int balance = getBalanceFactor(node);

        // Left Left Case
        if (balance > 1 && getBalanceFactor(node->left) >= 0)
        {
            return rightRotate(node);
        }

        // Left Right Case
        if (balance > 1 && getBalanceFactor(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Right Case
        if (balance < -1 && getBalanceFactor(node->right) <= 0)
        {
            return leftRotate(node);
        }

        // Right Left Case
        if (balance < -1 && getBalanceFactor(node->right) > 0)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorderTraversal(Node *node)
    {
        if (node)
        {
            inorderTraversal(node->left);
            cout << node->key << " ";
            inorderTraversal(node->right);
        }
    }

    void preorderTraversal(Node *node)
    {
        if (node)
        {
            cout << node->key << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }

public:
    void insert(int key)
    {
        root = insert(root, key);
    }

    Node *insert(Node *node, int key)
    {
        if (!node)
            return new Node(key);

        if (key < node->key)
        {
            node->left = insert(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = insert(node->right, key);
        }
        else
        {
            return node; // Duplicate keys not allowed
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        int balance = getBalanceFactor(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void deleteKey(int key)
    {
        root = deleteNode(root, key);
    }

    void inorderTraversal()
    {
        inorderTraversal(root);
        cout << endl;
    }

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
    avltree.insert(9);
    avltree.insert(5);
    avltree.insert(10);
    avltree.insert(0);
    avltree.insert(6);
    avltree.insert(11);
    avltree.insert(-1);
    avltree.insert(1);
    avltree.insert(2);

    cout << "Inorder traversal of the AVL tree is:\n";
    avltree.inorderTraversal();

    avltree.deleteKey(10);

    cout << "Inorder traversal after deleting 10:\n";
    avltree.inorderTraversal();

    cout << "Preorder traversal of the AVL tree is:\n";
    avltree.preorderTraversal();

    return 0;
}
