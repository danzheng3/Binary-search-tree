#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"

int insert(Tnode **root, int key);
int deleted(Tnode **root, int key);

void preOrderTraversal(Tnode *node, FILE *outputFile);
void writeNodeToFile(Tnode *node, FILE *outputFile);
void freeTree(Tnode *node); 
int isValidBST(Tnode *node, int min, int max);
int isHeightBalanced(Tnode *node);
Tnode* getMinNode(Tnode* node);
Tnode* createNode(int key);
Tnode* getMaxNode(Tnode* node);
int readTreeFromFile(const char* filename);

void leftRotate(Tnode **node);
void rightRotate(Tnode **node);
void doubleLeftRotate(Tnode **node);
void doubleRightRotate(Tnode **node);
int getHeight(Tnode *node);
int getBalance(Tnode *node);

int isValidBST(Tnode *node, int min, int max);
int isHeightBalanced(Tnode *node);
