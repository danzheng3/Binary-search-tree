#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa3.h"


int isValidBST(Tnode *node, int min, int max) {
    if (node == NULL) {
        return 1;
    }
    if (node->key < min) {
        return 0;
    }
    if (node->key > max) {
        return 0;
    }
    return isValidBST(node->left, min, node->key) && isValidBST(node->right, node->key, max);
}

int isHeightBalanced(Tnode *node) {
    if (node == NULL) {
        return 1;
    }
    int leftHeight = getHeight(node->left);
    int rightHeight = getHeight(node->right);
    int balance = leftHeight - rightHeight;
    return (balance >= -1 && balance <= 1) && isHeightBalanced(node->left) && isHeightBalanced(node->right);
}


