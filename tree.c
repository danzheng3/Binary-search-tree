#include "hbt.h"
#include <stdlib.h>
#include <stdio.h>

int insert(Tnode **root, int key);
int delete(Tnode **root, int key);

int insert(Tnode **root, int key) {
  if (*root == NULL) {
    // Create a new node and insert the key
    Tnode *newNode = (Tnode *)malloc(sizeof(Tnode));
    if (newNode == NULL) {
      return 0; // Memory allocation failure
    }

    newNode->key = key;
    newNode->balance = 0;
    newNode->left = NULL;
    newNode->right = NULL;

    *root = newNode;
    return 1;
  }

  if (key < (*root)->key) {
    // Go left to insert the key (allowing duplicate keys to the left)
    if (!insert(&(*root)->left, key)) {
      return 0;
    }
  } else {
    // Go right to insert the key
    if (!insert(&(*root)->right, key)) {
      return 0;
    }
  }

  // Update balance factor
  (*root)->balance = getBalance(*root);

  // Perform rotations if necessary
  if ((*root)->balance > 1) {
    if (key < (*root)->left->key) {
      rightRotate(root);
    } else {
      doubleRightRotate(root);
    }
  } else if ((*root)->balance < -1) {
    if (key > (*root)->right->key) {
      leftRotate(root);
    } else {
      doubleLeftRotate(root);
    }
  }

  return 1;
}

int delete(Tnode **root, int key) {
  if (*root == NULL) {
    return 0; // Key not found
  }

  if (key < (*root)->key) {
    // Go left to delete the key
    if (!delete(&(*root)->left, key)) {
      return 0;
    }
  } else if (key > (*root)->key) {
    // Go right to delete the key
    if (!delete(&(*root)->right, key)) {
      return 0;
    }
  } else {
    // Node with matching key found, perform deletion
    Tnode *temp;
    if ((*root)->left == NULL || (*root)->right == NULL) {
      // Node has one child or no child
      temp = (*root)->left ? (*root)->left : (*root)->right;
      if (temp == NULL) {
        // No child
        temp = *root;
        *root = NULL;
      } else {
        // One child
        **root = *temp;
      }
      free(temp);
    } else {
      // Node has two children, find immediate predecessor
      temp = (*root)->left;
      while (temp->right != NULL) {
        temp = temp->right;
      }
      (*root)->key = temp->key;
      delete(&(*root)->left, temp->key);
    }
  }

  if (*root == NULL) {
    return 1; // Key deleted successfully
  }

  // Update balance factor
  (*root)->balance = getBalance(*root);

  // Perform rotations if necessary
  if ((*root)->balance > 1) {
    if (getBalance((*root)->left) >= 0) {
      rightRotate(root);
    } else {
      doubleRightRotate(root);
    }
  } else if ((*root)->balance < -1) {
    if (getBalance((*root)->right) <= 0) {
      leftRotate(root);
    } else {
      doubleLeftRotate(root);
    }
  }

  return 1;
}
