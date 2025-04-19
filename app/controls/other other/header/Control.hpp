#ifndef CONTROL_HPP
#define CONTROL_HPP

#include "../../global.hpp"

template <typename Controlable> class Control : public sf::Drawable, public sf::Transformable
{
public:
    sf::RectangleShape rectangle;
    sf::Text lable;
    Controlable controlable;
    bool enabled, clicked;

    Control();

    Control(const std::string &string, int characterSize = 20);

    void setFont(const sf::Font &font);
    void setString(const std::string &string);
    void setColor(sf::Color rectangleFill, sf::Color rectangleOutline, sf::Color text);

    bool within(sf::Vector2i point);
    bool clickWithin(sf::Vector2i point);
    void mouseReleased();

    bool isEnabled();
    void enable();
    void disable();

    void alignLeft();

    sf::Vector2f getPosition();

    sf::Vector2f getSize();

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override;
};

#include "../Control.tpp"

#endif // CONTROL_HPP