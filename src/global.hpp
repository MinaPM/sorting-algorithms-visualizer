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
#include "../graphics/Rectangle.hpp"



namespace Resources
{

    struct Padding
    {
        int top = 10, left = 10, right = -10, bottom = -10;
    } padding;

    // sf::ContextSettings settings;
    SDL_Point window_size;
    // sf::RenderWindow window;
    static SDL_Window *window = nullptr;
    static SDL_Renderer *gRenderer = nullptr;
    static bool windowRunning = true;

    // sf::SoundBuffer buffer;
    // sf::Text debugText(font);
    int characterSize;

    int load_resourses()
    {
        //font
        if (TTF_Init() < 0)
        {
            std::cerr << "Couldn't initialize SDL TTF: " << SDL_GetError() << std::endl;
            return 1;
        }
        TTF_Font* font = Text::loadStaticFont("assets/fonts/roboto.ttf", characterSize);
        if (font == nullptr)
        {
            std::cerr << "Couldn't open font: " << SDL_GetError() << std::endl;
            return 1;
        }


        return 0;
    }

    int initialize()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            SDL_Log("SDL_Init failed: %s", SDL_GetError());
            return 1;
        }

        window_size = {1500, 900};
        // settings.antiAliasingLevel = 0;
        // window.create(sf::VideoMode(window_size), "Sorting Algorithm Visualizer",
        //               sf::Style::Close,
        //               sf::State::Windowed,
        //               settings);

        window = SDL_CreateWindow("SDL2 Square",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  window_size.x,
                                  window_size.y,
                                  SDL_WINDOW_SHOWN);

        // window.setFramerateLimit(30);
        if (!window)
        {
            SDL_Log("SDL_CreateWindow failed: %s", SDL_GetError());
            SDL_Quit();
            return 1;
        }

        gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (!gRenderer)
        {
            SDL_Log("SDL_CreateRenderer failed: %s", SDL_GetError());

            SDL_DestroyWindow(window);
            SDL_Quit();
            return 1;
        }
        characterSize = 20;
        if (load_resourses())
        {
            std::cout << "Failed to load font." << std::endl;
            Resources::windowRunning = false;
            return 1;
        }

        return 0;
        // debugText.setFont(font);
        // debugText.setCharacterSize(characterSize);
        // debugText.setFillColor(sf::Color::Red);
        // debugText.setOutlineColor(sf::Color::Black);
        // debugText.setOutlineThickness(5);
    }


    // void setDebugText(std::string s)
    // {
    //     debugText.setString(s);
    //     debugText.setPosition({window_size.x - debugText.getGlobalBounds().size.x + padding.right,
    //                            window_size.y - debugText.getGlobalBounds().size.y + padding.bottom * 2});
    // }

    // void appendDebugText(std::string s)
    // {
    //     setDebugText(debugText.getString() + "\n" + s);
    // }

    // sf::Vector2i mousePosition() { return sf::Mouse::getPosition(window); }
    SDL_Point mousePosition()
    {
        SDL_Point p;
        SDL_GetMouseState(&p.x, &p.y);
        return p;
    }

    // close event
    // const auto onClose = [](const sf::Event::Closed &)
    // {
    //     window.close();
    // };
}

// namespace GlobalVars
// {

// }

#endif // GLOBAL_H
