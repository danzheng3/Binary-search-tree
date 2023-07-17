#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>

int isValidBST(Tnode *node, int min, int max);
int isHeightBalanced(Tnode *node);

int isValidBST(Tnode *node, int min, int max) {
    if (node == NULL) {
        return 1;
    }
    if (node->key < min || node->key > max) {
        return 0;
    }
    return isValidBST(node->left, min, node->key - 1) && isValidBST(node->right, node->key + 1, max);
}

int isHeightBalanced(Tnode *node) {
    if (node == NULL) {
        return 1;
    }
    int balance = getBalance(node);
    return (balance >= -1 && balance <= 1) && isHeightBalanced(node->left) && isHeightBalanced(node->right);
}