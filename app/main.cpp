#include "global.hpp"
#include "./controls/ControlGroup.hpp"
#include "./Bar/BarShape.h"
#include "./Bar/BarBoard.h"




int *sortingDelay;
void sleep()
{
    const int minDelay = 200;
    const int maxDelay = 100'000;
    const int range = maxDelay - minDelay;
    auto stamp = std::chrono::high_resolution_clock::now() +
        std::chrono::microseconds(maxDelay - range * (*sortingDelay / 99));
    std::this_thread::sleep_until(stamp);
}



SmartArray<BarShape> *barsp;
void sort()
{
    barsp->memoryStats.resetStats();

    for (size_t i = 1; i < barsp->length(); i++)
    {
        size_t j = i;
        while (j > 0 && barsp->read(j) < barsp->read(j - 1))
        {
            barsp->swap(j, j - 1);
            j--;
            // sleep();

        }
    }
    Resources::appendDebugText("");
    Resources::appendDebugText(barsp->memoryStats.to_string());

    barsp->memoryStats.resetStats();
}


int main()
{
    Resources::initialize();


    MAINCONTROLS::createControls();
    SmartArray<BarShape> bars;
    barsp=&bars;

    BarBoard barboard(
        MAINCONTROLS::barControls.sliders["Count"].controlable,
        MAINCONTROLS::barControls.sliders["Max Height"].controlable,
        MAINCONTROLS::barControls.sliders["Width"].controlable,
        MAINCONTROLS::barControls.sliders["Spacing"].controlable,
        MAINCONTROLS::barControls.sliders["Speed"].controlable,
        bars
    );

    sortingDelay=&(MAINCONTROLS::barControls.sliders["Speed"].controlable);

    (MAINCONTROLS::barControls.buttons["Sort"])->setOnTrigger([&]()
    {
        sort();
    });



    MAINCONTROLS::bindControls(barboard);
    barboard.shuffle();

    // events
    const auto onClose = [](const sf::Event::Closed&)
    {
        Resources::window.close();
        // return 0;
    };



    while (Resources::window.isOpen())
    {
        Resources::window.handleEvents(onClose, MAINCONTROLS::onMouseButtonPressed,
            MAINCONTROLS::onMouseButtonReleased, MAINCONTROLS::onMouseMoved);

        Resources::window.clear();
        Resources::window.draw(barboard);
        Resources::window.draw(MAINCONTROLS::barControls);
        Resources::window.draw(Resources::debugText);
        Resources::window.display();
    }


    return 0;
}
