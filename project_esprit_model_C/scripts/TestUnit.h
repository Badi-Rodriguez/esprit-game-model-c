//
// Created by Badi on 12/4/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_TESTUNIT_H
#define PROJECT_ESPRIT_MODEL_C_TESTUNIT_H

#include <iostream>
#include "../data_structures/DoubleList.h"
#include "../data_structures/HashTable.h"
#include "../data_structures/XFastTrie.h"
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

void testXFastTrie() {
    std::cout << "Testing XFastTrie...\n";

    // Create an XFastTrie instance
    XFastTrie<int, std::string> xFastTrie;

    // Test 1: Insert elements
    xFastTrie.insert(10, "Ten");
    xFastTrie.insert(5, "Five");
    xFastTrie.insert(15, "Fifteen");
    xFastTrie.insert(7, "Seven");
    xFastTrie.insert(12, "Twelve");

    std::cout << "Inserted elements into XFastTrie.\n";

    // Test 2: Find keys
    auto foundLeaf = xFastTrie.find(10);
    if (foundLeaf) {
        std::cout << "Find key 10: Found with value = " << foundLeaf->value << "\n";
    } else {
        std::cout << "Find key 10: Not Found\n";
    }

    foundLeaf = xFastTrie.find(20);
    if (foundLeaf) {
        std::cout << "Find key 20: Found with value = " << foundLeaf->value << "\n";
    } else {
        std::cout << "Find key 20: Not Found\n";
    }

    // Test 3: Predecessor
    auto predLeaf = xFastTrie.pred(12);
    if (predLeaf) {
        std::cout << "Predecessor of 12: Key = " << predLeaf->key << ", Value = " << predLeaf->value << "\n";
    } else {
        std::cout << "Predecessor of 12: Not Found\n";
    }

    predLeaf = xFastTrie.pred(5);  // Edge case: No predecessor
    if (predLeaf) {
        std::cout << "Predecessor of 5: Key = " << predLeaf->key << ", Value = " << predLeaf->value << "\n";
    } else {
        std::cout << "Predecessor of 5: Not Found\n";
    }

    // Test 4: Successor
    auto succLeaf = xFastTrie.succ(7);
    if (succLeaf) {
        std::cout << "Successor of 7: Key = " << succLeaf->key << ", Value = " << succLeaf->value << "\n";
    } else {
        std::cout << "Successor of 7: Not Found\n";
    }

    succLeaf = xFastTrie.succ(15);  // Edge case: No successor
    if (succLeaf) {
        std::cout << "Successor of 15: Key = " << succLeaf->key << ", Value = " << succLeaf->value << "\n";
    } else {
        std::cout << "Successor of 15: Not Found\n";
    }

    // Test 5: Display structure
    std::cout << "\nTrie Structure:\n";
    xFastTrie.display();

    // Test 6: Get vector for SFML rendering
    auto outputVector = xFastTrie.getCoutVector();
    std::cout << "\nOutput vector (for SFML rendering):\n";
    for (const auto& line : outputVector) {
        std::cout << line << "\n";
    }

    std::cout << "XFastTrie test completed.\n";
}



#endif //PROJECT_ESPRIT_MODEL_C_TESTUNIT_H
