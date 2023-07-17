#ifndef __HBT_TREE__
#define __HBT_TREE__
#include <stdio.h>
#include <stdlib.h>

typedef struct _Tnode {
   int key: 29, balance: 3;
   struct _Tnode *left;
   struct _Tnode *right;
} Tnode;

void leftRotate(Tnode **node);
void rightRotate(Tnode **node);
void doubleLeftRotate(Tnode **node);
void doubleRightRotate(Tnode **node);
int getHeight(Tnode *node);
int getBalance(Tnode *node);
int insert(Tnode **root, int key);
int delete(Tnode **root, int key);

void preOrderTraversal(Tnode *node, FILE *outputFile);
void writeNodeToFile(Tnode *node, FILE *outputFile);
void freeTree(Tnode *node); 

#define HBT_MAX 268435455
#define HBT_MIN -268435456

#endif
