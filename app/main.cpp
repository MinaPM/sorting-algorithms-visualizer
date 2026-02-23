#include "global.hpp"
#include "./controls/ControlGroup.hpp"
#include "Algorithms/insertionSort.hpp"

//controls
//board
//array


int* sortingDelay;
const int minDelay = 200;
const int maxDelay = 100'000;
const int range = maxDelay - minDelay;

void sleep()
{
    auto stamp =
        std::chrono::high_resolution_clock::now() +
        std::chrono::microseconds(maxDelay - range * (*sortingDelay / 99));
    std::this_thread::sleep_until(stamp);
}


void sort()
{
    GlobalVars::bars.memoryStats.resetStats();

    for (size_t i = 1; i < GlobalVars::bars.length(); i++)
    {
        size_t j = i;
        while (j > 0 && GlobalVars::bars.read(j) < GlobalVars::bars.read(j - 1))
        {
            GlobalVars::bars.swap(j, j - 1);
            j--;
            sleep();
        }
    }
    Resources::appendDebugText("");
    Resources::appendDebugText(GlobalVars::bars.memoryStats.to_string());

    GlobalVars::bars.memoryStats.resetStats();
}

Insertion insertion;
void sort2()
{
    insertion.setArray(GlobalVars::bars);
    insertion.sort();

}


int main()
{
    Resources::initialize();
    MAINCONTROLS::createControls();

    BarBoard barboard(
        MAINCONTROLS::barControls.sliders["Count"].controlable,
        MAINCONTROLS::barControls.sliders["Max Height"].controlable,
        MAINCONTROLS::barControls.sliders["Width"].controlable,
        MAINCONTROLS::barControls.sliders["Spacing"].controlable,
        MAINCONTROLS::barControls.sliders["Speed"].controlable,
        GlobalVars::bars
    );

    sortingDelay = &(MAINCONTROLS::barControls.sliders["Speed"].controlable);

    (MAINCONTROLS::barControls.buttons["Sort"])->setOnTrigger(
        [&]() { sort2(); });


    MAINCONTROLS::bindControls(barboard);
    GlobalVars::bars.shuffle();


    while (Resources::window.isOpen())
    {
        Resources::window.handleEvents(
            Resources::onClose,
            MAINCONTROLS::onMouseButtonPressed,
            MAINCONTROLS::onMouseButtonReleased,
            MAINCONTROLS::onMouseMoved);

        Resources::window.clear();
        Resources::window.draw(barboard);
        Resources::window.draw(MAINCONTROLS::barControls);
        Resources::window.draw(Resources::debugText);
        Resources::window.display();
    }


    return 0;
}
