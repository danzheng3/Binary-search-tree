#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
void leftRotate(Tnode **node);
void rightRotate(Tnode **node);
void doubleLeftRotate(Tnode **node);
void doubleRightRotate(Tnode **node);
int getHeight(Tnode *node);
int getBalance(Tnode *node);
int insert(Tnode **root, int key);
int delete(Tnode **root, int key);*/


int main(int argc, char* argv[]) {
    if (argc != 4) {
        return EXIT_FAILURE;
    }

    char* option = argv[1];
    char* operations_input_file = argv[2];
    char* tree_output_file = argv[3];

    FILE *inputFile = fopen(operations_input_file, "rb");
    if(inputFile==NULL) {
        printf("-1\n");
        return EXIT_FAILURE;
    }

    if (strcmp(option, "-b") == 0) {
        Tnode *root = NULL;
        int key;
        char op;

        while (fread(&key, sizeof(int), 1, inputFile)==1 && fread(&op, sizeof(char), 1, inputFile)==1) {
            if (op=='i') {
                if(!insert(&root,key)) {
                    printf("O\n");
                    break;

                }
            } else if (op=='d') {
                if(!delete(&root,key)) {
                    printf("O\n");
                    break;
                }
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


    }
    return EXIT_SUCCESS;
} 

// Free the memory allocated for the tree (recursive)
void freeTree(Tnode *node) {
  if (node == NULL) {
    return;
  }
  freeTree(node->left);
  freeTree(node->right);
  free(node);
}

// Pre-order traversal and write to the output file

void writeNodeToFile(Tnode *node, FILE *outputFile) {
    int key = node->key;
    int balance = node->balance;

    unsigned char ch = 0;

    // Set the left child flag
    if (node->left != NULL)
        ch |= 0x02;

    // Set the right child flag
    if (node->right != NULL)
        ch |= 0x01;

    // Write the key as an int to the output file
    fwrite(&key, sizeof(int), 1, outputFile);

    // Write the char with branch information to the output file
    fwrite(&ch, sizeof(unsigned char), 1, outputFile);

    // Recursively write the left and right child nodes
    if (node->left != NULL)
        writeNodeToFile(node->left, outputFile);
    if (node->right != NULL)
        writeNodeToFile(node->right, outputFile);
}

void preOrderTraversal(Tnode *node, FILE *outputFile) {
    if (node == NULL || outputFile == NULL)
        return;

    // Write the nodes in pre-order traversal to the output file
    writeNodeToFile(node, outputFile);
}

