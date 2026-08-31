//
// Created by Mina on 2/23/26.
//

#ifndef SORTING_ALGORITHMS_INSERTIONSORT_H
#define SORTING_ALGORITHMS_INSERTIONSORT_H
#include "SortAlgorithm.hpp"

class InsertionSort : public Algorithm
{
private:
    void (InsertionSort::*nextStep)() = nullptr;
    size_t outerIndex, innerIndex;
    bool swapped;
    std::remove_reference_t<decltype((*array)[0])> key;

public:
    void start() override { reset(); }

    void reset() override
    {
        outerIndex = 1;
        innerIndex = 0;
        nextStep = &InsertionSort::mainLoop;

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

    void mainLoop()
    {
        if (outerIndex < ((*array).length()))
        {
            key = (*array)[outerIndex];
            innerIndex = outerIndex - 1;

            nextStep = &InsertionSort::innerLoop;
        }
        else
        {
            nextStep = nullptr;
        }
    }

    void innerLoop()
    {
        if (innerIndex >= 0 && (*array)[innerIndex] > key)
        {
            (*array)[innerIndex + 1] = (*array)[innerIndex];
            innerIndex = innerIndex - 1;
        }
        else
        {
            (*array)[innerIndex + 1] = key;
            ++outerIndex;
            nextStep = &InsertionSort::mainLoop;
        }
    }

    InsertionSort(SmartArray<BarShape> &array) : Algorithm(array)
    {
    }
};

#endif // SORTING_ALGORITHMS_INSERTIONSORT_H
