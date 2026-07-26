#include "Control.hpp"

class CheckBox : public Control<bool>
{
protected:
    void setLayout() override
    {
        label.setPosition({
            rectangle.getPosition().x + rectangle.getGlobalBounds().size.x + 5,
            rectangle.getPosition().y - label.getGlobalBounds().size.y / 2 + rectangle.getSize().y / 2
        });
    }

public:
    CheckBox(const std::string& text, bool status = false) : Control(text)
    {
        controlable = status;
        rectangle.setSize(sf::Vector2f(15, 15));
        rectangle.setOutlineThickness(2);
        rectangle.setFillColor(sf::Color::Transparent);
        setLayout();
    }

    void setPosition(sf::Vector2f position) override
    {
        rectangle.setPosition(position);
        setLayout();
    }


    void enable()
    {
        enabled = true;
        setColor(sf::Color::Blue, sf::Color::White, sf::Color::Blue);
    }

    void disable()
    {
        enabled = false;
        setColor(sf::Color(50, 50, 50), sf::Color(50, 50, 50), sf::Color(50, 50, 50));
    }

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const override
    {
        Control::draw(rt, states);
        states.transform *= getTransform();
    }

    const bool& bindStatus() { return controlable; }

    void toggle()
    {
        controlable = !controlable;
        if (controlable)
            rectangle.setFillColor(sf::Color::Red);
        else
            rectangle.setFillColor(sf::Color::Transparent);
    }

    void check()
    {
        controlable = true;
        rectangle.setFillColor(sf::Color::Red);
    }

    void uncheck()
    {
        controlable = false;
        rectangle.setFillColor(sf::Color::Transparent);
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
