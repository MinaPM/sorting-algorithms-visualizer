#include "./header/Control.hpp"

template <typename Controlable>
Control<Controlable>::Control()
{
    enabled = true;
    clicked = false;
    rectangle.setOutlineThickness(3);
    lable.setCharacterSize(20);
    lable.setFont(Resources::font);
}

template <typename Controlable>
Control<Controlable>::Control(const std::string &string, int characterSize): Control()
{
    lable.setString(string);
    lable.setCharacterSize(characterSize);
}
template <typename Controlable>
void Control<Controlable>::setFont(const sf::Font &font) { lable.setFont(font); }
template <typename Controlable>
void Control<Controlable>::setString(const std::string &string) { lable.setString(string); }
template <typename Controlable>
void Control<Controlable>::setColor(sf::Color rectangleFill, sf::Color rectangleOutline, sf::Color text)
{
    rectangle.setFillColor(rectangleFill);
    rectangle.setOutlineColor(rectangleOutline);
    lable.setFillColor(text);
}
template <typename Controlable>
bool Control<Controlable>::within(sf::Vector2i point) { return rectangle.getGlobalBounds().contains((sf::Vector2f)point); }
template <typename Controlable>
bool Control<Controlable>::clickWithin(sf::Vector2i point) { return clicked = within(point); }
template <typename Controlable>
void Control<Controlable>::mouseReleased() { clicked = false; }
template <typename Controlable>
bool Control<Controlable>::isEnabled() { return enabled; }

template <typename Controlable>
void Control<Controlable>::enable()
{
    enabled = true;
    sf::Color c1(rectangle.getFillColor()), c2(rectangle.getOutlineColor()), c3(lable.getFillColor());
    c1.a = 255;
    c2.a = 255;
    c3.a = 255;
    setColor(c1, c2, c3);
}

template <typename Controlable>
void Control<Controlable>::disable()
{
    enabled = false;
    sf::Color c1(rectangle.getFillColor()), c2(rectangle.getOutlineColor()), c3(lable.getFillColor());
    c1.a = 124;
    c2.a = c1.a;
    c3.a = c1.a;
    setColor(c1, c2, c3);
}

template <typename Controlable>
void Control<Controlable>::alignLeft() { lable.setPosition(rectangle.getPosition().x, lable.getPosition().y); }

template <typename Controlable>
sf::Vector2f Control<Controlable>::getPosition() { return rectangle.getPosition(); }

template <typename Controlable>
sf::Vector2f Control<Controlable>::Control::getSize() { return rectangle.getSize(); }

template <typename Controlable>
void Control<Controlable>::draw(sf::RenderTarget &rt, sf::RenderStates states) const
{
    states.transform *= getTransform();
    rt.draw(rectangle, states);
    rt.draw(lable, states);
}