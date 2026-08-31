//
// Created by Mina on 3/12/26.
//

#ifndef SORTING_ALGORITHMS_BUBBLESORT_H
#define SORTING_ALGORITHMS_BUBBLESORT_H
#include "SortAlgorithm.hpp"

class BubbleSort : public Algorithm
{
    void (BubbleSort::*nextStep)() = nullptr;
    size_t outerIndex = 0, innerIndex = 0;
    bool swapped;
    
    void start() override { reset(); }
    void reset() override
    {
        outerIndex = 0;
        innerIndex = 0;
        nextStep = &BubbleSort::mainLoop;

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
        if (outerIndex < (*array).length() - 1)
        {
            swapped = false;
            innerIndex = 0;

            nextStep = &BubbleSort::innerLoop;
            return;
        }
        nextStep = nullptr;
    }

    void innerLoop()
    {
        if (innerIndex < (*array).length() - outerIndex - 1)
        {
            if ((*array)[innerIndex] > (*array)[innerIndex + 1])
            {
                array->swap(innerIndex, innerIndex + 1);
                swapped = true;
            }
            innerIndex++;
        }
        else
        {
            outerIndex++;
            if (!swapped)
                nextStep = nullptr;
            else
                nextStep = &BubbleSort::mainLoop;
        }
    }

public:
    BubbleSort(SmartArray<BarShape> &array) : Algorithm(array)
    {
    }

private:
};

#endif // SORTING_ALGORITHMS_BUBBLESORT_H