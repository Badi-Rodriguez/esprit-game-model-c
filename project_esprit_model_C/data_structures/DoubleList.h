#ifndef PROJECT_ESPRIT_MODEL_C_DOUBLELIST_H
#define PROJECT_ESPRIT_MODEL_C_DOUBLELIST_H

#include <iostream>
#include <vector>
#include "BiNode.h"

template <typename T>
class DoubleList {
private:
    BiNode<T>* head;
    BiNode<T>* tail;

public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    ~DoubleList();

    // Basic operations
    void push_front(const T& value);
    void push_back(const T& value);
    void pop_front();
    void pop_back();
    void remove(const T& value);
    bool empty() const { return head == nullptr; }

    // Helper functions
    BiNode<T>* find(const T& value) const;
    std::vector<T> to_vector() const;

    // Iterator support
    class Iterator {
    private:
        BiNode<T>* current;

    public:
        Iterator(BiNode<T>* start) : current(start) {}
        T& operator*() { return current->data; }
        Iterator& operator++() {
            current = current->next;
            return *this;
        }
        bool operator!=(const Iterator& other) const { return current != other.current; }
        bool operator==(const Iterator& other) const { return current == other.current; }
    };

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }

};

// Destructor
template <typename T>
DoubleList<T>::~DoubleList() {
    while (head) {
        pop_front();
    }
}

// Push to the front
template <typename T>
void DoubleList<T>::push_front(const T& value) {
    BiNode<T>* newNode = new BiNode<T>(value);
    newNode->next = head;
    if (head) {
        head->prev = newNode;
    } else {
        tail = newNode;  // If the list was empty
    }
    head = newNode;
}

// Push to the back
template <typename T>
void DoubleList<T>::push_back(const T& value) {
    BiNode<T>* newNode = new BiNode<T>(value);
    newNode->prev = tail;
    if (tail) {
        tail->next = newNode;
    } else {
        head = newNode;  // If the list was empty
    }
    tail = newNode;
}

// Pop from the front
template <typename T>
void DoubleList<T>::pop_front() {
    if (!head) return;
    BiNode<T>* temp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;  // If the list becomes empty
    }
    delete temp;
}

// Pop from the back
template <typename T>
void DoubleList<T>::pop_back() {
    if (!tail) return;
    BiNode<T>* temp = tail;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    } else {
        head = nullptr;  // If the list becomes empty
    }
    delete temp;
}

// Remove a specific value
template <typename T>
void DoubleList<T>::remove(const T& value) {
    BiNode<T>* nodeToRemove = find(value);
    if (!nodeToRemove) return;

    if (nodeToRemove->prev) {
        nodeToRemove->prev->next = nodeToRemove->next;
    } else {
        head = nodeToRemove->next;  // Node is the head
    }

    if (nodeToRemove->next) {
        nodeToRemove->next->prev = nodeToRemove->prev;
    } else {
        tail = nodeToRemove->prev;  // Node is the tail
    }

    delete nodeToRemove;
}

// Find a value
template <typename T>
BiNode<T>* DoubleList<T>::find(const T& value) const {
    BiNode<T>* current = head;
    while (current) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// Convert to vector
template <typename T>
std::vector<T> DoubleList<T>::to_vector() const {
    std::vector<T> result;
    BiNode<T>* current = head;
    while (current) {
        result.push_back(current->data);
        current = current->next;
    }
    return result;
}

#endif // PROJECT_ESPRIT_MODEL_C_DOUBLELIST_H






