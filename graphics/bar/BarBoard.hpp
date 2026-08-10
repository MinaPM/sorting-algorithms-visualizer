#ifndef BAR_BOARD
#define BAR_BOARD

// #include "../../src/global.hpp"
#include "../../src/smartArray.hpp"
#include "BarShape.hpp"

class BarBoard
{
private:
    SmartArray<BarShape> *bars;
    int max_dist, *barCount, *barWidth, *height, *spacing, width;

    // removed temporary
    // sf::Sound beep;
    const bool *enableSound;

public:
    BarBoard()
    {
    }

    BarBoard(int *barCount,
             int *height,
             int *barWidth,
             int *spacing,
             SmartArray<BarShape> &bars)
        : bars(&bars),
          barCount(barCount),
          height(height),
          barWidth(barWidth),
          spacing(spacing)
    {
        updateBarCount();
    }

    void setPosition(float x = 0, float y = 0)
    {
        float last = x;
        for (auto &bar : *bars)
        {
            bar.rectangle.setPosition(last, y);
            last += *barWidth + *spacing;
        }
    }

    void center()
    {
        width = (bars->length() - 1) * (*barWidth + *spacing);
        int x1 = ((int)(Resources::window_size.x) - width) / 2;
        int y1 = (Resources::window_size.y + Resources::padding.bottom);
        setPosition(x1, y1);
    }

    void updateBarCount()
    {
        *barCount = std::min(*barCount,
                             ((int)Resources::window_size.x / (*barWidth + *spacing)));

        bars->resize(*barCount, BarShape(*barWidth, *height));
        center();
    }

    void updateBarSize()
    {
        *barWidth = std::min(*barWidth,
                             ((int)Resources::window_size.x / ((int)bars->length()) - *spacing));
        for (auto &bar : *bars)
        {
            bar.rectangle.setWidth(*barWidth);
        }
        center();
    }

    void updateSpacing()
    {
        *spacing = std::min(*spacing,
                            ((int)Resources::window_size.x / ((int)bars->length()) - *barWidth));

        center();
    }

    // void draw(sf::RenderTarget &rt, sf::RenderStates states) const override
    // {
    //     states.transform *= getTransform();

    //     for (auto &bar : *bars)
    //     {
    //         rt.draw(bar, states);
    //     }
    // }
    void draw()  
    {
        for (auto &bar : *bars)
        {
            bar.draw();
        }
    }

    void draw( SDL_Renderer *renderer)  
    {
        for (auto &bar : *bars)
        {
            bar.draw(renderer);
        }
    }
};

#endif // BAR_BOARD
