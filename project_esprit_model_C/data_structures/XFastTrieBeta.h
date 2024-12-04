//
// Created by Badi on 12/4/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_XFASTTRIEBETA_H
#define PROJECT_ESPRIT_MODEL_C_XFASTTRIEBETA_H

#include <iostream>
#include <vector>
#include "HashTable.h"

template <typename Key, typename Value>
struct XFastLeaf {
    Key key;
    Value value;

    XFastLeaf(Key k, Value v) : key(k), value(v) {}
};

template <typename Key, typename Value>
struct XFastNode {
    XFastNode* left;
    XFastNode* right;
    XFastLeaf<Key, Value>* leaf;

    XFastNode() : left(nullptr), right(nullptr), leaf(nullptr) {}
};


class XFastTrieBeta {

};


#endif //PROJECT_ESPRIT_MODEL_C_XFASTTRIEBETA_H
