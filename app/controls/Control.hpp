#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "../global.hpp"
template <typename Controlable>
class Control : public sf::Drawable, public sf::Transformable
{
public:
    sf::RectangleShape rectangle;
    sf::Text lable;
    Controlable controlable;
    std::function<void()> onTrigger;

    bool enabled, clicked;

    Control()
    {
        enabled = true;
        clicked = false;
        rectangle.setOutlineThickness(3);
        onTrigger = nullptr;
        lable.setFont(Resources::font);
        lable.setCharacterSize(Resources::characterSize);
    }

    Control(const std::string &string) : Control()
    {
        lable.setString(string);
    }

    void setFont(const sf::Font &font) { lable.setFont(font); }
    void setString(const std::string &string) { lable.setString(string); }
    void setColor(sf::Color rectangleFill, sf::Color rectangleOutline, sf::Color text)
    {
        rectangle.setFillColor(rectangleFill);
        rectangle.setOutlineColor(rectangleOutline);
        lable.setFillColor(text);
    }

    bool within() { return rectangle.getGlobalBounds().contains((sf::Vector2f)Resources::mousePosition()); }
    bool clickWithin() { return clicked = within(); }
    void mouseReleased() { clicked = false; }

    bool isEnabled() { return enabled; }

    void enable()
    {
        enabled = true;
        sf::Color c1(rectangle.getFillColor()), c2(rectangle.getOutlineColor()), c3(lable.getFillColor());
        c1.a = 255;
        c2.a = 255;
        c3.a = 255;
        setColor(c1, c2, c3);
    }
    void disable()
    {
        enabled = false;
        sf::Color c1(rectangle.getFillColor()), c2(rectangle.getOutlineColor()), c3(lable.getFillColor());
        c1.a = 124;
        c2.a = c1.a;
        c3.a = c1.a;
        setColor(c1, c2, c3);
    }

    const Controlable &bindControlable() { return &controlable; }

    void setOnTrigger(std::function<void()> func) { onTrigger = func; }

    void update()
    {
        if (onTrigger)
            onTrigger();
    }

    void alignLeft() { lable.setPosition(rectangle.getPosition().x, lable.getPosition().y); }

    sf::Vector2f getPosition()
    {
        return rectangle.getPosition();
    }

    sf::Vector2f getSize()
    {
        return rectangle.getSize();
    }

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        rt.draw(rectangle, states);
        rt.draw(lable, states);
    }
};
#endif // CONTROL_HPP