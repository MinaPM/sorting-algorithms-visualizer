//
// Created by Mina on 2/23/26.
//

#ifndef SORTING_ALGORITHMS_MERGESORT_H
#define SORTING_ALGORITHMS_MERGESORT_H
#include "SortAlgorithm.hpp"

class MergeSort : public Algorithm
{
    void (MergeSort::*nextStep)() = nullptr;

    void start() override { reset(); }

    std::remove_pointer_t<decltype(array)> arr1, arr2;
    size_t currSize, left, i, j, k, n1, n2, mid, right;

    void reset() override
    {
        currSize = 1;
        left = 0;
        nextStep = &MergeSort::mainLoop;
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
        if (currSize <= array->length() - 1)
        {
            left = 0;
            nextStep = &MergeSort::innerLoop;
            innerLoop();
            return;
        }
        nextStep = nullptr;
    }

    void innerLoop()
    {
        if (left < array->length() - 1)
        {

            mid = std::min(left + currSize - 1, array->length() - 1);
            right = std::min(left + 2 * currSize - 1, array->length() - 1);

            n1 = mid - left + 1;
            n2 = right - mid;

            copyToTempArrays(left, mid);

            i = 0;
            j = 0;
            k = left;

            nextStep = &MergeSort::mergeBoth;
            return;
        }

        nextStep = &MergeSort::mainLoop;
        currSize = 2 * currSize;
    }

    void mergeBoth()
    {
        if (i < n1 && j < n2)
        {
            if (arr1[i] <= arr2[j])
            {
                (*array)[k] = arr1[i];
                i++;
            }
            else
            {
                (*array)[k] = arr2[j];
                j++;
            }
            k++;
            return;
        }
        nextStep = &MergeSort::mergeLeftOverArr1;
    }

    void mergeLeftOverArr1()
    {
        if (i < n1)
        {
            (*array)[k] = arr1[i];
            i++;
            k++;
            return;
        }

        nextStep = &MergeSort::mergeLeftOverArr2;
    }

    void mergeLeftOverArr2()
    {
        if (j < n2)
        {
            (*array)[k] = arr2[j];
            j++;
            k++;
            return;
        }
        nextStep = &MergeSort::innerLoop;
        left += 2 * currSize;
    }

    void copyToTempArrays(size_t left1, size_t mid1)
    {
        arr1.erase();
        arr2.erase();
        arr1.resize(n1);
        arr2.resize(n2);

        for (size_t i1 = 0; i1 < n1; i1++)
            arr1[i1] = (*array)[left1 + i1];
        for (size_t j1 = 0; j1 < n2; j1++)
            arr2[j1] = (*array)[mid1 + 1 + j1];
    }

public:
    MergeSort(SmartArray<BarShape> &array) : Algorithm(array)
    {
    }
};

#endif // SORTING_ALGORITHMS_MERGESORT_H
