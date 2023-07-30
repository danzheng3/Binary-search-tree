#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa3.h"

Tnode* rotateRight(Tnode* node);
Tnode* rotateLeft(Tnode* node);
Tnode* balanceTree(Tnode* node);
int getHeight(Tnode* node);
int updateBalance(Tnode* node);
Tnode* updateBalancesAndBalanceTree(Tnode* node);


// Function to perform a right rotation on the given node
Tnode* rotateRight(Tnode* node) {
    Tnode* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    return newRoot;
}

// Function to perform a left rotation on the given node
Tnode* rotateLeft(Tnode* node) {
    Tnode* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    return newRoot;
}


// Function to balance the AVL tree after insertion or deletion
Tnode* balanceTree(Tnode* node) {
    if (node->balance < -1) {
        if (node->right->balance > 0) {
            node->right = rotateRight(node->right);
        }
        node = rotateLeft(node);
    } else if (node->balance > 1) {
        if (node->left->balance < 0) {
            node->left = rotateLeft(node->left);
        }
        node = rotateRight(node);
    }
    return node;
}

// Function to find the height of a node
int getHeight(Tnode* node) {
    if (node == NULL) {
        return 0;
    }
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int updateBalance(Tnode* node) {
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    node->balance = leftHeight - rightHeight;
    return node->balance;
}

// Function to update balances in the entire BST and balance the tree if needed
Tnode* updateBalancesAndBalanceTree(Tnode* node) {
    if (node == NULL) {
        return NULL;
    }

    // Update balances of left and right subtrees
    node->left = updateBalancesAndBalanceTree(node->left);
    node->right = updateBalancesAndBalanceTree(node->right);

    // Update the balance of the current node
    int newBalance = updateBalance(node);

    // If the tree is unbalanced, balance it
    if (newBalance < -1 || newBalance > 1) {
        node = balanceTree(node);
    }

    return node;
}

