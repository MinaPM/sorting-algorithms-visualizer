//
// Created by Mina on 2/23/26.
//

#ifndef SORTING_ALGORITHMS_HEAPSORT_H
#define SORTING_ALGORITHMS_HEAPSORT_H
#include "SortAlgorithm.hpp"

class HeapSort : public Algorithm
{
public:
    HeapSort(SmartArray<BarShape> &array) : Algorithm(array)
    {
    }

    void start() override { reset(); }

    void reset() override
    {
        lastIndex = array->length() - 1;
        buildHeapIndex = lastIndex / 2;
        continuepush = false;
        if (array)
            array->memoryStats.resetStats();
    }

private:
    int buildHeapIndex;
    int node, parent, child;
    int lastIndex;

    bool continuepush = false;
    static int parentOf(const int key) { return (key - 1) / 2; };
    static int leftChild(const int key) { return 2 * key + 1; }
    static int rightChild(const int key) { return leftChild(key) + 1; }

    bool step() override
    {

        // continue push loop
        if (continuepush && child <= lastIndex)
        {
            pushuploop();
            return true;
        }

        // build heap step
        if (buildHeapIndex >= 0)
        {
            setNode(buildHeapIndex--);
            pushuploop();
            return true;
        }

        // pop max step
        if (lastIndex >= 0)
        {
            array->swap(lastIndex--, 0);

            setNode(0);
            pushuploop();
            return true;
        }

        return false;
    }

    void setNode(int node)
    {
        this->node = node;
        child = leftChild(node);
        parent = node;
    }

    void pushuploop()
    {
        continuepush = true;

        if (child > lastIndex)
        {
            continuepush = false;
            return;
        }

        if (child != lastIndex && (*array)[child] < (*array)[rightChild(parent)])
            child = rightChild(parent);

        if ((*array)[parent] < (*array)[child])
        {
            array->swap(parent, child);
            parent = child;
            child = leftChild(parent);
        }
        else
            continuepush = false;
    }
};

#endif // SORTING_ALGORITHMS_HEAPSORT_H
