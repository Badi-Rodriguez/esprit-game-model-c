//
// Created by Badi on 12/4/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_MOCK_YFASTTRIE_H
#define PROJECT_ESPRIT_MODEL_C_MOCK_YFASTTRIE_H

#include "XFastTrie.h"
#include "AVL.h"
#include <iostream>
#include <unordered_map>

template <typename Key, typename Value>
class MockYFastTrie {
private:
    XFastTrie<Key, AVL<Key, Value>> globalStructure;  // X-Fast Trie to store clusters
    std::unordered_map<Key, AVL<Key, Value>*> clusterMap;  // Cluster management

public:
    MockYFastTrie() = default;

    ~MockYFastTrie() {
        for (auto& entry : clusterMap) {
            delete entry.second;
        }
    }

    void insert(Key key, Value value) {
        // Find or create a cluster
        if (clusterMap.find(key) == clusterMap.end()) {
            auto* cluster = new AVL<Key, Value>();
            cluster->insert(key, value);
            clusterMap[key] = cluster;
            globalStructure.insert(key, *cluster);
        } else {
            clusterMap[key]->insert(key, value);
        }
    }

    Value* search(Key key) {
        if (clusterMap.find(key) != clusterMap.end()) {
            return clusterMap[key]->search(key);
        }
        return nullptr;
    }

    void display() const {
        std::cout << "Mock Y-Fast Trie Contents:\n";
        for (const auto& entry : clusterMap) {
            std::cout << "Cluster Representative Key: " << entry.first << "\n";
            entry.second->display();
            std::cout << "-----------------------------\n";
        }
    }
};

#endif //PROJECT_ESPRIT_MODEL_C_MOCK_YFASTTRIE_H

