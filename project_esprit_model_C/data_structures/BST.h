#ifndef PROJECT_ESPRIT_MODEL_C_BST_H
#define PROJECT_ESPRIT_MODEL_C_BST_H

template <typename T>
struct BSTNode {
    T data;
    BSTNode* left;
    BSTNode* right;

    // Constructor to create a new node
    BSTNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
private:
    BSTNode<T>* root;

    // Helper function to recursively insert a value into the BST
    BSTNode<T>* insert(BSTNode<T>* node, T value);

    // Helper function to search for a value in the BST
    BSTNode<T>* search(BSTNode<T>* node, T value);

    // Helper function to perform an in-order traversal
    void inorderTraversal(BSTNode<T>* node);

    // Helper function to delete a node from the BST
    BSTNode<T>* deleteNode(BSTNode<T>* root, T key);

public:
    // Constructor to initialize the BST
    BST();

    // Function to insert a value into the BST
    void insert(T value);

    // Function to search for a value in the BST (now returns a pointer to BSTNode)
    BSTNode<T>* search(T value);

    // Function to delete a value from the BST
    void deleteNode(T value);

    // Function to perform an in-order traversal of the BST
    void inorderTraversal();

    // Helper function to find the minimum node in the BST
    BSTNode<T>* findMin(BSTNode<T>* node);
};

#endif //PROJECT_ESPRIT_MODEL_C_BST_H

