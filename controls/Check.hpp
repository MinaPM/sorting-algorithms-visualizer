#include "Control.hpp"

class CheckBox : public Control<bool>
{
protected:
    void setLayout() override
    {
        label.setPosition({
            rectangle.getPosition().x + rectangle.getSize().x + 5,
            rectangle.getPosition().y - label.getSize().y / 2 + rectangle.getSize().y / 2
        });
    }

public:
    CheckBox(const std::string& text, bool status = false) : Control(text)
    {
        controlable = status;
        rectangle.setSize(15, 15);
        rectangle.setOutlineThickness(2);
        rectangle.setFillColor(SDL_Color{0, 0, 0, 0});
        setLayout();
    }

    void setPosition(SDL_Point position) 
    {
        rectangle.setPosition(position);
        setLayout();
    }


    void enable()
    {
        enabled = true;
        setColor(SDL_Color{0, 0, 255, 255}, SDL_Color{255, 255, 255, 255}, SDL_Color{0, 0, 255, 255});
    }

    void disable()
    {
        enabled = false;
        setColor(SDL_Color{50, 50, 50, 255}, SDL_Color{50, 50, 50, 255}, SDL_Color{50, 50, 50, 255});
    }

    
    // void draw(sf::RenderTarget& rt, sf::RenderStates states) const override
    // {
    //     Control::draw(rt, states);
    //     states.transform *= getTransform();
    // }

    const bool& bindStatus() { return controlable; }

    void toggle()
    {
        controlable = !controlable;
        if (controlable)
            rectangle.setFillColor(SDL_Color{255, 0, 0, 255});
        else
            rectangle.setFillColor(SDL_Color{0, 0, 0, 0});
    }

    void check()
    {
        controlable = true;
        rectangle.setFillColor(SDL_Color{255, 0, 0, 255});
    }

    void uncheck()
    {
        controlable = false;
        rectangle.setFillColor(SDL_Color{0, 0, 0, 0});
    }

    bool clickWithin()
    {
        if (enabled && within())
        {
            toggle();
            return true;
        }
        else
            return false;
    }
};
