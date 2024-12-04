//
// Created by Badi on 12/4/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_TESTUNIT_H
#define PROJECT_ESPRIT_MODEL_C_TESTUNIT_H

#include <iostream>
#include "../data_structures/DoubleList.h"
#include "../data_structures/HashTable.h"
#include "../data_structures/XFastTrie.h"
#include "../data_structures/AVL.h"
#include "../data_structures/YFastTrie.h"
#include "Item.h"

// Test function

void TestDoubleList() {
    std::cout << "Testing DoubleList...\n";

    DoubleList<int> list;

    // Test push_back
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    std::cout << "After push_back: ";
    for (const auto& value : list) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Test push_front
    list.push_front(5);
    list.push_front(1);
    std::cout << "After push_front: ";
    for (const auto& value : list) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Test pop_front
    list.pop_front();
    std::cout << "After pop_front: ";
    for (const auto& value : list) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Test pop_back
    list.pop_back();
    std::cout << "After pop_back: ";
    for (const auto& value : list) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Test find
    int searchValue = 10;
    auto node = list.find(searchValue);
    std::cout << "Find " << searchValue << ": "
              << (node ? "Found" : "Not Found") << "\n";

    // Test remove
    list.remove(20);
    std::cout << "After remove(20): ";
    for (const auto& value : list) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    // Test to_vector
    auto vectorRepresentation = list.to_vector();
    std::cout << "Vector representation: ";
    for (const auto& value : vectorRepresentation) {
        std::cout << value << " ";
    }
    std::cout << "\n";

    std::cout << "DoubleList test completed.\n";
}

void TestHashTable() {
    std::cout << "Testing HashTable...\n";

    HashTable<int, std::string> hashTable;

    // Test insert
    hashTable.insert(1, "One");
    hashTable.insert(2, "Two");
    hashTable.insert(3, "Three");
    std::cout << "Inserted key-value pairs.\n";

    // Test get
    std::cout << "Get key 2: " << hashTable.get(2) << "\n";

    // Test contains
    int keyToCheck = 3;
    std::cout << "Contains key " << keyToCheck << ": "
              << (hashTable.contains(keyToCheck) ? "Yes" : "No") << "\n";

    // Test remove
    hashTable.remove(2);
    std::cout << "Removed key 2.\n";

    // Verify removal
    std::cout << "Contains key 2 after removal: "
              << (hashTable.contains(2) ? "Yes" : "No") << "\n";

    // Test iteration through all elements
    auto allNodes = hashTable.getAllNodes();
    std::cout << "All key-value pairs: ";
    for (const auto& node : allNodes) {
        std::cout << "{" << node.key << ": " << node.value << "} ";
    }
    std::cout << "\n";

    std::cout << "HashTable test completed.\n";
}

void TestXFastTrie() {
    std::cout << "Testing XFastTrie...\n";

    // Create an XFastTrie instance
    XFastTrie<int, std::string> xFastTrie;

    // Test 1: Insert elements
    std::cout << "Test 1: Insert elements\n";
    xFastTrie.insert(10, "Ten");
    xFastTrie.insert(5, "Five");
    xFastTrie.insert(15, "Fifteen");
    xFastTrie.insert(7, "Seven");
    xFastTrie.insert(12, "Twelve");
    std::cout << "Inserted elements into XFastTrie.\n";

    // Test 2: Find keys
    std::cout << "\nTest 2: Find keys\n";
    auto foundLeaf = xFastTrie.find(10);
    std::cout << "Find key 10: " << (foundLeaf ? "Found, Value = " + foundLeaf->value : "Not Found") << "\n";

    foundLeaf = xFastTrie.find(20);
    std::cout << "Find key 20: " << (foundLeaf ? "Found, Value = " + foundLeaf->value : "Not Found") << "\n";

    // Test 3: Predecessor
    std::cout << "\nTest 3: Predecessor\n";
    auto predLeaf = xFastTrie.pred(12);
    std::cout << "Predecessor of 12: " << (predLeaf ? "Key = " + std::to_string(predLeaf->key) + ", Value = " + predLeaf->value : "Not Found") << "\n";

    predLeaf = xFastTrie.pred(5);  // Edge case: No predecessor
    std::cout << "Predecessor of 5: " << (predLeaf ? "Key = " + std::to_string(predLeaf->key) + ", Value = " + predLeaf->value : "Not Found") << "\n";

    // Test 4: Successor
    std::cout << "\nTest 4: Successor\n";
    auto succLeaf = xFastTrie.succ(7);
    std::cout << "Successor of 7: " << (succLeaf ? "Key = " + std::to_string(succLeaf->key) + ", Value = " + succLeaf->value : "Not Found") << "\n";

    succLeaf = xFastTrie.succ(15);  // Edge case: No successor
    std::cout << "Successor of 15: " << (succLeaf ? "Key = " + std::to_string(succLeaf->key) + ", Value = " + succLeaf->value : "Not Found") << "\n";

    // Test 5: Display structure
    std::cout << "\nTest 5: Display structure\n";
    xFastTrie.display();

    // Test 6: Get vector for SFML rendering
    std::cout << "\nTest 6: Get vector for SFML rendering\n";
    auto outputVector = xFastTrie.getCoutVector();
    for (const auto& line : outputVector) {
        std::cout << line << "\n";
    }

    // Test 7: Empty trie operations
    std::cout << "\nTest 7: Edge cases\n";
    XFastTrie<int, std::string> emptyTrie;
    std::cout << "Empty Trie - Find key 1: " << (emptyTrie.find(1) ? "Found" : "Not Found") << "\n";
    std::cout << "Empty Trie - Predecessor of key 1: " << (emptyTrie.pred(1) ? "Found" : "Not Found") << "\n";
    std::cout << "Empty Trie - Successor of key 1: " << (emptyTrie.succ(1) ? "Found" : "Not Found") << "\n";

    std::cout << "XFastTrie test completed.\n";
};

void TestAVL() {
    std::cout << "Testing AVL Tree...\n";

    // Create an instance of AVL
    AVL<int, std::string> avlTree;

    // Test 1: Insert elements
    avlTree.insert(10, "Ten");
    avlTree.insert(20, "Twenty");
    avlTree.insert(5, "Five");
    avlTree.insert(15, "Fifteen");
    avlTree.insert(25, "Twenty-Five");

    std::cout << "Inserted elements into AVL Tree.\n";

    // Test 2: Search elements
    auto value = avlTree.search(10);
    std::cout << "Search key 10: " << (value ? "Found with value = " + *value : "Not Found") << "\n";

    value = avlTree.search(30);
    std::cout << "Search key 30: " << (value ? "Found with value = " + *value : "Not Found") << "\n";

    // Test 3: Find minimum and maximum
    int minKey = avlTree.findMinKey();
    std::cout << "Minimum key: " << minKey << "\n";

    int maxKey = avlTree.findMaxKey();
    std::cout << "Maximum key: " << maxKey << "\n";

    // Test 4: Remove elements
    avlTree.remove(20);
    std::cout << "Removed key 20.\n";

    value = avlTree.search(20);
    std::cout << "Search key 20 after removal: " << (value ? "Found with value = " + *value : "Not Found") << "\n";

    avlTree.remove(5);
    std::cout << "Removed key 5.\n";

    value = avlTree.search(5);
    std::cout << "Search key 5 after removal: " << (value ? "Found with value = " + *value : "Not Found") << "\n";

    // Test 5: Edge cases
    avlTree.remove(10); // Removing the root
    std::cout << "Removed root key 10.\n";

    value = avlTree.search(10);
    std::cout << "Search key 10 after removal: " << (value ? "Found with value = " + *value : "Not Found") << "\n";

    // Check updated min and max
    minKey = avlTree.findMinKey();
    std::cout << "Minimum key after removals: " << minKey << "\n";

    maxKey = avlTree.findMaxKey();
    std::cout << "Maximum key after removals: " << maxKey << "\n";

    std::cout << "AVL Tree test completed.\n";
}

void TestYFastTrie() {
    std::cout << "Testing YFastTrie...\n";

    // Create a YFastTrie instance
    YFastTrie<int, std::string> yFastTrie;

    // Test 1: Insert elements
    yFastTrie.insert(10, "Ten");
    yFastTrie.insert(5, "Five");
    yFastTrie.insert(15, "Fifteen");
    yFastTrie.insert(7, "Seven");
    yFastTrie.insert(12, "Twelve");

    std::cout << "Inserted elements into YFastTrie.\n";

    // Test 2: Search for keys
    auto value = yFastTrie.search(10);
    if (value) {
        std::cout << "Search key 10: Found, Value = " << *value << "\n";
    } else {
        std::cout << "Search key 10: Not Found\n";
    }

    value = yFastTrie.search(20);
    if (value) {
        std::cout << "Search key 20: Found, Value = " << *value << "\n";
    } else {
        std::cout << "Search key 20: Not Found\n";
    }

    // Test 3: Predecessor queries
    auto pred = yFastTrie.predecessor(12);
    if (pred.first) {
        std::cout << "Predecessor of 12: Key = " << pred.first << ", Value = " << pred.second << "\n";
    } else {
        std::cout << "Predecessor of 12: Not Found\n";
    }

    pred = yFastTrie.predecessor(5);
    if (pred.first) {
        std::cout << "Predecessor of 5: Key = " << pred.first << ", Value = " << pred.second << "\n";
    } else {
        std::cout << "Predecessor of 5: Not Found\n";
    }

    // Test 4: Successor queries
    auto succ = yFastTrie.successor(7);
    if (succ.first) {
        std::cout << "Successor of 7: Key = " << succ.first << ", Value = " << succ.second << "\n";
    } else {
        std::cout << "Successor of 7: Not Found\n";
    }

    succ = yFastTrie.successor(15);
    if (succ.first) {
        std::cout << "Successor of 15: Key = " << succ.first << ", Value = " << succ.second << "\n";
    } else {
        std::cout << "Successor of 15: Not Found\n";
    }

    // Test 5: Remove elements
    yFastTrie.remove(7);
    std::cout << "Removed key 7.\n";

    value = yFastTrie.search(7);
    if (value) {
        std::cout << "Search key 7 after removal: Found, Value = " << *value << "\n";
    } else {
        std::cout << "Search key 7 after removal: Not Found\n";
    }

    pred = yFastTrie.predecessor(12);
    if (pred.first) {
        std::cout << "Predecessor of 12 after removing 7: Key = " << pred.first << ", Value = " << pred.second << "\n";
    } else {
        std::cout << "Predecessor of 12 after removing 7: Not Found\n";
    }

    succ = yFastTrie.successor(12);
    if (succ.first) {
        std::cout << "Successor of 12 after removing 7: Key = " << succ.first << ", Value = " << succ.second << "\n";
    } else {
        std::cout << "Successor of 12 after removing 7: Not Found\n";
    }

    std::cout << "YFastTrie test completed.\n";
}

#endif //PROJECT_ESPRIT_MODEL_C_TESTUNIT_H
