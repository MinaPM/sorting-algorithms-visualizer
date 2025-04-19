#include "../../global.hpp"




enum BarControls
{
    COUNT,
    WIDTH,
    HEIGHT,
    SPACING,
};

class ControlGroup : public sf::Drawable,
                     public sf::Transformable
{

public:
    Slider sliders[4];
    ControlGroup()
        : sliders{
              Slider("Count", 20, 30, 1, 100),
              Slider("Width", 20, 5, 10, 2000),
              Slider("Height", 20, 1, 10, 2000),
              Slider("Spacing", 20, 1, 0, 2000)
          }
    {
        int x = 20, y = 100;

        for (auto &slider : sliders)
        {
            slider.setPosition(x, y);
            y += slider.getSize().y + 40 + 60;
        }
    }

    // void setFunctions(PuzzleFunctions pFunction, bool enable)
    // {
    // }

    void update(sf::Vector2i point)
    {
        for (auto &slider : sliders)
            slider.setValue(point);
    }

    void mouseReleased()
    {
        for (auto &slider : sliders)
            slider.mouseReleased();
    }

    void mouseClicked(sf::Vector2i point)
    {
        for (auto &slider : sliders)
            slider.clickWithin(point);
    }

    void somethingHappened(sf::Event &event,sf::Vector2i point )
    {
        switch (event.type)
        {
        case sf::Event::MouseButtonPressed:
            mouseClicked(point);
        case sf::Event::MouseMoved:
            update(point);
            break;

        case sf::Event::MouseButtonReleased:
            mouseReleased();
            break;
        }
    }

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override
    {
        states.transform *= getTransform();

        for (auto &slider : sliders)
            rt.draw(slider, states);

        // rt.draw(sound_check, states);
    }
};
