#ifndef GLOBAL_H
#define GLOBAL_H

#include <SDL.h>
#include <SDL_ttf.h>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif
#include <thread>
#include <functional>
#include <iostream>
#include <random>
#include <map>

#include "../graphics/Text.hpp"

namespace Resources
{
    int load_resources()
    {
        // font
        if (TTF_Init() < 0)
        {
            std::cerr << "Couldn't initialize SDL TTF: " << SDL_GetError() << std::endl;
            return 1;
        }
        TTF_Font *font = Text::loadStaticFont("assets/fonts/roboto.ttf");
        if (font == nullptr)
        {
            std::cerr << "Couldn't open font: " << SDL_GetError() << std::endl;
            return 1;
        }

        return 0;
    }

    SDL_Point mousePosition()
    {
        SDL_Point p;
        SDL_GetMouseState(&p.x, &p.y);
        return p;
    }
}

namespace Colors
{

    const SDL_Color RED = {255, 0, 0, 255};
    const SDL_Color GREEN = {0, 255, 0, 255};
    const SDL_Color BLUE = {0, 0, 255, 255};
    const SDL_Color BLACK = {0, 0, 0, 255};
    const SDL_Color WHITE = {255, 255, 255, 255};
    const SDL_Color GRAY = {128, 128, 128, 255};
    const SDL_Color TRANSPARENT = {0, 0, 0, 0};

    const SDL_Color MAIN = RED;
    const SDL_Color SECONDARY = BLUE;
    const SDL_Color BACKGROUND = GRAY;
    const SDL_Color DISABLED = GRAY;
    const SDL_Color TEXT = WHITE;
    const SDL_Color OUTLINE = WHITE;

}

#endif // GLOBAL_H
