#ifndef BAR_SHAPE
#define BAR_SHAPE

#include "../global.hpp"

class BarShape : public sf::Drawable, public sf::Transformable
{
    sf::RectangleShape rectangle;
    int width, height;

public:
    BarShape() : BarShape(20, 100) {}

    BarShape(const int &width, const int &height)
    {
        // rectangle.setOutlineThickness(1);
        setSize(width, height);
        rectangle.setFillColor(sf::Color::White);
        rectangle.setOutlineColor(sf::Color::Red);
    }

    void updateValue(const int &value)
    {
        setSize(width, value);
    }
    void updateValue(const BarShape &value)
    {
        setSize(width, value.height);
    }

    int getValue() { return height; }

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

    sf::Vector2f getSize()
    {
        return rectangle.getSize();
    }

    void draw(sf::RenderTarget &rt, sf::RenderStates states) const override
    {
        states.transform *= getTransform();
        rt.draw(rectangle, states);
    }

    void swap(BarShape &other)
    {
        int height1 = other.height;
        other.updateValue(height);
        updateValue(height1);
    }

    bool operator<(BarShape &other) { return this->height < other.height; }
    bool operator>(BarShape &other) { return this->height > other.height; }
};

class BarBoard : public sf::Drawable,
                 public sf::Transformable
{
private:
    std::vector<BarShape> bars;
    int max_dist, *barCount, *barWidth, *height, *spacing, width, *sortingDelay;

    sf::Sound beep;
    const bool *enableSound;

public:
    BarBoard(int &barCount, int &height, int &barWidth, int &spacing, int &sortingDelay) : barCount(&barCount),
                                                                                           height(&height),
                                                                                           barWidth(&barWidth),
                                                                                           spacing(&spacing),
                                                                                           sortingDelay(&sortingDelay)
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
            bar.setSize(*barWidth, bar.getSize().y);
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

public:
    void shuffle()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, *height);

        for (auto &bar : bars)
        {
            bar.updateValue(distrib(gen));
        }
    }

    void sort()
    {

        for (int i = 1; i < *barCount; i++)
        {
            int j = i;
            while (j > 0 && bars[j] < bars[j - 1])
            {
                bars[j].swap(bars[j - 1]);
                j--;
                sleep();
            }
        }
        Resources::appendDebugText("done!");
    }

private:
    void sleep()
    {
        std::this_thread::sleep_for(std::chrono::microseconds(maxDelay + (minDelay - maxDelay) * (*sortingDelay / 100)));
    }
    const int minDelay = 1000;
    const int maxDelay = 100'000;
};

#endif // BAR_SHAPE