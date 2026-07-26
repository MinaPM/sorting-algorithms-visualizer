//
// Created by Mina on 2/23/26.
//

#ifndef SORTING_ALGORITHMS_HEAPSORT_H
#define SORTING_ALGORITHMS_HEAPSORT_H
#include "algorithm.hpp"

class HeapSort : public Algorithm {
public:
    HeapSort(SmartArray<BarShape> &array) : Algorithm(array) {
    }

    void start() override { heapSort(); }

private:
    int lastIndex;
    static int parentOf(const int key) { return (key - 1) / 2; };
    static int leftChild(const int key) { return 2 * key + 1; }
    static int rightChild(const int key) { return leftChild(key) + 1; }

    void heapSort() {
        lastIndex = array->length() - 1;
        buildMaxHeap();
        while (lastIndex >= 0)
            deleteTop();
    }

    void buildMaxHeap() {
        for (int i = (lastIndex) / 2; i >= 0; i--) {
            iterPushUp(i);
            sleep();
        }
    }


    void iterPushUp(int root) {
        int child = leftChild(root), parent = root;
        while (child <= lastIndex) {
            if (child != lastIndex && (*array)[child] < (*array)[rightChild(parent)])
                child = rightChild(parent);

            if ((*array)[parent] < (*array)[child]) {
                array->swap(parent, child);
                parent = child;
                child = leftChild(parent);
            } else
                break;
            sleep();
        }
    }

    void deleteTop() {
        array->swap(lastIndex--, 0);
        iterPushUp(0);
        sleep();
    }
};


#endif //SORTING_ALGORITHMS_HEAPSORT_H
