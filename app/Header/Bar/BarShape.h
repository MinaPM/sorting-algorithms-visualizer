#ifndef BAR_SHAPE
#define BAR_SHAPE

#include "../../global.hpp"

class BarShape : public sf::Drawable, public sf::Transformable
{
    sf::RectangleShape rectangle;
    int width, height;

public:
    float tile_size;

    BarShape() : BarShape(20, 100) {}

    BarShape(const int &width, const int &height)
    {
        this->width = width;
        this->height = height;
        rectangle.setSize(sf::Vector2f(width, height));
        rectangle.setFillColor(sf::Color::White);

        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(1);

        rectangle.setOrigin(width / 2, height);
    }

    void update_value(const int &value)
    {
        this->height = value;
        rectangle.setSize(sf::Vector2f(width, height));
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
    int max_dist, *barCount, width, height, barWidth, spacing;

    sf::Sound beep;
    const bool *enableSound;

public:
    BarBoard(int *barCount, int height, int barWidth, int spacing = 20) : barCount(barCount)
    {
        this->height = height;
        this->barWidth = barWidth;
        this->spacing = spacing;

        this->barCount = barCount;

        this->width = (barWidth + spacing) * *barCount - spacing;

        barWidth = (width / *barCount) * .9;
        setBarCount();
    }

    void setPosition(float x = 0, float y = 0)
    {
        float last = x;
        for (int i = 0; i < bars.size(); i++)
        {
            bars[i].setPosition(last, y);
            last += barWidth + spacing;
        }
    }

    void center_bars()
    {
        int x1 = (Resources::window_size.x - width) / 2;
        int y1 = (Resources::window_size.y + height) / 2;

        setPosition(x1, y1);
    }

    void setBarCount()
    {
        bars.resize(*barCount, BarShape(barWidth, height));

        Resources::appendDebugText(std::to_string(bars.size()));
        center_bars();
    }

    // void update_values(const Tile &tile)
    // {
    //     for (int i = 0; i < N; i++)
    //         for (int j = 0; j < N; j++)
    //             tileShapes[i][j].update_values(
    //                 tile.tiles[i][j],
    //                 tile.H[i][j],
    //                 max_dist);

    //     if (*enableSound)
    //         beep.play();
    // }

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        // for (int i = 0; i < *barCount; i++)
        // {
        //     rt.draw(bars[i], states);
        // }

        for (auto &bar : bars)
        {

            rt.draw(bar, states);
        }
    }
};

#endif // BAR_SHAPE