#include <stdio.h>
#include <stdlib.h>

typedef struct Tnode {
    int key;
    int balance;
    struct Tnode *left;
    struct Tnode *right;
} Tnode;

// Function to read a single node from the binary file
Tnode* readNodeFromFile(FILE *inputFile) {
    Tnode* node = (Tnode*)malloc(sizeof(Tnode));

    if (fread(&node->key, sizeof(int), 1, inputFile) != 1) {
        free(node);
        return NULL;
    }

    unsigned char ch;
    if (fread(&ch, sizeof(unsigned char), 1, inputFile) != 1) {
        free(node);
        return NULL;
    }

    node->balance = ch & 0x03; // Extracting the balance from the flags

    if (ch & 0x02) // Check the left child flag
        node->left = readNodeFromFile(inputFile);
    else
        node->left = NULL;

    if (ch & 0x01) // Check the right child flag
        node->right = readNodeFromFile(inputFile);
    else
        node->right = NULL;

    return node;
}

// Function to write the contents of the tree to a text file using pre-order traversal
void writeNodeToTextFile(Tnode *node, FILE *outputFile) {
    if (node == NULL)
        return;

    fprintf(outputFile, "%d %d\n", node->key, node->balance);
    writeNodeToTextFile(node->left, outputFile);
    writeNodeToTextFile(node->right, outputFile);
}

int main(int argc, char*argv[]) {
    char* input = argv[1];
    char* output = argv[2];
    // Open the binary input file
    FILE *inputFile = fopen(input, "rb");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    // Read the binary data and construct the tree
    Tnode *root = readNodeFromFile(inputFile);

    // Close the input file
    fclose(inputFile);

    // Open the output text file
    FILE *outputFile = fopen(output, "w");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        return 1;
    }

    // Write the tree contents to the text file using pre-order traversal
    writeNodeToTextFile(root, outputFile);

    // Close the output file
    fclose(outputFile);

    // Free the allocated memory for the tree
    // (You need to implement a function to free the memory properly)
    // freeTree(root);

    printf("Conversion completed successfully.\n");

    return 0;
}
