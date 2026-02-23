#include "global.hpp"
#include "./controls/ControlGroup.hpp"
#include "Algorithms/insertionSort.hpp"

//controls
//board
//array


int main()
{
    Resources::initialize();
    MAINCONTROLS::createControls();

    BarBoard barboard(
        MAINCONTROLS::barControls.sliders["Count"].controlable,
        MAINCONTROLS::barControls.sliders["Max Height"].controlable,
        MAINCONTROLS::barControls.sliders["Width"].controlable,
        MAINCONTROLS::barControls.sliders["Spacing"].controlable,
        GlobalVars::bars
    );



    GlobalVars::sortingAlgorithm = &GlobalVars::insersion;


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
