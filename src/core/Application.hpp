#pragma once
#include "../global.hpp"
// #include "../../controls/ControlGroup.hpp"
#include "../../graphics/bar/BarBoard.hpp"
#include "../../controls/Check.hpp"
class Application
{
public:
    BarBoard barboard;
    SmartArray<BarShape> bars;
    Text debugText;
    CheckBox testSlider{"Test", false};

    Application()
    {
        if (Resources::initialize())
        {
            // std::cerr << "Failed to initialize resources." << std::endl;
            Resources::windowRunning = false;
            return;
        }
        // bars.resize(40, BarShape());
        // MainControls::createControls();
        // barboard = BarBoard(
        //     MainControls::barControls.sliders["Count"].controlable,
        //     MainControls::barControls.sliders["Max Height"].controlable,
        //     MainControls::barControls.sliders["Width"].controlable,
        //     MainControls::barControls.sliders["Spacing"].controlable,
        //     GlobalVars::bars);
        int *barCount = new int(400);
        int *height = new int(120);
        int *barWidth = new int(2);
        int *spacing = new int(1);

        barboard = BarBoard(
            barCount,
            height,
            barWidth,
            spacing,
            bars);
        // MainControls::bindControls(barboard);

        testSlider.setPosition({10, 10});
        // testSlider.setString("Test");
    }

    void run()
    {
        while (Resources::windowRunning)
        {
            // Resources::window.handleEvents(
            //     Resources::onClose,
            //     MainControls::onMouseButtonPressed,
            //     MainControls::onMouseButtonReleased,
            //     MainControls::onMouseMoved);

            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    Resources::windowRunning = false;
                }
            }

            SDL_SetRenderDrawColor(Resources::gRenderer, 20, 20, 20, 255);
            SDL_RenderClear(Resources::gRenderer);

            testSlider.draw(Resources::gRenderer);
            barboard.draw();
            SDL_RenderPresent(Resources::gRenderer);

            // Resources::window.clear();
            // Resources::window.draw(barboard);
            // Resources::window.draw(MainControls::barControls);
            // Resources::window.draw(Resources::debugText);
            // Resources::window.display();

#ifndef __EMSCRIPTEN__
            SDL_Delay(16);
#endif
        }
    }

private:
};
