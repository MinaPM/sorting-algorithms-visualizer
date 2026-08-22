#ifndef ALGORITHM
#define ALGORITHM
#include "../src/smartArray.hpp"
#include "../graphics/bar/BarShape.hpp"

class Algorithm
{
private:
public:
    Algorithm() : array(nullptr)
    {
    }

    Algorithm(SmartArray<BarShape> &array) : array(&array)
    {
    }

    void setArray(SmartArray<BarShape> &array)
    {
        this->array = &array;
    }

    void sort()
    {
        if (array)
            start();
    }

    virtual void reset() {}

    virtual bool step() { return false; }

    void sort(SmartArray<BarShape> &array)
    {
        setArray(array);
        sort();
    }

    static void setDelay(int &delay) { sortingDelay = &delay; }

    static Uint64 getDelayMs()
    {
        if (sortingDelay == nullptr)
            return 0;

        const int index = *sortingDelay - 1;
        if (index < 0 || index >= 7)
            return 0;

        return delays[index];
    }

    static int *sortingDelay;

    static const Uint64 delays[];

protected:
    SmartArray<BarShape> *array;

    void virtual start()
    {
    }

    static void sleep()
    {
        const Uint32 ms = getDelayMs();
        if (ms == 0)
            return;

#ifndef __EMSCRIPTEN__
        SDL_Delay(ms);
#endif
    }
};

int *Algorithm::sortingDelay = nullptr;

const Uint64 Algorithm::delays[] = {200u, 100u, 50u, 20u, 10u, 1u, 0u};

#endif // ALGORITHM
