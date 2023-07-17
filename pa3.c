#include "hbt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa3.h"




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
                if(!insert(&root,key)) {
                  

                }
            } else if (op=='d') {
                if(!deleted(&root,key)) {
                    //must remove these
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
        if (argc != 3) {
        printf("-1\n");
        return EXIT_FAILURE;
    }

    char* tree_input_file = argv[2];
    return readTreeFromFile(tree_input_file);


    
    }

}

int readTreeFromFile(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (file == NULL) {
        return -1; // 
    }

    int isValidFile = 0;
    int isBST = 0;
    int isheightBalanced = 0;

    Tnode* root = NULL;
    Tnode* currentNode = NULL;
    int key;
    char branchPattern;

    while (fread(&key, sizeof(int), 1, file) == 1 && fread(&branchPattern, sizeof(char), 1, file) == 1) {
        Tnode* newNode = (Tnode*)malloc(sizeof(Tnode));
        newNode->key = key;
        newNode->left = NULL;
        newNode->right = NULL;

        if (root == NULL) {
            root = newNode;
            currentNode = newNode;
        } else {
            while (1) {
                if (branchPattern & 0x01) { // Left child exists
                    if (currentNode->left == NULL) {
                        currentNode->left = newNode;
                        break;
                    } else {
                        currentNode = currentNode->left;
                    }
                } else { // Left child is NULL
                    if (currentNode->right == NULL) {
                        currentNode->right = newNode;
                        break;
                    } else {
                        currentNode = currentNode->right;
                    }
                }
                branchPattern >>= 1;
            }
        }
    }

    if (feof(file)) {
        isValidFile = 1;
        isBST = isValidBST(root, HBT_MIN, HBT_MAX);
        isheightBalanced = isHeightBalanced(root);
    }

    fclose(file);
    freeTree(root);

    printf("%d,%d,%d\n", isValidFile, isBST, isheightBalanced);

    if (isValidFile == 1) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}

void freeTree(Tnode *node) {
  if (node == NULL) {
    return;
  }
  freeTree(node->left);
  freeTree(node->right);
  free(node);
}

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

