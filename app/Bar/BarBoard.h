#ifndef BAR_BOARD
#define BAR_BOARD

#include "../global.hpp"
#include "../smartArray.hpp"
#include "BarShape.h"
class BarBoard : public sf::Drawable,
                 public sf::Transformable
{
private:
    SmartArray<BarShape> bars;
    int max_dist, *barCount, *barWidth, *height, *spacing, width, *sortingDelay;

    sf::Sound beep;
    const bool *enableSound;

public:
    BarBoard(int &barCount,
             int &height,
             int &barWidth,
             int &spacing,
             int &sortingDelay)
        : barCount(&barCount),
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
        bars.memoryStats.resetStats();

        for (size_t i = 1; i < *barCount; i++)
        {
            size_t j = i;
            while (j > 0 && bars.read(j) < bars.read(j - 1))
            {
                bars.swap(j, j - 1);
                j--;
                sleep();
            }
        }
        Resources::appendDebugText("");
        Resources::appendDebugText(bars.memoryStats.to_string());

        bars.memoryStats.resetStats();
    }

private:
    void sleep()
    {
        auto stamp = std::chrono::high_resolution_clock::now() +
                     std::chrono::microseconds(maxDelay - range * (*sortingDelay / 99));
        std::this_thread::sleep_until(stamp);
    }
    const int minDelay = 200;
    const int maxDelay = 100'000;
    const int range = maxDelay - minDelay;
};

#endif // BAR_BOARD