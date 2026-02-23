#ifndef ALGORITHM
#define ALGORITHM
#include "../smartArray.hpp"
#include "../Bar/BarShape.h"


class Algorithm
{
private:
public:
    Algorithm() : array(nullptr)
    {
    }

    Algorithm(SmartArray<BarShape>& array) : array(&array)
    {
    }


    void setArray(SmartArray<BarShape>& array)
    {
        this->array = &array;
    }

    void sort()
    {
        if (array)
            start();
    }

    void sort(SmartArray<BarShape>& array)
    {
        setArray(array);
        sort();
    }


    static void setDelay(int& delay) { sortingDelay = &delay; }

    static int* sortingDelay;

protected:
    SmartArray<BarShape>* array;


    void virtual start()
    {
    }

    static const int minDelay = 200;
    static const int maxDelay = 100'000;
    static const int range = maxDelay - minDelay;

    static void sleep()
    {
        auto stamp =
            std::chrono::high_resolution_clock::now() +
            std::chrono::microseconds(maxDelay - range * (*sortingDelay / 99));
        std::this_thread::sleep_until(stamp);
    }
};

int *Algorithm::sortingDelay= nullptr;

#endif // ALGORITHM
