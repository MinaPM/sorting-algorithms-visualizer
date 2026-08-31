//
// Created by Mina on 2/23/26.
//

#ifndef SORTING_ALGORITHMS_QUICKSORT_H
#define SORTING_ALGORITHMS_QUICKSORT_H
#include "SortAlgorithm.hpp"

class QuickSort : public Algorithm
{
    void (QuickSort::*nextStep)() = nullptr;

    void start() override { reset(); }

    void reset() override
    {

        top = 0;
        left = 0;
        right = array->length() - 1;

        stack.resize(array->length());

        stack[top++] = left;

        stack[top++] = right;

        nextStep = &QuickSort::mainLoop;

        if (array)
            array->memoryStats.resetStats();
    }

    bool step() override
    {
        if (nextStep)
        {
            (this->*nextStep)();
            return true;
        }
        else
        {
            return false;
        }
    }

    size_t top, left, right, pivot, partitionIndex, partitionValue, partitionCounter;
    std::remove_pointer_t<decltype(array)> stack;

    void mainLoop()
    {
        if (top > 0)
        {
            right = stack[--top];
            left = stack[--top];

            size_t mid = left + (right - left) / 2;
            array->swap(mid, right);

            partitionValue = (*array)[right];
            partitionIndex = (left - 1);

            partitionCounter = left;
            nextStep = &QuickSort::partition;
        }
        else
        {
            nextStep = nullptr;
        }
    }

    void partition()
    {

        if (partitionCounter <= right - 1)
        {
            if ((*array)[partitionCounter] <= partitionValue)
            {
                partitionIndex++;
                array->swap(partitionIndex, partitionCounter);
            }
            partitionCounter++;
        }
        else
        {

            array->swap(partitionIndex + 1, right);

            pivot = partitionIndex + 1;

            if (pivot > left + 1)
            {
                stack[top++] = left;
                stack[top++] = pivot - 1;
            }

            if (pivot + 1 < right)
            {
                stack[top++] = pivot + 1;
                stack[top++] = right;
            }

            nextStep = &QuickSort::mainLoop;
        }
    }

public:
    QuickSort(SmartArray<BarShape> &array) : Algorithm(array)
    {
    }
};

#endif // SORTING_ALGORITHMS_QUICKSORT_H
