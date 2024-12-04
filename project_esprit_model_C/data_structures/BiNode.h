#ifndef PROJECT_ESPRIT_MODEL_C_BINODE_H
#define PROJECT_ESPRIT_MODEL_C_BINODE_H

template <typename T>  // Add template parameter
class BiNode {
public:
    T data;
    BiNode* next;
    BiNode* prev;

    explicit BiNode(T value) : data(value), next(nullptr), prev(nullptr) {}
};

#endif //PROJECT_ESPRIT_MODEL_C_BINODE_H

