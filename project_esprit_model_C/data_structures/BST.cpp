#include "BST.h"
#include <iostream>

// Constructor to initialize the BST
template <typename T>
BST<T>::BST() : root(nullptr) {}

// Helper function to recursively insert a value into the BST
template <typename T>
BSTNode<T>* BST<T>::insert(BSTNode<T>* node, T value) {
    if (node == nullptr) {
        return new BSTNode<T>(value);
    }

    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    }

    return node; // return the unchanged node pointer
}

// Function to insert a value into the BST
template <typename T>
void BST<T>::insert(T value) {
    root = insert(root, value);
}

// Helper function to search for a value in the BST (returns pointer to node)
template <typename T>
BSTNode<T>* BST<T>::search(BSTNode<T>* node, T value) {
    if (node == nullptr || node->data == value) {
        return node;
    }

    if (value < node->data) {
        return search(node->left, value);  // Continue searching left
    }

    return search(node->right, value);  // Continue searching right
}

// Function to search for a value in the BST
template <typename T>
BSTNode<T>* BST<T>::search(T value) {
    return search(root, value);  // Use the helper function
}

// Helper function to perform an in-order traversal
template <typename T>
void BST<T>::inorderTraversal(BSTNode<T>* node) {
    if (node == nullptr) {
        return;
    }

    inorderTraversal(node->left);
    std::cout << node->data << " ";
    inorderTraversal(node->right);
}

// Function to perform an in-order traversal of the BST
template <typename T>
void BST<T>::inorderTraversal() {
    inorderTraversal(root);
    std::cout << std::endl;
}

// Helper function to find the minimum node in the BST
template <typename T>
BSTNode<T>* BST<T>::findMin(BSTNode<T>* node) {
    while (node && node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Helper function to delete a node from the BST
template <typename T>
BSTNode<T>* BST<T>::deleteNode(BSTNode<T>* root, T key) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->data) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->data) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node to be deleted found

        // Node has one or no children
        if (root->left == nullptr) {
            BSTNode<T>* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            BSTNode<T>* temp = root->left;
            delete root;
            return temp;
        }

        // Node has two children: Get the inorder successor (smallest in the right subtree)
        BSTNode<T>* temp = findMin(root->right);

        // Copy the inorder successor's content to this node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to delete a value from the BST
template <typename T>
void BST<T>::deleteNode(T value) {
    root = deleteNode(root, value);
}

// Explicit template instantiation
template class BST<int>;
template class BST<float>;
template class BST<std::string>;

