#ifndef BAR_SHAPE
#define BAR_SHAPE

#include "../../src/global.hpp"
#include "../Rectangle.hpp"

class BarShape
{
    public:
    Rectangle rectangle;


    BarShape( int width=20, int height=100 )
    {
        rectangle.setSize(width, height);
    }
    void updateValue(const int &value) { rectangle.setHeight(value); }
    void updateValue(const BarShape &value) { updateValue(value.rectangle.getHeight()); }

    int getValue() { return rectangle.getHeight(); }

    void swap(BarShape &other)
    {
        int height1 = other.getValue();
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
        updateValue(other);
        return *this;
    }
    BarShape &operator=(int value)
    {
        updateValue(value);
        return *this;
    }

    operator int() const
    {
        return rectangle.getHeight();
    }

public: 
    void draw(SDL_Renderer *renderer)
    {
        rectangle.draw(renderer);
    }
    
};

#endif // BAR_SHAPE