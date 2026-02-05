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
                   exceutionTime(0), lastIndex(0) {};
    Algorithm(int *array, int size) : Algorithm()
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

    void sort(int *array, int size)
    {
        Algorithm(array, size);
        auto startTime = std::chrono::high_resolution_clock::now();
        if (array)
            start();
        auto endTime = std::chrono::high_resolution_clock::now();
        exceutionTime = (std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime)).count();
    }

    void printResults()
    {
        std::cout << "Excution Time: " << getExcutionTime()
                  << " micro seconds , Comparisons: " << getComparisonCount() << "\n";
    }
    int getComparisonCount() { return comparisonCount; }
    int getSwapCount() { return swapCount; }
    int getExcutionTime() { return exceutionTime; }

protected:
    enum Comparison
    {
        LT,
        GT,
        EQ,
        LTEQ,
        GTEQ
    };
    SmartArray<BarShape>& array;
    int size, lastIndex, comparisonCount, swapCount, exceutionTime;
    bool Compare(int value1, Comparison comparison, int value2)
    {
        comparisonCount++;
        switch (comparison)
        {
        case LT:
            return value1 < value2;
        case GT:
            return value1 > value2;
        case EQ:
            return value1 == value2;
        case LTEQ:
            return value1 <= value2;
        case GTEQ:
            return value1 >= value2;
        }

        // shouldnt reach here anyways
        return NULL;
    }

    void Swap(int &value1, int &value2)
    {
        swapCount++;
        std::swap(value1, value2);
    }
    void virtual start() {}
};

#endif // ALGORITHM