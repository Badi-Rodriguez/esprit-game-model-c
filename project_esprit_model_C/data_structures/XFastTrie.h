#ifndef PROJECT_ESPRIT_MODEL_C_XFASTTRIE_H
#define PROJECT_ESPRIT_MODEL_C_XFASTTRIE_H

#include <vector>
#include <iostream>
#include "HashTable.h"
#include "DoubleList.h"

// Define Node and Leaf structures
template <typename Key, typename Value>
struct XFastLeaf {
    Key key;
    Value value;

    XFastLeaf(Key k, Value v) : key(k), value(v) {}
};

template <typename Key, typename Value>
struct XFastNode {
    XFastNode* left;   // Pointer to left child (0)
    XFastNode* right;  // Pointer to right child (1)
    XFastLeaf<Key, Value>* leaf;  // Pointer to leaf node if it exists

    XFastNode() : left(nullptr), right(nullptr), leaf(nullptr) {}
};

template <typename Key, typename Value>
class XFastTrie {
private:
    static const int BITS = sizeof(Key) * 8;  // Number of bits in the key
    using Node = XFastNode<Key, Value>;
    using Leaf = XFastLeaf<Key, Value>;

    Node* root;  // Root of the trie
    std::vector<HashTable<Key, Node*>> levelHashTables;  // Hash tables for each prefix length
    DoubleList<Leaf*> leafList;  // Linked list of all leaves for range queries

    // Helper: Get the `i`-th bit of a key
    bool getBit(Key key, int i) const {
        return (key >> i) & 1;
    }

public:
    XFastTrie() : root(new Node()), levelHashTables(BITS) {}
    ~XFastTrie() {
        // Recursive deletion of nodes can be implemented here
    }

    void insert(Key key, Value value);
    Leaf* find(Key key);
    Leaf* pred(Key key);
    Leaf* succ(Key key);
    void display() const;
    std::vector<std::string> getCoutVector() const;
};

// Insert a key-value pair into the trie
template <typename Key, typename Value>
void XFastTrie<Key, Value>::insert(Key key, Value value) {
    Node* currentNode = root;

    for (int i = BITS - 1; i >= 0; --i) {
        bool bit = getBit(key, i);

        if (bit == 0) {
            if (currentNode->left == nullptr) {
                currentNode->left = new Node();
            }
            currentNode = currentNode->left;
        } else {
            if (currentNode->right == nullptr) {
                currentNode->right = new Node();
            }
            currentNode = currentNode->right;
        }

        levelHashTables[i].insert(key, currentNode);
    }

    if (currentNode->leaf == nullptr) {
        currentNode->leaf = new Leaf(key, value);
        leafList.push_back(currentNode->leaf);
    } else {
        currentNode->leaf->value = value;
    }
}

// Find a key in the trie
template <typename Key, typename Value>
typename XFastTrie<Key, Value>::Leaf* XFastTrie<Key, Value>::find(Key key) {
    Node* currentNode = root;

    for (int i = BITS - 1; i >= 0; --i) {
        bool bit = getBit(key, i);

        if (bit == 0) {
            if (currentNode->left != nullptr) {
                currentNode = currentNode->left;
            } else {
                return nullptr;
            }
        } else {
            if (currentNode->right != nullptr) {
                currentNode = currentNode->right;
            } else {
                return nullptr;
            }
        }
    }

    return currentNode->leaf;
}

// Find the predecessor of a key
template <typename Key, typename Value>
typename XFastTrie<Key, Value>::Leaf* XFastTrie<Key, Value>::pred(Key key) {
    Leaf* target = find(key);

    if (target != nullptr) {
        auto it = leafList.begin();
        auto prev = it;

        while (it != leafList.end()) {
            if ((*it)->key == key) {
                return prev == it ? nullptr : *prev;
            }
            prev = it;
            ++it;
        }
    }

    return nullptr;
}

// Find the successor of a key
template <typename Key, typename Value>
typename XFastTrie<Key, Value>::Leaf* XFastTrie<Key, Value>::succ(Key key) {
    Leaf* target = find(key);

    if (target != nullptr) {
        auto it = leafList.begin();

        while (it != leafList.end()) {
            if ((*it)->key == key) {
                ++it;
                return it != leafList.end() ? *it : nullptr;
            }
            ++it;
        }
    }

    return nullptr;
}

// Display the trie structure
template <typename Key, typename Value>
void XFastTrie<Key, Value>::display() const {
    std::cout << "X-Fast Trie Structure:\n";

    for (int i = 0; i < BITS; ++i) {
        std::cout << "Level " << i << ":\n";
        auto allNodes = levelHashTables[i].getAllNodes();
        for (const auto& node : allNodes) {
            std::cout << "  Prefix: " << node.key << " -> Node\n";
        }
    }

    std::cout << "Leaf List:\n";
    for (const auto& leaf : leafList) {
        std::cout << "  Key: " << leaf->key << ", Value: " << leaf->value << "\n";
    }
}

// Get a vector for SFML rendering
template <typename Key, typename Value>
std::vector<std::string> XFastTrie<Key, Value>::getCoutVector() const {
    std::vector<std::string> output;

    output.push_back("X-Fast Trie Structure:");
    for (int i = 0; i < BITS; ++i) {
        output.push_back("Level " + std::to_string(i) + ":");
        auto allNodes = levelHashTables[i].getAllNodes();
        for (const auto& node : allNodes) {
            output.push_back("  Prefix: " + std::to_string(node.key) + " -> Node");
        }
    }

    output.push_back("Leaf List:");
    for (const auto& leaf : leafList) {
        output.push_back("  Key: " + std::to_string(leaf->key) + ", Value: " + leaf->value);
    }

    return output;
}

#endif // PROJECT_ESPRIT_MODEL_C_XFASTTRIE_H



