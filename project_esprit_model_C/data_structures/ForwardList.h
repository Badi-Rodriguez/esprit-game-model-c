//
// Created by Badi on 11/13/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_FORWARDLIST_H
#define PROJECT_ESPRIT_MODEL_C_FORWARDLIST_H

#include <iostream>
#include "Node.h"

class ForwardList {
private:
    Node* head;
public:
    ForwardList();
    ~ForwardList();
    Node* fetch_head();
    int search(int);
    void print_list();
    void push_front(int);
    void push_back(int);
    void pop_front();
    void pop_back();
    void link(ForwardList);
    void clear();
};

#endif //PROJECT_ESPRIT_MODEL_C_FORWARDLIST_H
