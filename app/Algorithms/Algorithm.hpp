#ifndef ALGORITHM
#define ALGORITHM
#include "../smartArray.hpp"
#include "../Bar/BarShape.h"
#include <chrono>
#include <iostream>

class Algorithm
{
private:
public:
    Algorithm() : array(nullptr), size(0),
                  comparisonCount(0), swapCount(0),
                  exceutionTime(0), lastIndex(0)
    {
    };

    Algorithm(int* array, int size) : Algorithm()
    {
        this->array = array;
        this->size = size;
        lastIndex = size - 1;
    }

    void sort()
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        if (array)
            start();
        auto endTime = std::chrono::high_resolution_clock::now();
        exceutionTime = (std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime)).count();
    }

    void sort(int* array, int size)
    {
        Algorithm(array, size);
        sort();
    }


    int getExcutionTime() { return exceutionTime; }

protected:
    SmartArray<BarShape>& array;
    int size, lastIndex, comparisonCount, swapCount, exceutionTime;

    void virtual start()
    {
    }
};

#endif // ALGORITHM
