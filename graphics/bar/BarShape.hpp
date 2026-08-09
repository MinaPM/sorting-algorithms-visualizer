#ifndef BAR_SHAPE
#define BAR_SHAPE

#include "../../src/global.hpp"
// #include "../../src/smartArray.hpp"
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
    SDL_Rect rectangle{0, 0, BarVars::defaultWidth, BarVars::defaultHeight};

public:
    BarShape() : BarShape(BarVars::defaultWidth, BarVars::defaultHeight) {}

    BarShape( int width, int height )
    {
        setSize(width, height);
        // rectangle.setOutlineThickness(1);
        // rectangle.setFillColor(BarVars::barFillColor);
        // rectangle.setOutlineColor(sf::Color::Red);
    }
    void updateValue(const int &value) { setSize(rectangle.w, value); }
    void updateValue(const BarShape &value) { setSize(rectangle.w, value.rectangle.h); }

    int getValue() { return rectangle.h; }

    void swap(BarShape &other)
    {
        int height1 = other.rectangle.h;
        other.updateValue(rectangle.h);
        updateValue(height1);
        // other.setColor(BarVars::barFillColor);
        // this->setColor(BarVars::barFillColor);
    }

    bool operator<(const BarShape &other) const
    {
        return this->rectangle.h < other.rectangle.h;
    }

    bool operator>(const BarShape &other) const
    {
        return this->rectangle.h > other.rectangle.h;
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
        return rectangle.h;
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
        SDL_SetRenderDrawColor(renderer,
                               BarVars::barFillColor.r,
                               BarVars::barFillColor.g,
                               BarVars::barFillColor.b,
                               BarVars::barFillColor.a);
        SDL_RenderFillRect(renderer, &rectangle);
    }
    void draw()
    {
        draw(Resources::gRenderer);
    }

public: // size and position
    // void setPosition(float x) { rectangle.setPosition({x, rectangle.getPosition().y}); }
    void setPosition(int x) { rectangle.x = x; }
    void setPosition(int x, int y)
    {
        rectangle.x = x;
        rectangle.y = y-rectangle.h;
    }

    // void setSize(float width, float height) { setSize(sf::Vector2f(width, height)); }
    
    void setSize(int height){
        rectangle.h = height;
    }
    void setSize(int width, int height)
    {
        rectangle.w = width;
        rectangle.h = height;
    }
    void setSize(SDL_Point size)
    {
        this->rectangle.w = size.x;
        this->rectangle.h = size.y;
        // rectangle.setSize(size);
        // rectangle.setOrigin(size.componentWiseDiv({2,1}));
    }

    SDL_Point getSize() { return {rectangle.w, rectangle.h}; }
};

#endif // BAR_SHAPE