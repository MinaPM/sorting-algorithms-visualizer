#ifndef BAR_BOARD
#define BAR_BOARD

#include "../../src/smartArray.hpp"
#include "BarShape.hpp"

class BarBoard
{
private:
    SmartArray<BarShape> *bars;
    int max_dist, *barCount, *barWidth, *height, *spacing, width;

    Rectangle border;

    // removed temporary
    // sf::Sound beep;
    // const bool *enableSound;

public:
    BarBoard()
    {
    }

    BarBoard(int *barCount,
             int *height,
             int *barWidth,
             int *spacing,
             SmartArray<BarShape> &bars,
             SDL_Rect border)
        : bars(&bars),
          barCount(barCount),
          height(height),
          barWidth(barWidth),
          spacing(spacing),
          border(border)
    {
        this->border.setOutlineColor({255, 0, 0, 255});
        this->border.setOutlineThickness(1);
        this->border.setFillColor({0, 0, 0, 0});
        updateBarCount();
    }

    void setBorder(SDL_Rect borderRect, SDL_Color borderColor = {255, 0, 0, 255}, int thickness = 1)
    {
        border = borderRect;
        border.setOutlineColor(borderColor);
        border.setFillColor({0, 0, 0, 0});
        border.setOutlineThickness(thickness);
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
        int x1 = border.getX() + (border.getWidth() - width) / 2;
        int y1 = (border.getY() + border.getHeight());
        setPosition(x1, y1);
    }

    void updateBarCount()
    {
        *barCount = std::min(*barCount,
                             ((int)border.getWidth() / (*barWidth + *spacing)));

        bars->resize(*barCount, BarShape(*barWidth, *height));
        center();
    }

    void updateBarSize()
    {
        *barWidth = std::min(*barWidth,
                             ((int)border.getWidth() / ((int)bars->length()) - *spacing));
        for (auto &bar : *bars)
        {
            bar.rectangle.setWidth(*barWidth);
        }
        center();
    }

    void updateSpacing()
    {
        *spacing = std::min(*spacing,
                            ((int)border.getWidth() / ((int)bars->length()) - *barWidth));

        center();
    }

    void draw(SDL_Renderer *renderer)
    {
        for (auto &bar : *bars)
        {
            bar.draw(renderer);
        }
        border.draw(renderer);
    }
};

#endif // BAR_BOARD
