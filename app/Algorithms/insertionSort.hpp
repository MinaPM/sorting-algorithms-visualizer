//
// Created by Mina on 2/23/26.
//

#ifndef SORTING_ALGORITHMS_INSERTIONSORT_H
#define SORTING_ALGORITHMS_INSERTIONSORT_H
#include "algorithm.hpp"

class Insertion : public Algorithm
{

    void start() override
    {
        array->memoryStats.resetStats();

        for (size_t i = 1; i < array->length(); i++)
        {
            size_t j = i;
            while (j > 0 && array->read(j) < array->read(j - 1))
            {
                array->swap(j, j - 1);
                j--;
                sleep();
            }
        }
        // Resources::appendDebugText("");
        // Resources::appendDebugText(array->memoryStats.to_string());

        array->memoryStats.resetStats();
    }

public:
    Insertion(SmartArray<BarShape>& array) : Algorithm(array)
    {
    }

};


#endif //SORTING_ALGORITHMS_INSERTIONSORT_H
