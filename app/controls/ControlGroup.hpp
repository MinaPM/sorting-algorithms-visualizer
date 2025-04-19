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
    Slider sliders[4];
    ControlGroup()
        : sliders{
              Slider("Count", 20, 1, 5, 100),
              Slider("Height", 20, 10, 100, 200),
              Slider("Width", 20, 1, 10, 40),
              Slider("Spacing", 20, 1, 5, 40)}
    {
        int x = 20, y = 100;

        for (auto &slider : sliders)
        {
            slider.setPosition(x, y);
            y += slider.getSize().y + 40 + 60;
        }
    }

    void update()
    {
        sf::Vector2i point = Resources::mousePosition();
        for (auto &slider : sliders)
            slider.setValue(point);
    }

    void mouseReleased()
    {
        for (auto &slider : sliders)
            slider.mouseReleased();
    }

    void mouseClicked()
    {
        sf::Vector2i point = Resources::mousePosition();
        for (auto &slider : sliders)
            slider.clickWithin(point);
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

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        for (auto &slider : sliders)
            rt.draw(slider, states);
    }
};

#endif // CONTROLGROUP_HPP