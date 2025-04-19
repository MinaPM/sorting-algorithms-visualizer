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
        lable.setCharacterSize(20);
        rectangle.setOutlineThickness(3);
        onTrigger = nullptr;
    };
    Control(const sf::Font &font) : Control()
    {
        lable.setFont(font);
    }
    Control(const sf::Font &font, const std::string &string, int characterSize = 20) : Control(font)
    {
        lable.setString(string);
        lable.setCharacterSize(characterSize);
    }

    Control(const std::string &string, int characterSize = 20) : Control(Resources::font)
    {
        lable.setString(string);
        lable.setCharacterSize(characterSize);
    }

    void setFont(const sf::Font &font) { lable.setFont(font); }
    void setString(const std::string &string) { lable.setString(string); }
    void setColor(sf::Color rectangleFill, sf::Color rectangleOutline, sf::Color text)
    {
        rectangle.setFillColor(rectangleFill);
        rectangle.setOutlineColor(rectangleOutline);
        lable.setFillColor(text);
    }

    bool within(sf::Vector2i point) { return rectangle.getGlobalBounds().contains((sf::Vector2f)point); }
    bool clickWithin(sf::Vector2i point) { return clicked = within(point); }
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

    Controlable& bindControlable() { return &controlable; }

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