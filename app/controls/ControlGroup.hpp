#ifndef CONTROLGROUP_HPP
#define CONTROLGROUP_HPP

#include "../global.hpp"
#include "Slider.hpp"
#include "Button.hpp"
#include "checkGroup.hpp"
#include "../Bar/BarBoard.h"

class ControlGroup : public sf::Drawable,
                     public sf::Transformable
{
private:
    void setPosition()
    {
        setPosition((*sliders.begin()).second.getPosition());
    }

public:
    std::map<std::string, Slider> sliders;
    std::map<std::string, CheckGroup> checkGroups;
    std::map<std::string, Button*> buttons;


    void update()
    {
        for (auto& [placeHolder, slider] : sliders)
            slider.setValue();
    }

    void addSlider(std::string name, Slider slider)
    {
        sliders.emplace(name, slider);
        setPosition();
    }

    void addCheckGroup(std::string name)
    {
        checkGroups.emplace(name, CheckGroup(name));
        setPosition();
    }

    void addButton(std::string name)
    {
        Button* button = new Button(name);
        buttons.emplace(name, button);
        setPosition();
    }

    void mouseReleased()
    {
        for (auto& [placeHolder, slider] : sliders)
            slider.mouseReleased();
        for (auto& [placeHolder, checkGroup] : checkGroups)
            checkGroup.mouseReleased();
        for (auto& [placeHolder, button] : buttons)
            button->mouseReleased();
    }

    void mouseClicked()
    {
        for (auto& [placeHolder, slider] : sliders)
            slider.clickWithin();

        for (auto& [placeHolder, checkGroup] : checkGroups)
            checkGroup.clickWithin();

        for (auto& [placeHolder, button] : buttons)
            if (button->clickWithin())
                button->click();
    }

    void setPosition(sf::Vector2f position)
    {
        sf::Vector2f padding = {0, 50};
        for (auto& [placeHolder, slider] : sliders)
        {
            slider.setPosition(position.x, position.y);
            // y += slider.getSize().y + gap;
            position.y += slider.getSize().y + padding.y;
        }

        for (auto& [placeHolder, checkGroup] : checkGroups)
        {
            checkGroup.setPosition(position);
            position.y += checkGroup.getSize().y + padding.y;

            // y += checkGroup.getSize().y + gap;
        }

        for (auto& [placeHolder, button] : buttons)
        {
            button->setPosition(position.x, position.y);
            position.y += button->getSize().y + padding.y;
        }
    }

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        for (auto& [placeHolder, slider] : sliders)
            rt.draw(slider, states);

        for (auto& [placeHolder, checkGroup] : checkGroups)
            rt.draw(checkGroup, states);

        for (auto& [placeHolder, button] : buttons)
            rt.draw(*button, states);
    }
};


namespace MAINCONTROLS
{
    ControlGroup barControls;

    void createControls()
    {
        barControls.addSlider("Count", Slider("Count", 1, 600, 1000));
        barControls.addSlider("Max Height",
                              Slider("Max Height", 10, 300, Resources::window_size.y + Resources::padding.bottom * 2));
        barControls.addSlider("Width", Slider("Width", 1, 1, 40));
        barControls.addSlider("Spacing", Slider("Spacing", 1, 1, 40));
        barControls.addSlider("Speed", Slider("Speed", 1, 5, 100));
        barControls.addButton("Shuffle");
        barControls.addButton("Sort");
        barControls.addCheckGroup("Sorting Algorithm");
        barControls.checkGroups["Sorting Algorithm"].addCheckBox(("Merge"));

        barControls.setPosition({20, 100});
    }


    void bindControls(BarBoard& barboard)
    {
        barControls.sliders["Count"].setOnTrigger([&]() { barboard.updateBarCount(); });
        barControls.sliders["Max Height"].setOnTrigger([&]() { barboard.updateBarSize(); });
        barControls.sliders["Width"].setOnTrigger([&]() { barboard.updateBarSize(); });
        barControls.sliders["Spacing"].setOnTrigger([&]() { barboard.updateSpacing(); });
        barControls.buttons["Shuffle"]->setOnTrigger([&]() { GlobalVars::bars.shuffle(); });


        barControls.buttons["Sort"]->setOnTrigger([&]() { GlobalVars::sortingAlgorithm->sort(); });
        Algorithm::setDelay(MAINCONTROLS::barControls.sliders["Speed"].controlable);
    }


    //events
    const auto onMouseButtonPressed = [](sf::Event::MouseButtonPressed)
    {
        barControls.mouseClicked();
    };
    const auto onMouseButtonReleased = [](sf::Event::MouseButtonReleased)
    {
        barControls.mouseReleased();
    };
    const auto onMouseMoved = [](sf::Event::MouseMoved)
    {
        barControls.update();
    };
}

#endif // CONTROLGROUP_HPP
