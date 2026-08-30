#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SDL2/SDL.h>

class Rectangle
{
private:
    SDL_Rect rect{0, 0, 0, 0};
    SDL_Color fillColor{255, 255, 255, 255};
    SDL_Color outlineColor{0, 0, 0, 255};
    int outlineThickness{0};

public:
    Rectangle() = default;

    Rectangle(int x, int y, int w, int h)
        : rect{x, y, w, h} {}

    Rectangle(int x, int y, int w, int h, SDL_Color fill, SDL_Color outline = {0, 0, 0, 255}, int thickness = 0)
        : rect{x, y, w, h}, fillColor(fill), outlineColor(outline), outlineThickness(thickness) {}

    Rectangle(SDL_Rect rect, SDL_Color fill, SDL_Color outline = {0, 0, 0, 255}, int thickness = 0)
        : rect(rect), fillColor(fill), outlineColor(outline), outlineThickness(thickness) {}

    explicit Rectangle(const SDL_Rect &other) : rect(other) {}

    Rectangle(const Rectangle &other)
        : rect(other.rect), fillColor(other.fillColor), outlineColor(other.outlineColor), outlineThickness(other.outlineThickness) {}   


    // position
    int getX() const { return rect.x; }
    int getY() const { return rect.y; }
    SDL_Point getPosition() const { return {rect.x, rect.y}; }

    void setX(int x) { rect.x = x; }
    void setY(int y) { rect.y = y - rect.h; }

    void setPosition(SDL_Point point)
    {
        setX(point.x);
        setY(point.y);
    }
    void setPosition(int x, int y)
    {
        setX(x);
        setY(y);
    }

    // size
    int getWidth() const { return rect.w; }
    int getHeight() const { return rect.h; }
    SDL_Point getSize() const { return {rect.w, rect.h}; }

    void setWidth(int w) { rect.w = w; }
    void setHeight(int h)
    {
        rect.y += rect.h - h;
        rect.h = h;
    }
    void setSize(SDL_Point size)
    {
        setWidth(size.x);
        setHeight(size.y);
    }

    void setSize(int w, int h)
    {
        setWidth(w);
        setHeight(h);
    }

    // color
    void setFillColor(SDL_Color color) { fillColor = color; }
    void setOutlineColor(SDL_Color color) { outlineColor = color; }
    void setOutlineThickness(int thickness) { outlineThickness = thickness < 0 ? 0 : thickness; }

    SDL_Color getFillColor() const { return fillColor; }
    SDL_Color getOutlineColor() const { return outlineColor; }
    int getOutlineThickness() const { return outlineThickness; }

    // SDL_Rect access
    SDL_Rect getSDLRect() const
    {
        return rect;
    }

    Rectangle &operator=(const SDL_Rect &other)
    {
        rect = other;
        return *this;
    }
    const SDL_Rect &getSDLRectRef() const
    {
        return rect;
    }

    // operator overloads
    operator SDL_Rect() const
    {
        return rect;
    }

    Rectangle operator+(SDL_Rect other) const
    {
        SDL_Rect bounding;
        SDL_UnionRect(&rect, &other, &bounding);

        return Rectangle(bounding, fillColor, outlineColor, outlineThickness);
    }

    Rectangle operator+(const Rectangle &other) const
    {
        return *this + other.getSDLRect();
    }

    void draw(SDL_Renderer *renderer) const
    {
        if (!renderer)
            return;

        if (rect.w <= 0 || rect.h <= 0)
            return;

        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

        // Fill
        SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
        SDL_RenderFillRect(renderer, &rect);

        // Outline
        if (outlineThickness > 0)
        {
            SDL_SetRenderDrawColor(renderer, outlineColor.r, outlineColor.g, outlineColor.b, outlineColor.a);

            for (int i = 0; i < outlineThickness; ++i)
            {
                SDL_Rect outlineRect{
                    rect.x + i,
                    rect.y + i,
                    rect.w - (2 * i),
                    rect.h - (2 * i)};

                if (outlineRect.w <= 0 || outlineRect.h <= 0)
                {
                    break;
                }

                SDL_RenderDrawRect(renderer, &outlineRect);
            }
        }
    }
};

#endif // RECTANGLE_HPP