#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

enum choice{
    EXIT,
    READ_TREE,
    DISPLAY_TREE,
    CALCULATE_DEPTH_TREE,
    SEARCH_NODE,
    CALCULATE_DEPTH_NODE,
    CALCULATE_HEIGHT_NODE,
    DISPLAY_LEAF,
    CLEAN_TREE,
    FREE_MEMORY,
};

/**
 * Create a new node with the given key and allocate memory for it.
 * @param key The key value for the new node.
 * @return A pointer to the newly created node.
 */
Node* create_node(int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/**
 * Insert a node with the given key into the binary tree rooted at 'root'.
 * @param root The root of the binary tree.
 * @param key The key value to insert.
 * @return The root of the modified binary tree.
 */
Node* insert_node_in_tree(Node* root, int key) {
    if (root == NULL) {
        return create_node(key);
    }
    if (key < root->key) {
        root->left = insert_node_in_tree(root->left, key);
    } else if (key > root->key) {
        root->right = insert_node_in_tree(root->right, key);
    }
    return root;
}

/**
 * Perform a pre-order traversal of the binary tree rooted at 'root' and print the keys.
 * @param root The root of the binary tree.
 */
void pre_order_traversal(Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        pre_order_traversal(root->left);
        pre_order_traversal(root->right);
    }
}

/**
 * Calculate the depth of the binary tree rooted at 'root'.
 * @param root The root of the binary tree.
 * @return The depth of the binary tree.
 */
int tree_depth(Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        int leftDepth = tree_depth(root->left);
        int rightDepth = tree_depth(root->right);
        return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
    }
}

/**
 * Search for a node with the given key in the binary tree rooted at 'root'.
 * @param root The root of the binary tree.
 * @param key The key value to search for.
 * @return A pointer to the node with the given key, or NULL if not found.
 */
Node* search(Node* root, int key) {
    if (root == NULL || root->key == key) {
        return root;
    }
    if (root->key < key) {
        return search(root->right, key);
    }
    return search(root->left, key);
}

/**
 * Calculate the depth of the node with the given key in the binary tree rooted at 'root'.
 * @param root The root of the binary tree.
 * @param key The key value of the node to calculate the depth for.
 * @param depth The current depth of the search.
 * @return The depth of the node with the given key, or -1 if not found.
 */
int node_depth(Node* root, int key, int depth) {
    if (root == NULL) {
        return -1;
    }
    if (root->key == key) {
        return depth;
    }
    if (key < root->key) {
        return node_depth(root->left, key, depth + 1);
    }
    return node_depth(root->right, key, depth + 1);
}

/**
 * Calculate the height of the node with the given key in the binary tree rooted at 'root'.
 * @param root The root of the binary tree.
 * @param key The key value of the node to calculate the height for.
 * @return The height of the node with the given key, or -1 if not found.
 */
int get_node_height(Node* root, int key) {
    Node* node = search(root, key);
    if (node == NULL) {
        return -1;
    }
    return tree_depth(node);
}

/**
 * Print the leaf nodes of the binary tree rooted at 'root'.
 * @param root The root of the binary tree.
 */
void print_leaves(Node* root) {
    if (root != NULL) {
        if (root->left == NULL && root->right == NULL) {
            printf("%d ", root->key);
        }
        print_leaves(root->left);
        print_leaves(root->right);
    }
}

/**
 * Delete the binary tree rooted at 'root' and free the memory.
 * @param root The root of the binary tree.
 */
void delete_tree(Node* root) {
    if (root != NULL) {
        delete_tree(root->left);
        delete_tree(root->right);
        free(root);
    }
}

/**
 * Print the menu options for the binary tree operations.
 */
void print_menu() {
    printf("\n1. Read the tree\n");
    printf("2. Display the tree\n");
    printf("3. Calculate the depth of the tree\n");
    printf("4. Search for a node in the tree\n");
    printf("5. Calculate the depth of a node\n");
    printf("6. Calculate the height of a node\n");
    printf("7. Display all the leaf nodes of the tree\n");
    printf("8. Clean the tree\n");
    printf("9. Free the memory of the tree\n");
    printf("0. Exit\n");
}

int main() {
    Node* root = NULL;
    int choice, key;

    do {
        print_menu();
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case READ_TREE:
                printf("Enter the elements of the tree (0 to finish): ");
                while (1) {
                    scanf("%d", &key);
                    if (key == 0) break;
                    root = insert_node_in_tree(root, key);
                }
                break;
            case DISPLAY_TREE:
                printf("The elements of the tree are: ");
                pre_order_traversal(root);
                printf("\n");
                break;
            case CALCULATE_DEPTH_TREE:
                printf("The depth of the tree is: %d\n", tree_depth(root));
                break;
            case SEARCH_NODE:
                printf("Enter the search key: ");
                scanf("%d", &key);
                if (search(root, key) != NULL) {
                    printf("The node with key %d exists in the tree.\n", key);
                } else {
                    printf("The node with key %d does not exist in the tree.\n", key);
                }
                break;
            case CALCULATE_DEPTH_NODE:
                printf("Enter the search key: ");
                scanf("%d", &key);
                printf("The depth of the node is: %d\n", node_depth(root, key, 0));
                break;
            case CALCULATE_HEIGHT_NODE:
                printf("Enter the search key: ");
                scanf("%d", &key);
                printf("The height of the node is: %d\n", get_node_height(root, key));
                break;
            case DISPLAY_LEAF:
                printf("The leaf nodes of the tree are: ");
                print_leaves(root);
                printf("\n");
                break;
            case CLEAN_TREE:
                delete_tree(root);
                root = NULL;
                printf("The tree has been cleaned.\n");
                break;
            case FREE_MEMORY:
                delete_tree(root);
                root = NULL;
                printf("The memory of the tree has been freed.\n");
                break;
            case EXIT:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 0);

    return 0;
}
