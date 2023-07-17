#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa3.h"

void leftRotate(Tnode **node);
void rightRotate(Tnode **node);
void doubleLeftRotate(Tnode **node);
void doubleRightRotate(Tnode **node);
int getHeight(Tnode *node);
int getBalance(Tnode *node);

// Get the height of a node (recursive)
int getHeight(Tnode *node) {
  if (node == NULL) {
    return -1; // Empty tree has height -1
  }
  int leftHeight = getHeight(node->left);
  int rightHeight = getHeight(node->right);
  return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Get the balance factor of a node
int getBalance(Tnode *node) {
  if (node == NULL) {
    return 0; // Empty tree has balance 0
  }
  return getHeight(node->left) - getHeight(node->right);
}

/* Left rotation
void leftRotate(Tnode **node) {
  Tnode *current = *node;
  Tnode *newRoot = current->right;
  current->right = newRoot->left;
  newRoot->left = current;
  *node = newRoot;
} */

// Left rotation
void leftRotate(Tnode **node) {
  Tnode *current = *node;
  if (current == NULL || current->right == NULL) {
    return; // Cannot perform rotation
  }
  Tnode *newRoot = current->right;
  current->right = newRoot->left;
  newRoot->left = current;
  *node = newRoot;
}


// Right rotation
/*void rightRotate(Tnode **node) {
  Tnode *current = *node;
  Tnode *newRoot = current->left;
  current->left = newRoot->right;
  newRoot->right = current;
  *node = newRoot;
}*/

// Right rotation
void rightRotate(Tnode **node) {
  Tnode *current = *node;
  if (current == NULL || current->left == NULL) {
    return; // Cannot perform rotation
  }
  Tnode *newRoot = current->left;
  current->left = newRoot->right;
  newRoot->right = current;
  *node = newRoot;
}



// Double left rotation (left-right rotation)
void doubleLeftRotate(Tnode **node) {
  leftRotate(&(*node)->left);
  rightRotate(node);
}

// Double right rotation (right-left rotation)
void doubleRightRotate(Tnode **node) {
  rightRotate(&(*node)->right);
  leftRotate(node);
}
