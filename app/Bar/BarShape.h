#ifndef BAR_SHAPE
#define BAR_SHAPE

#include "../global.hpp"

class BarShape : public sf::Drawable, public sf::Transformable
{
    sf::RectangleShape rectangle;
    int width, height;

public:
    float tile_size;

    BarShape() : BarShape(20, 100) {}

    BarShape(const int &width, const int &height)
    {
        rectangle.setOutlineThickness(1);
        setSize(width, height);
        rectangle.setFillColor(sf::Color::White);
        rectangle.setOutlineColor(sf::Color::Red);
    }

    void updateValue(const int &value)
    {
        this->height = value;
        setSize(width, height);
    }

    void setPosition(float x)
    {
        rectangle.setPosition(x, rectangle.getPosition().y);
    }

    void setPosition(float x, float y)
    {
        rectangle.setPosition(x, y);
    }

    void setColor(sf::Color color) { rectangle.setFillColor(color); }

    void setSize(float width, float height)
    {
        this->width = width;
        this->height = height;
        rectangle.setSize(sf::Vector2f(width, height));
        rectangle.setOrigin(width / 2, height);
    }

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        rt.draw(rectangle, states);
    }
};

class BarBoard : public sf::Drawable,
                 public sf::Transformable
{
private:
    std::vector<BarShape> bars;
    int max_dist, *barCount, *barWidth, *height, *spacing, width;

    sf::Sound beep;
    const bool *enableSound;

public:
    BarBoard(int &barCount, int &height, int &barWidth, int &spacing) : barCount(&barCount),
                                                                        height(&height),
                                                                        barWidth(&barWidth),
                                                                        spacing(&spacing)
    {

        updateBarCount();
    }

    void setPosition(float x = 0, float y = 0)
    {
        float last = x;
        for (auto &bar : bars)
        {
            bar.setPosition(last, y);
            last += *barWidth + *spacing;
        }
    }

    void center()
    {
        width = (*barCount - 1) * (*barWidth + *spacing);
        int x1 = ((int)(Resources::window_size.x) - width) / 2;
        int y1 = (Resources::window_size.y + Resources::padding.bottom);
        setPosition(x1, y1);
    }

    void updateBarCount()
    {
        *barCount = std::min(*barCount,
                             ((int)Resources::window_size.x / (*barWidth + *spacing)));

        bars.resize(*barCount, BarShape(*barWidth, *height));
        center();
    }

    void updateBarSize()
    {
        *barWidth = std::min(*barWidth,
                             ((int)Resources::window_size.x / (*barCount) - *spacing));
        for (auto &bar : bars)
        {
            bar.setSize(*barWidth, *height);
        }
        center();
    }

    void updateSpacing()
    {
        *spacing = std::min(*spacing,
                            ((int)Resources::window_size.x / (*barCount) - *barWidth));

        center();
    }

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override
    {
        states.transform *= getTransform();

        for (auto &bar : bars)
        {
            rt.draw(bar, states);
        }
    }
};

#endif // BAR_SHAPE