#pragma once
#include "../global.hpp"
#include "../../controls/ControlGroup.hpp"

class Application {
public:
    BarBoard barboard;

    Application() {
        Resources::initialize();
        MainControls::createControls();
        barboard = BarBoard(
            MainControls::barControls.sliders["Count"].controlable,
            MainControls::barControls.sliders["Max Height"].controlable,
            MainControls::barControls.sliders["Width"].controlable,
            MainControls::barControls.sliders["Spacing"].controlable,
            GlobalVars::bars
        );
        MainControls::bindControls(barboard);
    }

    void run() {
        while (Resources::window.isOpen()) {
            Resources::window.handleEvents(
                Resources::onClose,
                MainControls::onMouseButtonPressed,
                MainControls::onMouseButtonReleased,
                MainControls::onMouseMoved);

            Resources::window.clear();
            Resources::window.draw(barboard);
            Resources::window.draw(MainControls::barControls);
            Resources::window.draw(Resources::debugText);
            Resources::window.display();
        }
    }

private:
};
