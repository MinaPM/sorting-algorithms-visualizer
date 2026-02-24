//
// Created by Mina on 2/23/26.
//

#ifndef SORTING_ALGORITHMS_QUICKSORT_H
#define SORTING_ALGORITHMS_QUICKSORT_H
#include "algorithm.hpp"


class QuickSort : public Algorithm
{
    void start() override { quickSort(0, array->length() - 1); }

    void quickSort(int left, int right)
    {
        if (left >= right)
            return;

        int pivot = right;
        int i = left - 1, j = left;
        for (; j < pivot;)
        {
            if ((*array)[j] < (*array)[pivot])
            {
                i++;
                array->swap(i, j);
            }
            j++;
            sleep();
        }

        i++;
        array->swap(i, pivot);
        quickSort(left, i - 1);
        quickSort(i + 1, right);
    }

public:
    QuickSort(SmartArray<BarShape>& array) : Algorithm(array)
    {
    }
};


#endif //SORTING_ALGORITHMS_QUICKSORT_H
