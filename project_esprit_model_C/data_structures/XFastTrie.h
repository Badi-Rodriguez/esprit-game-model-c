#ifndef PROJECT_ESPRIT_MODEL_C_XFASTTRIE_H
#define PROJECT_ESPRIT_MODEL_C_XFASTTRIE_H

#include <vector>
#include <iostream>
#include <functional>
#include <bitset>
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
        std::function<void(Node*)> deleteNodes = [&](Node* node) {
            if (!node) return;
            deleteNodes(node->left);
            deleteNodes(node->right);
            delete node->leaf;
            delete node;
        };
        deleteNodes(root);
    }



    void insert(Key key, const Value &value);
    Leaf* find(Key key);
    Leaf* pred(Key key);
    Leaf* succ(Key key);
    void display() const;
    std::vector<std::string> getCoutVector() const;
    void remove(Key key);

};

// Insert a key-value pair into the trie
template <typename Key, typename Value>
void XFastTrie<Key, Value>::insert(Key key, const Value& value) {
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

// Complexity: O(log U), where U is the size of the key space (2^BITS).
// Traversal occurs for each bit in the key, and hash table operations are O(1) in the average case.

template<typename Key, typename Value>
void XFastTrie<Key, Value>::remove(Key key) {
    Node* currentNode = root;

    for (int i = BITS - 1; i >= 0; --i) {
        bool bit = getBit(key, i);

        if (bit == 0) {
            if (currentNode->left) {
                currentNode = currentNode->left;
            } else {
                return; // Key does not exist
            }
        } else {
            if (currentNode->right) {
                currentNode = currentNode->right;
            } else {
                return; // Key does not exist
            }
        }

        levelHashTables[i].remove(key); // Remove key from hash table
    }

    // Remove leaf node and update leafList
    if (currentNode->leaf) {
        leafList.remove(currentNode->leaf);
        delete currentNode->leaf;
        currentNode->leaf = nullptr;
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

// Complexity: O(log U). Traverses the trie once, checking each bit of the key.

// Find the predecessor of a key
template <typename Key, typename Value>
typename XFastTrie<Key, Value>::Leaf* XFastTrie<Key, Value>::pred(Key key) {
    Key prefix = key >> 1;  // Start with the most significant bit
    for (int i = BITS - 1; i >= 0; --i) {
        if (levelHashTables[i].contains(prefix)) {
            Node* predecessorNode = levelHashTables[i].get(prefix);
            while (predecessorNode->right) {
                predecessorNode = predecessorNode->right;  // Go right to find predecessor
            }
            return predecessorNode->leaf;
        }
        prefix >>= 1;  // Move to a shorter prefix
    }
    return nullptr;
}
// Complexity: O(log U). Traverses up to log U levels of the trie, performing O(1) operations per level.

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
// Complexity: O(log U) for finding the key and O(1) for finding the next element in the leaf list.


// Display the trie structure
template <typename Key, typename Value>
void XFastTrie<Key, Value>::display() const {
    std::cout << "X-Fast Trie Structure:\n";

    for (int i = 0; i < BITS; ++i) {
        std::cout << "Level " << i << ":\n";
        auto allNodes = levelHashTables[i].getAllNodes();
        for (const auto& node : allNodes) {
            // Extract the prefix for the current level
            Key prefix = node.key >> (BITS - 1 - i);
            std::cout << "  Prefix: " << std::bitset<32>(prefix).to_string().substr(32 - (i + 1)) << " -> Node\n";
        }
    }

    std::cout << "Leaf List:\n";
    for (const auto& leaf : leafList) {
        std::cout << "  Key: " << leaf->key << ", Value: " << leaf->value << "\n";
    }
}
// Complexity: O(U), where U is the number of nodes in the trie. Iterates over all levels and nodes.

// Get a vector for SFML rendering
template <typename Key, typename Value>
std::vector<std::string> XFastTrie<Key, Value>::getCoutVector() const {
    std::vector<std::string> output;

    output.emplace_back("X-Fast Trie Structure:");
    for (int i = 0; i < BITS; ++i) {
        output.emplace_back("Level " + std::to_string(i) + ":");
        auto allNodes = levelHashTables[i].getAllNodes();
        for (const auto& node : allNodes) {
            // Extract the prefix for the current level
            Key prefix = node.key >> (BITS - 1 - i);
            std::string prefixStr = std::bitset<32>(prefix).to_string().substr(32 - (i + 1));
            output.emplace_back("  Prefix: " + prefixStr + " -> Node");
        }
    }

    output.emplace_back("Leaf List:");
    for (const auto& leaf : leafList) {
        output.emplace_back("  Key: " + std::to_string(leaf->key) + ", Value: " + leaf->value);
    }

    return output;
}
// Complexity: O(U), where U is the number of nodes in the trie. Iterates over all levels and nodes.

#endif // PROJECT_ESPRIT_MODEL_C_XFASTTRIE_H



