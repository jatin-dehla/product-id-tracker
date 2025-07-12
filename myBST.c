#include "myBST.h"
#include <stdlib.h>
#include <stdio.h>

// Create a new node with the given key
TreeNode* create_node(int key) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->parent = NULL;
    return new_node;
}

// Insert a node into the subtree rooted at root
void insert(TreeNode *root, TreeNode *node) {
    if (root == NULL) {
        root = node;
        return;
    }

    TreeNode* parent = NULL;
    TreeNode* current = root;

    while (current != NULL) {
        parent = current;
        if (node->key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    node->parent = parent;
    if (node->key < parent->key) {
        parent->left = node;
    } else {
        parent->right = node;
    }
}

// Helper function to replace one subtree as a child of its parent with another subtree
TreeNode* transplant(TreeNode *root, TreeNode *u, TreeNode *v) {
    if (u->parent == NULL) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if (v != NULL) {
        v->parent = u->parent;
    }
    return root;
}

// Helper function to find the minimum node in the subtree
TreeNode* tree_min(TreeNode *node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

// Helper function to find the maximum node in the subtree
TreeNode* tree_max(TreeNode *node) {
    while (node->right != NULL) {
        node = node->right;
    }
    return node;
}

// Delete a node from the subtree rooted at root
TreeNode* delete_node(TreeNode *root, TreeNode *node) {
    if (node->left == NULL) {
        root = transplant(root, node, node->right);
    } else if (node->right == NULL) {
        root = transplant(root, node, node->left);
    } else {
        TreeNode* successor = tree_min(node->right);
        if (successor->parent != node) {
            root = transplant(root, successor, successor->right);
            successor->right = node->right;
            successor->right->parent = successor;
        }
        root = transplant(root, node, successor);
        successor->left = node->left;
        successor->left->parent = successor;
    }
    free(node);
    return root;
}

// Find the successor of a node in the subtree rooted at root
TreeNode* find_successor(TreeNode *root, TreeNode *node) {
    if (node->right != NULL) {
        return tree_min(node->right);
    }
    TreeNode *parent = node->parent;
    while (parent != NULL && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

// Find the predecessor of a node in the subtree rooted at root
TreeNode* find_predecessor(TreeNode *root, TreeNode *node) {
    if (node->left != NULL) {
        return tree_max(node->left);
    }
    TreeNode *parent = node->parent;
    while (parent != NULL && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

// Find a node with a given key in the subtree rooted at root
TreeNode* find_key(TreeNode *root, int key) {
    while (root != NULL && root->key != key) {
        if (key < root->key) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return root;
}
