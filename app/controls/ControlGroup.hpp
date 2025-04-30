#ifndef CONTROLGROUP_HPP
#define CONTROLGROUP_HPP

#include "../global.hpp"
#include "./Slider.hpp"
#include "./Button.hpp"
#include "../Bar/BarShape.h"

class ControlGroup : public sf::Drawable,
                     public sf::Transformable
{

public:
    std::map<std::string, Slider> sliders;
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
        for (auto &[placeHolder, button] : buttons)
            button->mouseReleased();
    }

    void mouseClicked()
    {
        for (auto &[placeHolder, slider] : sliders)
            slider.clickWithin();
        for (auto &[placeHolder, button] : buttons)
            {if(button->clickWithin())
            button->click();}
    }

    void somethingHappened(const sf::Event &event)
    {
        switch (event.type)
        {
        case sf::Event::MouseButtonPressed:
            mouseClicked();
        case sf::Event::MouseMoved:
            update();
            break;
        case sf::Event::MouseButtonReleased:
            mouseReleased();
            break;
        }
    }

    void setPosition(int x = 20, int y = 100)
    {
        int gap = 50;
        for (auto &[placeHolder, slider] : sliders)
        {
            slider.setPosition(x, y);
            y += slider.getSize().y + gap;
        }

        for (auto &[placeHolder, button] : buttons)
        {
            button->setPosition(x, y);
            y += button->getSize().y + gap;
        }
    }

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        for (auto &[placeHolder, slider] : sliders)
            rt.draw(slider, states);

        for (auto &[placeHolder, button] : buttons)
            rt.draw(*button, states);
    }
};

#endif // CONTROLGROUP_HPP