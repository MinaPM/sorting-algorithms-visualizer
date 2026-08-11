#ifndef TEXT_HPP
#define TEXT_HPP

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

class Text
{
private:
    inline static TTF_Font *s_font{nullptr};

    std::string value;
    SDL_Color color{255, 0, 0, 255};
    int x{0};
    int y{0};

public:
    Text() = default;

    Text(std::string text, int x, int y, SDL_Color color = {255, 0, 0, 255})
        : value(std::move(text)), color(color), x(x), y(y) {}

    static TTF_Font *loadStaticFont(const std::string &fontPath, int size)
    {
        if (!s_font)
        {
            s_font = TTF_OpenFont(fontPath.c_str(), size);
            if (!s_font)
            {
                std::cerr << "Failed to load font in class: " << TTF_GetError() << std::endl;
            }
        }
        return s_font;
    }

    static void closeStaticFont()
    {
        if (s_font)
        {
            TTF_CloseFont(s_font);
            s_font = nullptr;
        }
    }

    // void setFont(TTF_Font* newFont) { font = newFont; }
    void setText(const std::string &text) { value = text; }
    void setPosition(int newX, int newY)
    {
        x = newX;
        y = newY;
    }
    void setPosition(SDL_Point point)
    {
        x = point.x;
        y = point.y;
    }
    void setColor(SDL_Color newColor) { color = newColor; }

    const std::string &getText() const { return value; }
    SDL_Color getColor() const { return color; }
    int getX() const { return x; }
    int getY() const { return y; }

    SDL_Rect getSize() const
    {
        if (!s_font || value.empty())
        {
            return {0, 0, 0, 0};
        }

        int textWidth = 0;
        int textHeight = 0;

        if (TTF_SizeUTF8(s_font, value.c_str(), &textWidth, &textHeight) != 0)
        {
            std::cerr << "Failed to get text size: " << TTF_GetError() << std::endl;
            return {0, 0, 0, 0};
        }

        return {0, 0, textWidth, textHeight};
    }

    bool draw(SDL_Renderer *renderer) const
    {
        if (!renderer || !s_font || value.empty())
        {
            return false;
        }

        SDL_Surface *surface = TTF_RenderText_Blended(s_font, value.c_str(), color);
        if (!surface)
        {
            return false;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture)
        {
            SDL_FreeSurface(surface);
            return false;
        }

        SDL_Rect dst{x, y, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, nullptr, &dst);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
        return true;
    }
};

#endif // TEXT_HPP