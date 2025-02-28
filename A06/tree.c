/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 2/28/2025
 * Description: Binary Search Tree Implementation
 ---------------------------------------------*/
#include "tree.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

// Function to find a node by its name
struct tree_node* find(const char* name, struct tree_node* root) {
    if (root == NULL) {
        return NULL;
    }
    int cmp = strncmp(name, root->data.name, 64);
    if (cmp < 0) {
        return find(name, root->left);
    } else if (cmp > 0) {
        return find(name, root->right);
    } else {
        return root;
    }
}

// Function to insert new node with given name
struct tree_node* insert(const char* name, struct tree_node* root) {
    if (root == NULL) {
        root = (struct tree_node*)malloc(sizeof(struct tree_node));
        strncpy(root->data.name, name, 64);
        root->left = NULL;
        root->right = NULL;
        return root;
    }

    int cmp = strncmp(name, root->data.name, 64);
    if (cmp < 0) {
        root->left = insert(name, root->left);
    } else if (cmp > 0) {
        root->right = insert(name, root->right);
    }
    return root;
}

// Function to clear all nodes in tree
void clear(struct tree_node* root) {
    if (root == NULL) {
        return;
    }
    clear(root->left);
    clear(root->right);
    free(root);  // Free  current node
}

// Function to print tree in the format
void printTree(struct tree_node* root, int depth, char prefix) {
    if (root == NULL) {
        return;
    }
    for (int i = 0; i < depth; i++) {
        printf(" ");
    }
    if (prefix != ' ') {  // Print prefix for left and right labels
        printf("%c:", prefix);
    }
    printf("%s\n", root->data.name);

    if (root->left) {
        printTree(root->left, depth + 2, 'l');  // Print left child
    }
    if (root->right) {
        printTree(root->right, depth + 2, 'r');  // Print right child
    }
}

// Function to print tree (entry point)
void print(struct tree_node* root) {
    if (root != NULL) {
        printf("%s\n", root->data.name);  // Print root without prefix
        if (root->left) {
            printTree(root->left, 1, 'l');  // Print left subtree
        }
        if (root->right) {
            printTree(root->right, 1, 'r');  // Print right subtree
        }
    }
}

// Function to print tree in sorted order
void printSorted(struct tree_node* root) {
    if (root == NULL) {
        return;
    }
    printSorted(root->left);  // left subtree
    printf("%s\n", root->data.name);  // current node
    printSorted(root->right);  // right subtree
}
