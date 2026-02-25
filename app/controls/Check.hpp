#include "Control.hpp"

class CheckBox : public Control<bool>
{
protected:

    void setLayout() override
    {
        check_circle.setPosition(rectangle.getPosition());
        label.setPosition({
            rectangle.getPosition().x + rectangle.getGlobalBounds().size.x + 5,
            rectangle.getPosition().y - label.getGlobalBounds().size.y / 2
        });
    }

public:
    sf::CircleShape check_circle;

    CheckBox(const std::string& text, bool status = false) : Control(text)
    {
        controlable = status;
        rectangle.setSize(sf::Vector2f(15, 15));
        check_circle.setRadius(rectangle.getSize().x / 2);
        check_circle.setFillColor(sf::Color::Red);
        setPosition(0, 0);
    }

    void setPosition(sf::Vector2f position) override
    {
        rectangle.setPosition(position);
        setLayout();
    }

    void setPosition(float x, float y)
    {
        setPosition({x, y});
    }

    void enable()
    {
        enabled = true;
        setColor(sf::Color::Blue, sf::Color::White, sf::Color::Blue);
    }

    void disable()
    {
        enabled = false;
        setColor(sf::Color(50, 50, 50), sf::Color::White, sf::Color(50, 50, 50));
    }

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const override
    {
        Control::draw(rt, states);
        states.transform *= getTransform();
        if (controlable)
            rt.draw(check_circle, states);
    }

    void setColor(sf::Color fill, sf::Color outline, sf::Color text)
    {
        Control::setColor(fill, outline, text);
        check_circle.setFillColor(outline);
    }

    const bool& bindStatus() { return controlable; }

    void toggle() { controlable = !controlable; }

    void check() { controlable = true; }

    void uncheck() { controlable = false; }

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
