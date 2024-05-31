#include <stdio.h>
#include <stdlib.h>

typedef struct book {
    char *title;
    char *author;
    int year;
    int pages;
} Book;

typedef struct Node {
    int key;
    struct book book_info;
    struct Node *left;
    struct Node *right;
} Node;

typedef struct BinaryTree {
    Node *root;
} BinaryTree;

enum CHOICE {
    EXIT = 0,
    READ_TREE,
    PRINT_TREE,
    SEARCH_NODE,
    SVD,
    VSD,
    SDV,
    BSF,
    DSF,
    TREE_BALANCE,
    TREE_MIRROR,
    CLEAN_TREE,
    FREE_MEMORY,
};

/**
 * This function allocates memory for a new BinaryTree structure and returns a pointer to it.
 * The root of the tree is initialized to NULL.
 * @return A pointer to the newly created BinaryTree structure
 */
BinaryTree *create_binary_tree() {
    BinaryTree *Tree = (BinaryTree *) calloc(1, sizeof(BinaryTree));
    return Tree;
}

/**
 * Reads the details of a book from the user.
 * @return An initialized Book structure.
 */
Book read_book() {
    Book* new_book = (Book*)malloc(sizeof(Book));
    if (new_book == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    new_book->title = (char*)malloc(sizeof(char) * 50);
    new_book->author = (char*)malloc(sizeof(char) * 50);
    if (new_book->title == NULL || new_book->author == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    printf("Book title: ");
    scanf("%s", new_book->title);
    printf("Book author: ");
    scanf("%s", new_book->author);
    printf("Book year: ");
    scanf("%d", &(new_book->year));
    printf("Number of pages: ");
    scanf("%d", &(new_book->pages));
    return *new_book;
}

/**
 * Create a new node with the given key and allocate memory for it.
 * @param key The key value for the new node.
 * @param new_book The book details to be stored in the new node.
 * @return A pointer to the newly created node.
 */
Node* create_node(Book new_book, int key) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Memory allocation error.\n");
        exit(EXIT_FAILURE);
    }
    new_node->key = key;
    new_node->book_info = new_book;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/**
 * This function is used to insert a new node into the binary tree.
 * @param current_node The current node in the binary tree
 * @param new_node The new node to be inserted into the binary tree
 */
void insert_node(Node *current_node, Node *new_node) {
    if (new_node->key < current_node->key) {
        if (current_node->left) {
            insert_node(current_node->left, new_node);
        } else {
            current_node->left = new_node;
        }
    } else if (new_node->key > current_node->key) {
        if (current_node->right) {
            insert_node(current_node->right, new_node);
        } else {
            current_node->right = new_node;
        }
    }
}

/**
 * Insert a node with the given key into the binary tree rooted at 'root'.
 * @param tree The pointer of the binary tree
 * @param key The key value to insert.
 */
void insert_node_in_tree(BinaryTree *tree, Node *new_node) {
    if (!tree->root) {
        tree->root = new_node;
    } else {
        insert_node(tree->root, new_node);
    }
}

/**
 * Prints the details of a book stored in a node.
 * @param book_info the book containde in the current node
 */
void print_book(Book book_info) {
    printf("Title: %s\n", book_info.title);
    printf("Author: %s\n", book_info.author);
    printf("Year: %d\n", book_info.year);
    printf("Pages: %d\n", book_info.pages);
}

/**
 *Prints the key and the book details of a node.
 * @param node  The node to print.
 */
void print_node(Node *node) {
    printf("Key: %d\n", node->key);
    print_book(node->book_info);
}

/**
 *This function is a helper function for printing the binary tree.
 * @param current_node The current node in the binary tree.
 */
void print_tree_helper(Node *current_node) {
    if (!current_node) {
        return;
    }
    print_node(current_node);
    print_tree_helper(current_node->left);
    print_tree_helper(current_node->right);
}

/**
 * Perform a pre-order traversal of the binary tree rooted at 'root' and print the keys and the iphone inside the element.
 * @param tree The pointer of the binary tree.
 */
void print_binary_tree(BinaryTree *tree) {
    if (!tree->root) {
        return;
    }
    print_tree_helper(tree->root);
}

/**
 * Perform an in-order traversal of the binary tree rooted at 'root' and print the keys.
 * @param node The node of the binary tree.
 */
void svd_traversal_helper(Node* node) {
    if (node == NULL) {
        return;
    }
    svd_traversal_helper(node->left);
    printf("%d ", node->key);
    svd_traversal_helper(node->right);
}

/**
 *This function performs an in-order traversal of the binary tree rooted at 'tree'
 * and prints the keys of the nodes in the tree.
 * @param tree The pointer to the binary tree
 */
void svd_traversal(BinaryTree *tree) {
    printf("The tree in In-order traversal: ");
    svd_traversal_helper(tree->root);
    printf("\n");
}

/**
 *This function is a helper function for performing a pre-order traversal of the binary tree.
 * It prints the key of each node in the tree.
 * @param node The current node in the binary tree.
 */
void vsd_traversal_helper(Node* node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->key);
    vsd_traversal_helper(node->left);
    vsd_traversal_helper(node->right);
}

/**
 * Perform a pre-order traversal of the binary tree rooted at 'node' and print the keys.
 * @param tree The poiner of the binary tree.
 */
void vsd_traversal(BinaryTree *tree) {
    printf("The tree in Pre-order traversal: ");
    vsd_traversal_helper(tree->root);
    printf("\n");
}

/**
  *This function is a helper function for performing a post-order traversal of the binary tree.
 * It prints the key of each node in the tree.
  * @param node  The current node in the binary tree.
  */
void sdv_traversal_helper(Node* node) {
    if (node == NULL) {
        return;
    }
    sdv_traversal_helper(node->left);
    sdv_traversal_helper(node->right);
    printf("%d ", node->key);
}

/**
 * Perform a post-order traversal of the binary tree rooted at 'root' and print the keys.
 * @param tree The pointer of the binary tree.
 */
void sdv_traversal(BinaryTree *tree) {
    printf("The tree in Post-order traversal: ");
    sdv_traversal_helper(tree->root);
    printf("\n");
}

/**
 * Store array_of_nodes in in-order traversal in an array
 * @param node The node of the binary tree.
 * @param array_of_nodes The array to store the array_of_nodes.
 * @param index The current index in the array.
 */
void store_nodes_in_array_helper(Node* node, Node** array_of_nodes, int* index) {
    if (node == NULL) {
        return;
    }
    store_nodes_in_array_helper(node->left, array_of_nodes, index);
    array_of_nodes[(*index)++] = node;
    store_nodes_in_array_helper(node->right, array_of_nodes, index);
}

/**
 * This function stores the nodes of the binary tree in an array in an in-order traversal.
 * @param tree The pointer to the binary tree.
 * @param nodes_count The number of nodes in the binary tree.
 * @return A pointer to an array of pointers to the nodes in the binary tree.
 *         The array is dynamically allocated and should be freed by the caller.
 */
Node **store_BST_in_array(BinaryTree *tree, int nodes_count) {
    int index = 0;
    Node** array_of_nodes = (Node**)malloc(sizeof(Node*) * nodes_count);
    store_nodes_in_array_helper(tree->root, array_of_nodes, &index);
    return array_of_nodes;
}

/**
 * Convert a sorted array of nodes to a balanced binary search tree.
 * @param nodes The array of sorted nodes.
 * @param start The start index of the array.
 * @param end The end index of the array.
 * @return The root of the balanced binary search tree.
 */
Node* convert_array_to_BST(Node** nodes, int start, int end) {
    if (start > end) {
        return NULL;
    }
    int mid = (start + end) / 2;
    Node *root = nodes[mid];
    root->left = convert_array_to_BST(nodes, start, mid - 1);
    root->right = convert_array_to_BST(nodes, mid + 1, end);
    return root;
}

/**
 * Balance the binary tree rooted at 'root'.
 * @param root The root of the binary tree.
 * @return The root of the balanced binary tree.
 */
Node* balance_tree(BinaryTree *tree) {
    if (tree == NULL) {
        return NULL;
    }

    int node_count = 0;
    Node* temp = tree->root;
    while (temp != NULL) {
        node_count++;
        temp = temp->right;
    }

    Node** nodes = store_BST_in_array(tree, node_count);

    Node* new_root = convert_array_to_BST(nodes, 0, node_count - 1);

    free(nodes);

    return new_root;
}

/**
 *This function is a helper function for mirroring the binary tree.
 * It swaps the left and right children of every node.
 * @param node The node of the binary tree.
 */
void mirror_tree_helper(Node* node) {
    if (node == NULL) {
        return;
    }

    mirror_tree_helper(node->left);
    mirror_tree_helper(node->right);

    Node* temp = node->left;
    node->left = node->right;
    node->right = temp;
}

/**
 * Mirrors the binary tree by swapping the left and right children of every node.
 * @param tree The pointer of the binary tree.
 */
void mirror_tree(BinaryTree* tree) {
    mirror_tree_helper(tree->root);
}

/**
 *This function is a helper function for searching a node with a given key in the binary tree.
 * @param current_node
 * @param key
 * @return A pointer to the node with the given key, or NULL if not found.
 */
Node *search_by_key_helper(Node *current_node, int key) {
    if (current_node == NULL || current_node->key == key) {
        return current_node;
    }
    if (current_node->key < key) {
        return search_by_key_helper(current_node->right, key);
    }
    return search_by_key_helper(current_node->left, key);
}

/**
 * Search for a node with the given key in the binary tree rooted at 'root'.
 * @param tree The root of the binary tree.
 * @param key The key value to search_node_by_key for.
 */
Node* search_node_by_key(BinaryTree *tree, int key) {
    if (!tree) {
        return NULL;
    }
    return search_by_key_helper(tree->root, key);
}

/**
 * Delete the binary tree rooted at 'node' and free the memory.
 * @param node The node of the binary tree.
 */
void delete_node(Node* node) {
    if (node != NULL) {
        delete_node(node->left);
        delete_node(node->right);
        free(node);
    }
}

/**
 *Deletes the binary tree rooted at 'tree' and frees the memory.
 * @param tree The pointer to the binary tree to be deleted.
 */
void delete_tree(BinaryTree *tree) {
    if (!tree) {
        return;
    }
    delete_node(tree->root);
    tree->root = NULL;
}

/**
 * Calculate the get_height of the binary tree.
 * @param root The root of the binary tree.
 * @return The get_height of the binary tree.
 */
int get_height(Node* node) {
    if (node == NULL) {
        return 0;
    }
    int left_height = get_height(node->left);
    int right_height = get_height(node->right);
    return (left_height > right_height) ? left_height + 1 : right_height + 1;
}

/**
 * Print all nodes at a given level.
 * @param node The node of the binary tree.
 * @param level The level to print nodes from.
 */
void print_level(Node* node, int level) {
    if (node == NULL) {
        return;
    }
    if (level == 1) {
        printf("%d ", node->key);
    } else if (level > 1) {
        print_level(node->left, level - 1);
        print_level(node->right, level - 1);
    }
}

/**
 * Perform a breadth-first search (BSF) traversal of the binary tree using recursion.
 * @param root The root of the binary tree.
 */
void bsf_traversal_recursive(BinaryTree* tree) {
    int h = get_height(tree->root);
    for (int i = 1; i <= h; i++) {
        print_level(tree->root, i);
    }
    printf("\n");
}

/**
 * Print the menu options for the binary tree operations.
 */
void print_menu() {
    printf("\n%d) Add a book\n",READ_TREE);
    printf("%d) Display the tree\n",PRINT_TREE);
    printf("%d) Search for a node by key\n",SEARCH_NODE);
    printf("%d) In-order traversal\n",SVD);
    printf("%d) Pre-order traversal\n",VSD);
    printf("%d) Post-order traversal\n",SDV);
    printf("%d) Breadth-first traversal\n",BSF);
    printf("%d) Depth-first traversal\n",DSF);
    printf("%d) Balance the tree\n",TREE_BALANCE);
    printf("%d) Mirror the tree\n",TREE_MIRROR);
    printf("%d) Clear the tree\n",CLEAN_TREE);
    printf("%d) Exit\n",EXIT);
}

void switch_choice(int choice, BinaryTree* tree) {
    int key;
    Book book_info;
    Node* node;
    
    switch (choice) {
        case READ_TREE:
            book_info = read_book();
            printf("Enter key for the book: ");
            scanf("%d", &key);
            node = create_node(book_info, key);
            insert_node_in_tree(tree, node);
            break;
        case PRINT_TREE:
            print_binary_tree(tree);
            break;
        case SEARCH_NODE:
            printf("Enter the key to search: ");
            scanf("%d", &key);
            node = search_node_by_key(tree, key);
            if (node) {
                print_node(node);
            } else {
                printf("Node not found.\n");
            }
            break;
        case SVD:
            svd_traversal(tree);
            break;
        case VSD:
            vsd_traversal(tree);
            break;
        case SDV:
            sdv_traversal(tree);
            break;
        case BSF:
            bsf_traversal_recursive(tree);
            break;
        case TREE_BALANCE:
            tree->root = balance_tree(tree);
            break;
        case TREE_MIRROR:
            mirror_tree(tree);
            break;
        case CLEAN_TREE:
            delete_tree(tree);
            break;
        case EXIT:
            delete_tree(tree);
            free(tree);
            exit(0);
        default:
            printf("Invalid choice.\n");
    }
}

int main() {
    BinaryTree* tree = create_binary_tree();
    int choice;
    while (1) {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch_choice(choice, tree);
    }
    return 0;
}
