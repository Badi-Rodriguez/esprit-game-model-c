//
// Created by Badi on 11/13/2024.
//

#ifndef PROJECT_ESPRIT_MODEL_C_PRIORITYQUEUE_H
#define PROJECT_ESPRIT_MODEL_C_PRIORITYQUEUE_H


#include <iostream>
#include <vector>

using namespace std;

struct Cell {
    int row, col, cost;
    bool operator<(const Cell& other) const { return cost < other.cost; }
};

class PriorityQueue {
private:
    vector<Cell> heap;

    void heapifyUp(int index) {
        if (index == 0) return;
        int parent = (index - 1) / 2;
        if (heap[index].cost < heap[parent].cost) {
            swap(heap[index], heap[parent]);
            heapifyUp(parent);
        }
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index;

        if (leftChild < heap.size() && heap[leftChild].cost < heap[smallest].cost) {
            smallest = leftChild;
        }
        if (rightChild < heap.size() && heap[rightChild].cost < heap[smallest].cost) {
            smallest = rightChild;
        }
        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    void push(const Cell& cell) {
        heap.push_back(cell);
        heapifyUp(heap.size() - 1);
    }

    void pop() {
        if (heap.empty()) return;
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
    }

    Cell top() const {
        if (heap.empty()) throw out_of_range("PriorityQueue is empty");
        return heap[0];
    }

    bool empty() const {
        return heap.empty();
    }

};


#endif //PROJECT_ESPRIT_MODEL_C_PRIORITYQUEUE_H
