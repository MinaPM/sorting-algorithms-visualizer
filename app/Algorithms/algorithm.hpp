#ifndef ALGORITHM
#define ALGORITHM
#include "../smartArray.hpp"
#include "../Bar/BarShape.h"


class Algorithm {
private:
public:
    Algorithm() : array(nullptr) {
    }

    Algorithm(SmartArray<BarShape> &array) : array(&array) {
    }


    void setArray(SmartArray<BarShape> &array) {
        this->array = &array;
    }

    void sort() {
        if (array)
            start();
    }

    void sort(SmartArray<BarShape> &array) {
        setArray(array);
        sort();
    }


    static void setDelay(int &delay) { sortingDelay = &delay; }

    static int *sortingDelay;

protected:
    SmartArray<BarShape> *array;


    void virtual start() {
    }

    static const std::chrono::microseconds duration[4];

    static void sleep() {
        std::this_thread::sleep_for(duration[*sortingDelay - 1]);
    }
};

int *Algorithm::sortingDelay = nullptr;

const std::chrono::microseconds Algorithm::duration[] = {
    std::chrono::microseconds(100'000),
    std::chrono::microseconds(10'000),
    std::chrono::microseconds(1000),
    std::chrono::microseconds(100)
};;


#endif // ALGORITHM
