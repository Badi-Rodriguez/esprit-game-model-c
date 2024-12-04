//
// Created by Badi on 12/4/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_AVL_H
#define PROJECT_ESPRIT_MODEL_C_AVL_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <functional>

template <typename Key, typename Value>
class AVL {
private:
    struct AVLNode {
        Key key;
        Value value;
        int height;
        AVLNode* left;
        AVLNode* right;

        AVLNode(Key k, Value v)
                : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
    };

    AVLNode* root;

    // AVL helper functions
    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Update heights
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        // Return new root
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Update heights
        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        // Return new root
        return y;
    }

    AVLNode* balance(AVLNode* node) {
        if (!node) return node;

        // Update height
        node->height = std::max(height(node->left), height(node->right)) + 1;

        // Check balance factor
        int bf = balanceFactor(node);

        // Left-heavy
        if (bf > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }

        // Right-heavy
        if (bf < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* insert(AVLNode* node, Key key, Value value) {
        if (!node) return new AVLNode(key, value);

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        } else if (key > node->key) {
            node->right = insert(node->right, key, value);
        } else {
            node->value = value;  // Update value if key already exists
            return node;
        }

        return balance(node);
    }
    // Complexity: O(log n)

    // Complexity: O(log n)

    AVLNode* removeMin(AVLNode* node) {
        if (!node->left) return node->right;
        node->left = removeMin(node->left);
        return balance(node);
    }
    // Complexity: O(log n)

    AVLNode* remove(AVLNode* node, Key key) {
        if (!node) return nullptr; // Base case: Key not found

        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            // Node to be deleted found
            AVLNode* left = node->left;
            AVLNode* right = node->right;
            delete node; // Free memory

            // Case 1: No right child, return left subtree
            if (!right) return left;

            // Case 2: Find the minimum in the right subtree
            AVLNode* min = findMin(right);

            // Reassign pointers
            min->right = removeMin(right); // Remove the minimum node
            min->left = left;

            // Return balanced subtree
            return balance(min);
        }

        return balance(node); // Balance the current node
    }

    void displayHelper(AVLNode* node, int depth) const {
        if (!node) return;

        // Right subtree
        displayHelper(node->right, depth + 1);

        // Current node
        std::cout << std::string(depth * 4, ' ') << node->key << ": " << node->value << " (Height: " << node->height << ")\n";

        // Left subtree
        displayHelper(node->left, depth + 1);
    }

public:
    AVL() : root(nullptr) {}
    ~AVL() {
        std::function<void(AVLNode*)> deleteNodes = [&](AVLNode* node) {
            if (!node) return;
            deleteNodes(node->left);
            deleteNodes(node->right);
            delete node;
        };
        deleteNodes(root);
    }


    // Public interface
    void insert(Key key, Value value) {
        root = insert(root, key, value);
    }
    // Complexity: O(log n)

    void remove(Key key) {
        root = remove(root, key);
    }
    // Complexity: O(log n)

    Value* search(Key key) {
        AVLNode* current = root;
        while (current) {
            if (key < current->key) {
                current = current->left;
            } else if (key > current->key) {
                current = current->right;
            } else {
                return &(current->value);
            }
        }
        return nullptr;
    }
    // Complexity per level: O(1)
    // General complexity: O(Log n)

    Key findMinKey() {
        AVLNode* minNode = findMin(root);
        return minNode ? minNode->key : Key();
    }
    // Complexity: O(log n)

    Key findMaxKey() {
        AVLNode* current = root;
        while (current && current->right) {
            current = current->right;
        }
        return current ? current->key : Key();
    }
    // Complexity: O(log n)
    AVLNode* findMin(AVLNode* node) {
        return node->left ? findMin(node->left) : node;
    }

    AVLNode* findMin() {
        return findMin(root); // Call the recursive helper
    }

    AVLNode* findMax() {
        return findMax(root); // Add a recursive helper similar to `findMin`
    }

// Example of `findMax` helper
    AVLNode* findMax(AVLNode* node) {
        return node->right ? findMax(node->right) : node;
    }

    AVLNode* pred(AVLNode* node, Key key) {
        if (!node) return nullptr;

        if (key <= node->key) {
            return pred(node->left, key);
        } else {
            AVLNode* temp = pred(node->right, key);
            return temp ? temp : node;
        }
    }

    AVLNode* succ(AVLNode* node, Key key) {
        if (!node) return nullptr;

        if (key >= node->key) {
            return succ(node->right, key);
        } else {
            AVLNode* temp = succ(node->left, key);
            return temp ? temp : node;
        }
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void display() const {
        if (!root) {
            std::cout << "AVL Tree is empty.\n";
            return;
        }
        std::cout << "AVL Tree Contents:\n";
        displayHelper(root, 0);
    }

// Wrappers for `pred` and `succ`
    AVLNode* pred(Key key) {
        return pred(root, key);
    }

    AVLNode* succ(Key key) {
        return succ(root, key);
    }

    void visualizeAVL(sf::RenderWindow &window, int x, int y, sf::Font consoleFont) const {
        if (!root) return;

        const int NODE_RADIUS = 15;
        const int OFFSET_X = 50;
        const int OFFSET_Y = 50;

        std::function<void(AVLNode *, int, int)> drawNode = [&](AVLNode *node, int posX, int posY) {
            if (!node) return;

            // Draw current node
            sf::CircleShape nodeShape(NODE_RADIUS);
            nodeShape.setFillColor(sf::Color::Green);
            nodeShape.setPosition(posX, posY);

            sf::Text nodeLabel;
            nodeLabel.setFont(consoleFont);
            nodeLabel.setCharacterSize(14);
            nodeLabel.setFillColor(sf::Color::Black);
            nodeLabel.setString(std::to_string(node->key));
            nodeLabel.setPosition(posX + 5, posY + 5);

            window.draw(nodeShape);
            window.draw(nodeLabel);

            // Draw left child
            if (node->left) {
                sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(posX + NODE_RADIUS, posY + NODE_RADIUS)),
                        sf::Vertex(sf::Vector2f(posX - OFFSET_X + NODE_RADIUS, posY + OFFSET_Y + NODE_RADIUS))
                };
                window.draw(line, 2, sf::Lines);
                drawNode(node->left, posX - OFFSET_X, posY + OFFSET_Y);
            }

            // Draw right child
            if (node->right) {
                sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(posX + NODE_RADIUS, posY + NODE_RADIUS)),
                        sf::Vertex(sf::Vector2f(posX + OFFSET_X + NODE_RADIUS, posY + OFFSET_Y + NODE_RADIUS))
                };
                window.draw(line, 2, sf::Lines);
                drawNode(node->right, posX + OFFSET_X, posY + OFFSET_Y);
            }
        };

        drawNode(root, x, y);
    }

};



#endif //PROJECT_ESPRIT_MODEL_C_AVL_H
