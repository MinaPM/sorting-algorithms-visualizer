#ifndef BAR_SHAPE
#define BAR_SHAPE

#include "../global.hpp"
#include "../smartArray.hpp"
namespace BarVars
{
    const sf::Color barFillColor = sf::Color::White;
    const sf::Color barFillColorKey = sf::Color::Yellow;
    const sf::Color barFillColorCompare = sf::Color::Red;
    const int defaultWidth = 20;
    const int defaultHeight = 100;
}

class BarShape : public sf::Drawable, public sf::Transformable
{
    sf::RectangleShape rectangle;
    int width, height;

public:
    BarShape() : BarShape(BarVars::defaultWidth, BarVars::defaultHeight) {}

    BarShape(const int &width, const int &height)
    {
        // rectangle.setOutlineThickness(1);
        setSize(width, height);
        rectangle.setFillColor(BarVars::barFillColor);
        rectangle.setOutlineColor(sf::Color::Red);
    }

    void updateValue(const int &value) { setSize(width, value); }
    void updateValue(const BarShape &value) { setSize(width, value.height); }

    int getValue() { return height; }

    void swap(BarShape &other)
    {
        int height1 = other.height;
        other.updateValue(height);
        updateValue(height1);
        // other.setColor(BarVars::barFillColor);
        // this->setColor(BarVars::barFillColor);
    }

    bool operator<(const BarShape &other) const
    {
        return this->height < other.height;
    }

    bool operator>(const BarShape &other) const
    {
        return this->height > other.height;
    }

    BarShape& operator=(const BarShape &other){
        this->updateValue(other);
        return *this;
    } 
    BarShape& operator=(int value){
        this->updateValue(value);
        return *this;
    } 

public: // graphics
    void setColor(sf::Color color) { rectangle.setFillColor(color); }
    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        rt.draw(rectangle, states);
    }

public: // size and position
    void setPosition(float x) { rectangle.setPosition(x, rectangle.getPosition().y); }
    void setPosition(float x, float y) { rectangle.setPosition(x, y); }

    void setSize(float width, float height) { setSize(sf::Vector2f(width, height)); }
    void setSize(sf::Vector2f size)
    {
        this->width = size.x;
        this->height = size.y;
        rectangle.setSize(size);
        rectangle.setOrigin(width / 2, height);
    }

    sf::Vector2f getSize() { return rectangle.getSize(); }
};

#endif // BAR_SHAPE