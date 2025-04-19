#ifndef CONTROLGROUP_HPP
#define CONTROLGROUP_HPP

#include "../global.hpp"
#include "./Slider.hpp"
#include "../Bar/BarShape.h"
enum BarControls
{
    COUNT,
    HEIGHT,
    WIDTH,
    SPACING,
};

class ControlGroup : public sf::Drawable,
                     public sf::Transformable
{

public:
    std::map<std::string, Slider> sliders;

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

    void mouseReleased()
    {
        for (auto &[placeHolder, slider] : sliders)
            slider.mouseReleased();
    }

    void mouseClicked()
    {
        for (auto &[placeHolder, slider] : sliders)
            slider.clickWithin();
    }

    void somethingHappened(sf::Event &event)
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
        for (auto &[placeHolder, slider] : sliders)
        {
            slider.setPosition(x, y);
            y += slider.getSize().y + 40 + 60;
        }
    }

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        for (auto &[placeHolder, slider] : sliders)
            rt.draw(slider, states);
    }
};

#endif // CONTROLGROUP_HPP