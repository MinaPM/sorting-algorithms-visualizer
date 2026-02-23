#ifndef BAR_BOARD
#define BAR_BOARD

#include "../global.hpp"
#include "../smartArray.hpp"
#include "BarShape.h"

class BarBoard : public sf::Drawable,
                 public sf::Transformable
{
private:
    SmartArray<BarShape>& bars;
    int max_dist, *barCount, *barWidth, *height, *spacing, width;

    // removed temporary
    // sf::Sound beep;
    const bool* enableSound;

public:
    BarBoard(int& barCount,
             int& height,
             int& barWidth,
             int& spacing,
             SmartArray<BarShape>& bars
    )
        : bars(bars),
          barCount(&barCount),
          height(&height),
          barWidth(&barWidth),
          spacing(&spacing)
    {
        updateBarCount();
    }

    void setPosition(float x = 0, float y = 0)
    {
        float last = x;
        for (auto& bar : bars)
        {
            bar.setPosition(last, y);
            last += *barWidth + *spacing;
        }
    }

    void center()
    {
        width = (bars.length() - 1) * (*barWidth + *spacing);
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
                             ((int)Resources::window_size.x / ((int)bars.length()) - *spacing));
        for (auto& bar : bars)
        {
            bar.setSize(*barWidth, bar.getSize().y);
        }
        center();
    }

    void updateSpacing()
    {
        *spacing = std::min(*spacing,
                            ((int)Resources::window_size.x / ((int)bars.length()) - *barWidth));

        center();
    }

    void draw(sf::RenderTarget& rt, sf::RenderStates states) const override
    {
        states.transform *= getTransform();

        for (auto& bar : bars)
        {
            rt.draw(bar, states);
        }
    }
};



#endif // BAR_BOARD
