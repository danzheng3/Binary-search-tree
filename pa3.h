#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"

Tnode* insert(Tnode *root, int key);
Tnode* deleteNode(Tnode* root, int key);

void printNodePreOrder(Tnode *node);

void preOrderTraversal(Tnode *node, FILE *outputFile);
void writeNodeToFile(Tnode *node, FILE *outputFile);
void freeTree(Tnode *node); 
int isValidBST(Tnode *node, int min, int max);
int isHeightBalanced(Tnode *node);
Tnode* getMinNode(Tnode* node);
Tnode* createNode(int key);
Tnode* getMaxNode(Tnode* node);
int readTreeFromFile(const char* filename);

Tnode* rotateRight(Tnode* node);
Tnode* rotateLeft(Tnode* node);
Tnode* balanceTree(Tnode* node);
int getHeight(Tnode* node);
int isHeightBalanced(Tnode *node);
int isValidBST(Tnode *node, int min, int max);
Tnode* updateBalancesAndBalanceTree(Tnode *node);