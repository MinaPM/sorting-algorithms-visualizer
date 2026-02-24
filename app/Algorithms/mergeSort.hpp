//
// Created by Mina on 2/23/26.
//

#ifndef SORTING_ALGORITHMS_MERGESORT_H
#define SORTING_ALGORITHMS_MERGESORT_H
#include "algorithm.hpp"


class MergeSort : public Algorithm
{
    void start() override { mergeSort(0, array->length() - 1); }

    void mergeSort(int left, int right)
    {
        if (left >= right)
            return;

        sleep();

        int mid = (right - left) / 2 + left;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        merge(left, right, mid);
    }

    void merge(int left, int right, int mid)
    {
        int left_size = mid - left + 1, right_size = right - mid;

        int *left_array = new int[left_size], *right_array = new int[right_size];

        for (int i = 0; i < left_size; i++)
        {
            left_array[i] = (*array)[i + left];
        }

        for (int i = 0; i < right_size; i++)
        {
            right_array[i] = (*array)[i + mid + 1];
        }

        int left_index = 0, right_index = 0;

        int current_index = left;
        while (left_index < left_size && right_index < right_size)
        {
            if (left_array[left_index] < right_array[right_index])
            {
                (*array)[current_index] = left_array[left_index];
                left_index++;
            }
            else
            {
                (*array)[current_index] = right_array[right_index];
                right_index++;
            }
            sleep();
            current_index++;
        }

        for (; left_index < left_size; left_index++, current_index++)
        {
            sleep();
            (*array)[current_index] = left_array[left_index];
        }

        for (; right_index < right_size; right_index++, current_index++)
        {
            sleep();
            (*array)[current_index] = right_array[right_index];
        }

        delete[] left_array;
        delete[] right_array;
    }

public:
    MergeSort(SmartArray<BarShape>& array) : Algorithm(array)
    {
    }
};


#endif //SORTING_ALGORITHMS_MERGESORT_H
