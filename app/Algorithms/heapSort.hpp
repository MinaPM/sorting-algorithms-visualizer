//
// Created by Mina on 2/23/26.
//

#ifndef SORTING_ALGORITHMS_HEAPSORT_H
#define SORTING_ALGORITHMS_HEAPSORT_H
#include "algorithm.hpp"

class HeapSort : public Algorithm
{
public:
    HeapSort(SmartArray<BarShape>& array) : Algorithm(array)
    {
    }

    void start() override { heapSort(); }


private:
    int parentOf(int key) { return (key - 1) / 2; };
    int leftChild(int key) { return 2 * key + 1; }
    int rightChild(int key) { return leftChild(key) + 1; }

    void heapSort()
    {
        buildMaxHeap();
        // buildMaxHeapRecur(0);
        while (lastIndex >= 0)
            deleteTop();
    }

    void buildMaxHeap()
    {
        for (int i = (lastIndex) / 2; i >= 0; i--)
        {
            pushUp(i);
        }
    }

    void buildMaxHeapRecur(int root)
    {
        if (leftChild(root) > lastIndex)
            return;
        buildMaxHeapRecur(leftChild(root));
        buildMaxHeapRecur(rightChild(root));
        pushUp(root);
    }

    void pushUp(int root)
    {
        int child = leftChild(root);

        if (child > lastIndex)
            return;

        if (child != lastIndex && Compare(array[child], LT, array[rightChild(root)]))
            child = rightChild(root);

        if (Compare(array[root], LT, array[child]))
        {
            Swap(array[root], array[child]);
            pushUp(child);
        }
    }

    void iterPushUp(int root)
    {
        int child = leftChild(root), parent = root;

        while (child <= lastIndex)
        {
            if (child != lastIndex && Compare(array[child], LT, array[rightChild(parent)]))
                child = rightChild(parent);

            if (Compare(array[parent], LT, array[child]))
            {
                Swap(array[parent], array[child]);
                parent = child;
                child = leftChild(parent);
            }
            else
                break;
        }
    }

    void deleteTop()
    {
        Swap(array[lastIndex--], array[0]);
        pushUp(0);
    }

};


#endif //SORTING_ALGORITHMS_HEAPSORT_H