#include "Control.hpp"

class CheckBox : public Control<bool>
{
protected:
    void setLayout() override
    {
        label.setPosition({
            rectangle.getPosition().x + rectangle.getSize().x + 5,
            rectangle.getPosition().y 
            - rectangle.getSize().y / 2
        });
    }

public:
    CheckBox(const std::string& text, bool status = false) : Control(text)
    {
        controlable = status;
        rectangle.setSize(15, 15);
        rectangle.setOutlineThickness(2);
        setColor(Colors::TRANSPARENT, Colors::TEXT, Colors::TEXT);

        rectangle.setFillColor(Colors::TRANSPARENT);
        setLayout();
    }

    void setPosition(SDL_Point position)  override
    {
        rectangle.setPosition(position);
        setLayout();
    }


    void enable()
    {
        enabled = true;
        setColor(Colors::TRANSPARENT, Colors::TEXT, Colors::TEXT);

    }

    void disable()
    {
        enabled = false;
        setColor(Colors::TRANSPARENT, Colors::TEXT, Colors::TEXT);
    }


    const bool& bindStatus() { return controlable; }

    void toggle()
    {
        controlable = !controlable;
        if (controlable)
            rectangle.setFillColor(Colors::MAIN);
        else
            rectangle.setFillColor(Colors::TRANSPARENT);
    }

    void check()
    {
        controlable = true;
        rectangle.setFillColor(Colors::MAIN);
    }

    void uncheck()
    {
        controlable = false;
        rectangle.setFillColor(Colors::TRANSPARENT);
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
