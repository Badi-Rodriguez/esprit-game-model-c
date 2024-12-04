//
// Created by Badi on 12/4/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_YFASTTRIE_H
#define PROJECT_ESPRIT_MODEL_C_YFASTTRIE_H

#include <memory>
#include "XFastTrie.h"
#include "AVL.h"

template <typename Key, typename Value>
class YFastTrie {
private:
    XFastTrie<Key, AVL<Key, Value>*> globalStructure; // X-Fast Trie storing pointers to AVL trees
    std::unordered_map<Key, std::unique_ptr<AVL<Key, Value>>> clusterMap; // Use smart pointers for clusters

    // Helper to find the cluster for a key
    AVL<Key, Value>* findCluster(Key key) {
        auto predNode = globalStructure.pred(key);
        if (predNode) {
            std::cout << "Predecessor cluster found for key: " << key << ", Representative: " << predNode->key << "\n";
            return predNode->value; // `value` is a pointer to AVL
        }

        auto succNode = globalStructure.succ(key);
        if (succNode) {
            std::cout << "Successor cluster found for key: " << key << ", Representative: " << succNode->key << "\n";
            return succNode->value; // `value` is a pointer to AVL
        }

        std::cout << "No cluster found for key: " << key << "\n";
        return nullptr;
    }

public:
    YFastTrie() = default;

    ~YFastTrie() = default; // Smart pointers clean up automatically\\

    const std::unordered_map<Key, std::unique_ptr<AVL<Key, Value>>>& getClusterMap() const {
        return clusterMap;
    }


    void insert(Key key, Value value) {
        std::cout << "Inserting key: " << key << " with value: " << value << "\n";
        AVL<Key, Value>* cluster = findCluster(key);

        if (!cluster) {
            std::cout << "No cluster found for key: " << key << ". Creating new cluster.\n";
            auto newCluster = std::make_unique<AVL<Key, Value>>();
            newCluster->insert(key, value);
            Key representativeKey = newCluster->findMinKey();

            // Insert into globalStructure and clusterMap
            globalStructure.insert(representativeKey, newCluster.get());
            clusterMap[representativeKey] = std::move(newCluster);
        } else {
            cluster->insert(key, value);

            // Update representative if necessary
            Key newMinKey = cluster->findMinKey();
            if (key == newMinKey) {
                globalStructure.remove(newMinKey); // Remove old representative
                globalStructure.insert(key, cluster); // Insert updated representative
            }
        }
    }

    void remove(Key key) {
        AVL<Key, Value>* cluster = findCluster(key);
        if (!cluster) return;

        cluster->remove(key);

        if (cluster->isEmpty()) {
            Key representativeKey = cluster->findMinKey();
            globalStructure.remove(representativeKey);
            clusterMap.erase(representativeKey);
        } else if (key == cluster->findMinKey()) {
            globalStructure.remove(key);
            globalStructure.insert(cluster->findMinKey(), cluster);
        }
    }

    Value* search(Key key) {
        AVL<Key, Value>* cluster = findCluster(key);
        return cluster ? cluster->search(key) : nullptr;
    }

    std::pair<Key, Value> predecessor(Key key) {
        AVL<Key, Value>* cluster = findCluster(key);
        if (cluster) {
            auto predNode = cluster->pred(key);
            if (predNode) {
                return {predNode->key, predNode->value};
            }
        }

        auto globalPred = globalStructure.pred(key);
        if (globalPred && globalPred->value) {
            auto clusterPred = globalPred->value->findMax();
            return {clusterPred->key, clusterPred->value};
        }

        return {Key(), Value()}; // No predecessor
    }

    std::pair<Key, Value> successor(Key key) {
        AVL<Key, Value>* cluster = findCluster(key);
        if (cluster) {
            auto succNode = cluster->succ(key);
            if (succNode) return {succNode->key, succNode->value};
        }

        auto globalSucc = globalStructure.succ(key);
        if (globalSucc && globalSucc->value) {
            auto clusterSucc = globalSucc->value->findMin();
            return {clusterSucc->key, clusterSucc->value};
        }

        return {Key(), Value()}; // No successor
    }

    void display() const {
        std::cout << "Y-Fast Trie Contents:\n";

        for (const auto& [key, clusterPtr] : clusterMap) {
            std::cout << "Cluster Representative Key: " << key << "\n";
            if (clusterPtr) {
                std::cout << "AVL Tree Contents:\n";
                clusterPtr->display();
            } else {
                std::cout << "ERROR: Cluster is null for key " << key << "\n";
            }
            std::cout << "-----------------------------\n";
        }
    }
};
#endif //PROJECT_ESPRIT_MODEL_C_YFASTTRIE_H
