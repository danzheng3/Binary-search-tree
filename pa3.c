#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa3.h"

void insertNode(Tnode** root, int key, unsigned char branchPattern);
Tnode* readBinaryFormat(FILE* inputFile);
void decodeBinaryPattern(char pattern, int* hasLeftChild, int* hasRightChild);

int main(int argc, char* argv[]) {
    char* option = argv[1];
    
    if (strcmp(option, "-b") == 0) {

        if (argc != 4) {
        return EXIT_FAILURE;
        }
        char* operations_input_file = argv[2];
        char* tree_output_file = argv[3];

        FILE *inputFile = fopen(operations_input_file, "rb");
        if(inputFile==NULL) {
            printf("-1\n");
            return EXIT_FAILURE;
        }

        Tnode *root = NULL;
        int key;
        char op;

        while (fread(&key, sizeof(int), 1, inputFile)==1 && fread(&op, sizeof(char), 1, inputFile)==1) {
            if (op=='i') {
                //printf("inserted %d\n", key);
                root=insert(root,key);
                updateBalancesAndBalanceTree(root);
                //printf("new tree:\n");
                //printNodePreOrder(root);
                //printf("\n");
            } else if (op=='d') {
                //printf("deleted %d\n", key);
                root=deleteNode(root,key);
                updateBalancesAndBalanceTree(root);
                //printf("new tree:\n");
                //printNodePreOrder(root);
                //printf("\n");
            }
        }

        fclose(inputFile);

        FILE* outputFile = fopen(tree_output_file,"wb");
        if(outputFile==NULL) {
            freeTree(root);
            printf("O\n");
            return EXIT_FAILURE;
        }

        preOrderTraversal(root, outputFile);

        fclose(outputFile);
        freeTree(root);
        printf("1\n");

        return EXIT_SUCCESS;


        
    } else if (strcmp(option, "-e") == 0) {
        if (argc != 3) {
        printf("-1\n");
        return EXIT_FAILURE;
    }
    int fileOpen;

    char* operations_input_file = argv[2];
    FILE* inputFile = fopen(operations_input_file, "rb");
    if (inputFile==NULL) {
        fileOpen=-1;
        printf("-1,0,0\n");
        fclose(inputFile);
        return EXIT_FAILURE;
    }
    Tnode* root = readBinaryFormat(inputFile);
    fileOpen=1;
    //printNodePreOrder(root);
    if (root==NULL) {
        printf("0,0,0\n");
        fclose(inputFile);
        freeTree(root);
        return EXIT_FAILURE;
    }

    fclose(inputFile);
    int isBST=isValidBST(root,HBT_MIN,HBT_MAX);
    int isBalanced= isHeightBalanced(root);
    freeTree(root);

    printf("%d,%d,%d\n", fileOpen,isBST,isBalanced);
    return EXIT_SUCCESS;



    
    } else {
        return EXIT_FAILURE;
    }

}

void decodeBinaryPattern(char pattern, int* hasLeftChild, int* hasRightChild) {
    *hasLeftChild = (pattern & 0x02) ? 1 : 0;
    *hasRightChild = (pattern & 0x01) ? 1 : 0;
}


Tnode* readBinaryFormat(FILE* inputFile) {
    int key;
    char pattern;

    /*if (fscanf(inputFile, "%d %c", &key, &pattern) != 2) {
        printf("hit return null\n");
        return NULL;
    }*/

    if (fread(&key, sizeof(int), 1, inputFile) != 1 || fread(&pattern, sizeof(unsigned char), 1, inputFile) != 1) {
        return NULL;
    }

    int hasLeftChild, hasRightChild;
    decodeBinaryPattern(pattern, &hasLeftChild, &hasRightChild);

    Tnode* newNode = createNode(key);

    if (hasLeftChild) {
        newNode->left = readBinaryFormat(inputFile);
    }

    if (hasRightChild) {
        newNode->right = readBinaryFormat(inputFile);
    }

    return newNode;
}

void freeTree(Tnode *node) {
  if (node == NULL) {
    return;
  }
  freeTree(node->left);
  freeTree(node->right);
  free(node);
}

void insertNode(Tnode** root, int key, unsigned char branchPattern) {
    Tnode* newNode = createNode(key);
    if (branchPattern & 0x01) { 
        (*root)->left = newNode;
    } else { 
        (*root)->right = newNode;
    }
}

void writeNodeToFile(Tnode *node, FILE *outputFile) {
    int key = node->key;
    int balance = node->balance;

    unsigned char ch = 0;

    // left child
    if (node->left != NULL)
        ch |= 0x02;

    // right child
    if (node->right != NULL)
        ch |= 0x01;

    fwrite(&key, sizeof(int), 1, outputFile);
    fwrite(&ch, sizeof(unsigned char), 1, outputFile);

    if (node->left != NULL)
        writeNodeToFile(node->left, outputFile);
    if (node->right != NULL)
        writeNodeToFile(node->right, outputFile);
}

void preOrderTraversal(Tnode *node, FILE *outputFile) {
    if (node == NULL || outputFile == NULL)
        return;

    writeNodeToFile(node, outputFile);
}

