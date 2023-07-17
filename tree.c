#include "hbt.h"
#include <stdlib.h>
#include <stdio.h>
#include "pa3.h"

int insert(Tnode **root, int key);
int deleted(Tnode **root, int key);
Tnode* getMinNode(Tnode* node);
Tnode* createNode(int key);
Tnode* getMaxNode(Tnode* node);

int insert(Tnode **root, int key) {
  if (*root == NULL) {
    *root = createNode(key);
    return 1;
  }
//need to fix rotations with somewhere to go (left, right rotation end)

  int inserted;
  if (key < (*root)->key) {
    inserted = insert(&(*root)->left, key);
    if (inserted) {
      // Check if the left subtree is imbalanced
      if (getBalance(*root) == 2) {
        if (key < (*root)->left->key) {
          // Case 1: Left-Left
          rightRotate(root);
        } else {
          // Case 3: Left-Right
          doubleRightRotate(root);
        }
      }
    }
  } else if (key > (*root)->key) {
    inserted = insert(&(*root)->right, key);
    if (inserted) {
      // Check if the right subtree is imbalanced
      if (getBalance(*root) == -2) {
        if (key > (*root)->right->key) {
          // Case 2: Right-Right
          leftRotate(root);
        } else {
          // Case 4: Right-Left
          doubleLeftRotate(root);
        }
      }
    }
  } else {
    // Duplicate key, go left
    inserted = insert(&(*root)->left, key);
    if (inserted) {
      // Check if the left subtree is imbalanced
      if (getBalance(*root) == 2) {
        if (key < (*root)->left->key) {
          // Case 1: Left-Left
          rightRotate(root);
        } else {
          // Case 3: Left-Right
          doubleRightRotate(root);
        }
      }
    }
  }

  return inserted;
}



int deleted(Tnode **root, int key) {
  if (*root == NULL) {
    return 0; // Key not found
  }

  int isDeleted;
  if (key < (*root)->key) {
    isDeleted = deleted(&(*root)->left, key);
    if (isDeleted) {
      if (getBalance(*root) == -2) {
        if (getBalance((*root)->right) <= 0) {
          // Case 2: Right-Right
          leftRotate(root);
        } else {
          // Case 4: Right-Left
          doubleLeftRotate(root);
        }
      }
    }
  } else if (key > (*root)->key) {
    isDeleted = deleted(&(*root)->right, key);
    if (isDeleted) {
      // Check if the left subtree is imbalanced
      if (getBalance(*root) == 2) {
        if (getBalance((*root)->left) >= 0) {
          // Case 1: Left-Left
          rightRotate(root);
        } else {
          // Case 3: Left-Right
          doubleRightRotate(root);
        }
      }
    }
  } else {
    isDeleted = 1;
    Tnode *temp = *root;
    if ((*root)->left == NULL && (*root)->right == NULL) {
      // Node is a leaf
      *root = NULL;
      free(temp);
    } else if ((*root)->left != NULL && (*root)->right != NULL) {
      // Node has two children
      temp = getMaxNode((*root)->left);
      (*root)->key = temp->key;
      deleted(&(*root)->left, temp->key);
      if (getBalance(*root) == 2) {
        if (getBalance((*root)->left) >= 0) {

          rightRotate(root);
        } else {
          doubleRightRotate(root);
        }
      }
    } else {
      // Node has only one child
      if ((*root)->left != NULL) {
        *root = (*root)->left;
      } else {
        *root = (*root)->right;
      }
      free(temp);
    }
  }

  return isDeleted;
}

Tnode* getMaxNode(Tnode* node) {
  Tnode* current = node;
  while (current->right != NULL) {
    current = current->right;
  }
  return current;
}


Tnode* createNode(int key) {
  Tnode* newNode = (Tnode*)malloc(sizeof(Tnode));
  newNode->key = key;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

Tnode* getMinNode(Tnode* node) {
  Tnode* current = node;
  while (current->left != NULL) {
    current = current->left;
  }
  return current;
}

