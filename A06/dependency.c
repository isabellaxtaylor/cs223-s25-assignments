/*----------------------------------------------
 * Author: Isabella Taylor
 * Date: 3/1/2025
 * Description: Binary Search Tree for dependencies.
 ---------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 128
#define MAX_DEPENDENCIES 20

// Struct for dependency info
struct dep_node {
    char filename[MAX_NAME];
    char dependencies[MAX_DEPENDENCIES][MAX_NAME];
    int dep_count;
    struct dep_node* left;
    struct dep_node* right;
};

// Function for new dependency node
struct dep_node* create_node(const char* filename) {
    struct dep_node* newNode = (struct dep_node*)malloc(sizeof(struct dep_node));
    strncpy(newNode->filename, filename, MAX_NAME);
    newNode->dep_count = 0;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert file into dependency tree
struct dep_node* insert_dependency(struct dep_node* root, const char* filename) {
    if (root == NULL) {
        return create_node(filename);
    }
    int cmp = strcmp(filename, root->filename);
    if (cmp < 0) {
        root->left = insert_dependency(root->left, filename);
    } else if (cmp > 0) {
        root->right = insert_dependency(root->right, filename);
    }
    return root;
}

// Find file in dependency tree
struct dep_node* find_dependency(struct dep_node* root, const char* filename) {
    if (root == NULL || strcmp(root->filename, filename) == 0) {
        return root;
    }
    if (strcmp(filename, root->filename) < 0) {
        return find_dependency(root->left, filename);
    } else {
        return find_dependency(root->right, filename);
    }
}

// Take dependencies from file
void extract_dependencies(struct dep_node* node) {
    FILE* file = fopen(node->filename, "r");
    if (!file) {
        fprintf(stderr, "Error opening file: %s\n", node->filename);
        return;
    }

    char line[MAX_NAME];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "#include")) {
            char dep[MAX_NAME];
            if (sscanf(line, "#include \"%[^\"]\"", dep) == 1) {
                if (node->dep_count < MAX_DEPENDENCIES) {
                    strncpy(node->dependencies[node->dep_count], dep, MAX_NAME);
                    node->dep_count++;
                }
            }
        }
    }
    fclose(file);
}

// Print list of files in alphabetical order
void list_files(struct dep_node* root) {
    if (root == NULL) return;
    list_files(root->left);
    printf("%s\n", root->filename);
    list_files(root->right);
}

// Print dependencies of file
void print_dependencies(struct dep_node* root, const char* filename) {
    struct dep_node* node = find_dependency(root, filename);
    if (!node) {
        printf("%s not found\n", filename);
        return;
    }
    printf("%s has the following dependencies:\n", filename);
    for (int i = 0; i < node->dep_count; i++) {
        printf("  %s\n", node->dependencies[i]);
    }
}

// Free memory used
void free_tree(struct dep_node* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <files>\n", argv[0]);
        return 1;
    }

    struct dep_node* root = NULL;
    printf("Processing %d files\n", argc - 1);

    // Insert files into BST/extract dependencies
    for (int i = 1; i < argc; i++) {
        root = insert_dependency(root, argv[i]);
        extract_dependencies(find_dependency(root, argv[i]));
    }

    char input[MAX_NAME];
    while (1) {
        printf("$ ");
        if (!fgets(input, sizeof(input), stdin)) {
            break;
        }
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "quit") == 0) {
            break;
        } else if (strcmp(input, "list") == 0) {
            list_files(root);
        } else {
            print_dependencies(root, input);
        }
    }

    free_tree(root);
    return 0;
}