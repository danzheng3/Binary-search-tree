#include "hbt.h"
#include <stdlib.h>
#include <stdio.h>
#include "pa3.h"

Tnode* insert(Tnode *root, int key);
Tnode* deleteNode(Tnode* root, int key);
Tnode* getMinNode(Tnode* node);
Tnode* createNode(int key);
Tnode* getMaxNode(Tnode* node);

Tnode* insert(Tnode* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }

    if (key <= root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }

    // Update the balance factor of the current node
    root->balance = getHeight(root->left) - getHeight(root->right);

    // Rebalance the tree if necessary
    return balanceTree(root);
}

Tnode* findMinNode(Tnode* node) {
    if (node->left == NULL) {
        return node;
    }
    return findMinNode(node->left);
}


// Function to find the node with the maximum key in a subtree
Tnode* findMaxNode(Tnode* node) {
    if (node->right == NULL) {
        return node;
    }
    return findMaxNode(node->right);
}


// Function to perform the deletion of a node with the given key in the AVL tree
Tnode* deleteNode(Tnode* root, int key) {
    if (root == NULL) {
        return root; // Key not found, return the current root
    }

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Key found, perform deletion

        if (root->left == NULL || root->right == NULL) {
            // Node with one child or no child
            Tnode* temp = root->left ? root->left : root->right;

            free(root);
            return temp;
        } else {
            // Node with two children
            Tnode* predecessor = findMaxNode(root->left);
            root->key = predecessor->key;
            root->left = deleteNode(root->left, predecessor->key);
        }
    }

    root->balance = getHeight(root->left) - getHeight(root->right);

    // Rebalance the tree if necessary
    return balanceTree(root);
}




// Function to create a new node with the given key
Tnode* createNode(int key) {
    Tnode* newNode = (Tnode*)malloc(sizeof(Tnode));
    if (newNode == NULL) {
        exit(EXIT_FAILURE);
    }

    newNode->key = key;
    newNode->balance = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
