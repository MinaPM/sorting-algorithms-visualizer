#ifndef BAR_SHAPE
#define BAR_SHAPE

#include "../../src/global.hpp"
// #include "../../src/smartArray.hpp"
#include "../Rectangle.hpp"
namespace BarVars
{
    // const sf::Color barFillColor = sf::Color::White;
    // const sf::Color barFillColorKey = sf::Color::Yellow;
    // const sf::Color barFillColorCompare = sf::Color::Red;
    const SDL_Color barFillColor = {255, 255, 255, 255};
    const SDL_Color barFillColorKey = {255, 0, 255, 255};
    const SDL_Color barFillColorCompare = {255, 0, 0, 255};
    const int defaultWidth = 20;
    const int defaultHeight = 100;
}

class BarShape
{
    public:
    Rectangle rectangle{0, 0, BarVars::defaultWidth, BarVars::defaultHeight};

    BarShape() : BarShape(BarVars::defaultWidth, BarVars::defaultHeight) {}

    BarShape( int width, int height )
    {
        rectangle.setSize(width, height);
        // rectangle.setOutlineThickness(1);
        // rectangle.setFillColor(BarVars::barFillColor);
        // rectangle.setOutlineColor(sf::Color::Red);
    }
    void updateValue(const int &value) { rectangle.setHeight(value); }
    void updateValue(const BarShape &value) { updateValue(value.rectangle.getHeight()); }

    int getValue() { return rectangle.getHeight(); }

    void swap(BarShape &other)
    {
        int height1 = other.rectangle.getHeight();
        other.updateValue(rectangle.getHeight());
        updateValue(height1);
        // other.setColor(BarVars::barFillColor);
        // this->setColor(BarVars::barFillColor);
    }

    bool operator<(const BarShape &other) const
    {
        return this->rectangle.getHeight() < other.rectangle.getHeight();
    }

    bool operator>(const BarShape &other) const
    {
        return this->rectangle.getHeight() > other.rectangle.getHeight();
    }

    BarShape &operator=(const BarShape &other)
    {
        this->updateValue(other);
        return *this;
    }
    BarShape &operator=(int value)
    {
        this->updateValue(value);
        return *this;
    }

    operator int() const
    {
        return rectangle.getHeight();
    }

public: // graphics
    // void setColor(sf::Color color) { rectangle.setFillColor(color); }

    // void draw(sf::RenderTarget &rt, sf::RenderStates states) const override
    // {
    //     states.transform *= getTransform();
    //     rt.draw(rectangle, states);
    // }
    void draw(SDL_Renderer *renderer)
    {
        rectangle.draw(renderer);
    }
    void draw()
    {
        draw(Resources::gRenderer);
    }

public: // size and position
    // void setPosition(float x) { rectangle.setPosition({x, rectangle.getPosition().y}); }
   
    // void setSize(float width, float height) { setSize(sf::Vector2f(width, height)); }
    
   

    
};

#endif // BAR_SHAPE