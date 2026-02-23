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

protected:
    SmartArray<BarShape>* array;

    void virtual start()
    {
    }

private:
};

#endif // ALGORITHM
