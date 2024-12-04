//
// Created by Badi on 12/4/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_YFASTTRIE_H
#define PROJECT_ESPRIT_MODEL_C_YFASTTRIE_H


#include "XFastTrie.h"
#include "AVL.h"

template <typename Key, typename Value>
class YFastTrie {
private:
    XFastTrie<Key, AVL<Key, Value>> globalStructure; // X-Fast Trie storing AVL trees
    std::unordered_map<Key, AVL<Key, Value>*> clusterMap; // Map for cluster management

    // Helper to find the cluster for a key
    AVL<Key, Value>* findCluster(Key key) {
        auto clusterNode = globalStructure.pred(key); // Find predecessor cluster
        if (clusterNode) {
            return &clusterNode->value; // Return the AVL cluster
        }
        return nullptr; // No cluster found
    }


public:
    YFastTrie() = default;

    void insert(Key key, Value value) {
        AVL<Key, Value>* cluster = findCluster(key);

        if (!cluster) {
            // If no cluster exists, create a new one
            cluster = new AVL<Key, Value>();
            cluster->insert(key, value);
            clusterMap[key] = cluster;

            // Insert into globalStructure with the new representative (minimum key of the cluster)
            globalStructure.insert(key, *cluster);
        } else {
            cluster->insert(key, value);

            // Update representative in globalStructure if necessary
            if (key < cluster->findMin()->key) {
                globalStructure.remove(cluster->findMin()->key); // Remove old representative
                globalStructure.insert(key, *cluster); // Insert updated representative
            }
        }
    }

    void remove(Key key) {
        AVL<Key, Value>* cluster = findCluster(key);

        if (!cluster) return; // Key doesn't exist

        cluster->remove(key);

        // If the cluster becomes empty, clean up
        if (cluster->isEmpty()) {
            globalStructure.remove(key);
            clusterMap.erase(key);
            delete cluster;
        }
        else if (key == cluster->findMin()->key) {
            // Update representative in globalStructure if minimum key is removed
            globalStructure.remove(key);
            globalStructure.insert(cluster->findMin()->key, *cluster);
        }
    };

    Value* search(Key key) {
        AVL<Key, Value>* cluster = findCluster(key);

        if (!cluster){
            return nullptr;
        };

        return cluster->search(key);
    }

    // Predecessor and successor
    std::pair<Key, Value> predecessor(Key key) {
        AVL<Key, Value>* cluster = findCluster(key);

        if (cluster) {
            auto predNode = cluster->pred(key);
            if (predNode) return {predNode->key, predNode->value};
        }

        // If no local predecessor, check globalStructure
        auto globalPred = globalStructure.pred(key);
        if (globalPred) {
            auto clusterPred = globalPred->value.findMax();
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

        // If no local successor, check globalStructure
        auto globalSucc = globalStructure.succ(key);
        if (globalSucc) {
            auto clusterSucc = globalSucc->value.findMin();
            return {clusterSucc->key, clusterSucc->value};
        }

        return {Key(), Value()}; // No successor
    };

};

#endif //PROJECT_ESPRIT_MODEL_C_YFASTTRIE_H
