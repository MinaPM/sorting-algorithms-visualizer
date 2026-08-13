#ifndef CONTROLGROUP_HPP
#define CONTROLGROUP_HPP

// #include "../src/global.hpp"
#include "Slider.hpp"
#include "Button.hpp"
#include "CheckGroup.hpp"
// #include "../graphics/bar/BarBoard.hpp"

class ControlGroup
{
private:
    void setPosition()
    {
        setPosition((*sliders.begin()).second.getPosition());
    }

public:
    std::map<std::string, Slider> sliders;
    std::map<std::string, CheckGroup> checkGroups;
    std::map<std::string, Button *> buttons;

    void update()
    {
        for (auto &[placeHolder, slider] : sliders)
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
        Button *button = new Button(name);
        buttons.emplace(name, button);
        setPosition();
    }

    void mouseReleased()
    {
        for (auto &[placeHolder, slider] : sliders)
            slider.mouseReleased();
        for (auto &[placeHolder, checkGroup] : checkGroups)
            checkGroup.mouseReleased();
        for (auto &[placeHolder, button] : buttons)
            button->mouseReleased();
    }

    void mouseClicked()
    {
        for (auto &[placeHolder, slider] : sliders)
            slider.clickWithin();

        for (auto &[placeHolder, checkGroup] : checkGroups)
            checkGroup.clickWithin();

        for (auto &[placeHolder, button] : buttons)
            if (button->clickWithin())
                button->click();
    }

    void setPosition(SDL_Point position)
    {
        SDL_Point gap = {0, 50};
        for (auto &[placeHolder, slider] : sliders)
        {
            slider.setPosition(position.x, position.y);
            position.y += slider.getSize().h + gap.y;
        }

        for (auto &[placeHolder, checkGroup] : checkGroups)
        {
            checkGroup.setPosition(position);
            position.y += checkGroup.getSize().h + gap.y;

            // y += checkGroup.getSize().y + gap;
        }

        for (auto &[placeHolder, button] : buttons)
        {
            button->setPosition(position.x, position.y);
            position.y += button->getSize().h + gap.y;
        }
    }

    void draw(SDL_Renderer *renderer)
    {
        for (auto &[placeHolder, slider] : sliders)
            slider.draw(renderer);

        for (auto &[placeHolder, checkGroup] : checkGroups)
            checkGroup.draw(renderer);

        for (auto &[placeHolder, button] : buttons)
            button->draw(renderer);
    }
};


#endif // CONTROLGROUP_HPP
