//
// Created by Badi on 11/13/2024.
//

#include "ForwardList.h"

ForwardList::ForwardList() : head(nullptr) {}

ForwardList::~ForwardList() {
    clear();
}

Node* ForwardList::fetch_head() {
    return head;
}

int ForwardList::search(int target_value) {
    Node* temp = head;

    while (temp != nullptr) {
        if (temp->data == target_value) {
            std::cout << "Found data at location: "<< "[" << &temp << "]" << std::endl;
            return 1;
        }
        else {
            temp = temp->next;
        }
    }

    std::cout << "Data value " << "(" << target_value << ")" << "not found in ForwardList." << std::endl;
    return 0;
}

void ForwardList::print_list() {
    Node* temp = head;
    while (temp != nullptr) {
        std::cout << "Location: " << "[" << temp << "]"
                  << " Value: " << temp->data << std::endl;
        temp = temp->next;
    }
}

void ForwardList::push_front(int value) {
    Node* lock_on = new Node;
    lock_on->data = value;
    lock_on->next = head;
    head = lock_on;
}

void ForwardList::push_back(int value) {
    Node* temp = head;
    Node* lock_on = new Node;
    lock_on->data = value;
    lock_on->next = nullptr;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = lock_on;
}

void ForwardList::pop_front() {
    if (head != nullptr) {
        Node* old_head = head;
        head = head->next;
        delete old_head;
    }
}

void ForwardList::pop_back() {
    if (head == nullptr) return;
    if (head->next == nullptr) {
        delete head;
        head = nullptr;
        return;
    }

    Node* temp = head;
    while (temp->next->next != nullptr) {
        temp = temp->next;
    }
    delete temp->next;
    temp->next = nullptr;
}

void ForwardList::link(ForwardList target_list) {
    Node* temp = head;
    while (temp->next != nullptr)
        temp = temp->next;
    temp->next = target_list.fetch_head();
}

void ForwardList::clear() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
}

