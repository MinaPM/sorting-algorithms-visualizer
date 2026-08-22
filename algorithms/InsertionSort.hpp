//
// Created by Mina on 2/23/26.
//

#ifndef SORTING_ALGORITHMS_INSERTIONSORT_H
#define SORTING_ALGORITHMS_INSERTIONSORT_H
#include "SortAlgorithm.hpp"

class InsertionSort : public Algorithm
{
private:
    size_t i = 1;
    size_t j = 0;
    bool active = false;

public:
    void reset() override
    {
        i = 1;
        j = 0;
        active = true;
        if (array)
            array->memoryStats.resetStats();
    }

    bool step() override
    {
        if (!active || !array)
            return false;

        if (i >= array->length())
        {
            active = false;
            array->memoryStats.resetStats();
            return false;
        }

        if (j == 0)
            j = i;

        if (j > 0 && array->read(j) < array->read(j - 1))
        {
            array->swap(j, j - 1);
            j--;
            sleep();
            return true;
        }

        i++;
        j = 0;
        return true;
    }

    void start() override
    {
        reset();
    }

    InsertionSort(SmartArray<BarShape> &array) : Algorithm(array)
    {
    }
};

#endif // SORTING_ALGORITHMS_INSERTIONSORT_H
