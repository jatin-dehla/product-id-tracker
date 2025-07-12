#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "myHashTable.h"
#include "myBST.h"

#define NEIGHBOR_LIMIT 5

// Checks if an ID was produced (exists in hash table)
bool checkIDExists(int id, HashTable* hash_table) {
    if (search(hash_table, id)) {
        printf("Y\n");
        return true;
    } else {
        printf("N\n");
        return false;
    }
}

// Finds up to NEIGHBOR_LIMIT predecessors and successors of a given ID in BST
void findNeighboringIDs(int id, TreeNode* bst_root) {
    TreeNode* target_node = find_key(bst_root, id);
    if (target_node == NULL) {
        return;  // No neighbors to find if node doesn't exist
    }

    int neighbors[2 * NEIGHBOR_LIMIT];
    int neighbor_count = 0;

    // Find NEIGHBOR_LIMIT predecessors
    TreeNode* predecessor = target_node;
    for (int i = 0; i < NEIGHBOR_LIMIT; i++) {
        predecessor = find_predecessor(bst_root, predecessor);
        if (predecessor != NULL) {
            neighbors[neighbor_count++] = predecessor->key;
        } else {
            break;  // Stop if no more predecessors are found
        }
    }

    // Find NEIGHBOR_LIMIT successors
    TreeNode* successor = target_node;
    for (int i = 0; i < NEIGHBOR_LIMIT; i++) {
        successor = find_successor(bst_root, successor);
        if (successor != NULL) {
            neighbors[neighbor_count++] = successor->key;
        } else {
            break;  // Stop if no more successors are found
        }
    }

    // Print the neighbors if any were found
    if (neighbor_count > 0) {
        for (int i = 0; i < neighbor_count; i++) {
            printf("%d", neighbors[i]);
            if (i < neighbor_count - 1) {
                printf(",");
            }
        }
        printf("\n");
    }
}

int main() {
    int id;
    char operation;
    int max_table_size = 10000;
    HashTable* hash_table = create_table(max_table_size);
    TreeNode* bst_root = NULL;

    // Process each input operation
    while (scanf("%d,%c", &id, &operation) != EOF) {
        switch (operation) {
            case 'I': {  // Insert ID into hash table and BST
                if (insert_key(hash_table, id)) {
                    TreeNode* new_node = create_node(id);
                    if (bst_root == NULL) {
                        bst_root = new_node;
                    } else {
                        insert(bst_root, new_node);
                    }
                }
                break;
            }

            case 'D': {  // Delete ID from hash table and BST
                if (delete_key(hash_table, id)) {
                    TreeNode* node_to_delete = find_key(bst_root, id);
                    if (node_to_delete != NULL) {
                        bst_root = delete_node(bst_root, node_to_delete);
                    }
                }
                break;
            }

            case 'C': {  // Check ID existence and find neighbors
                if (checkIDExists(id, hash_table)) {
                    findNeighboringIDs(id, bst_root);
                }
                break;
            }
        }
    }

    // Cleanup
    clear_table(hash_table);
   

    return 0;
}
