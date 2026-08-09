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

// #include "smartArray.hpp"

// #include "../algorithms/SortAlgorithm.hpp"
// #include "../algorithms/BubbleSort.hpp"
// #include "../algorithms/HeapSort.hpp"
// #include "../algorithms/InsertionSort.hpp"
// #include "../algorithms/MergeSort.hpp"
// #include "../algorithms/QuickSort.hpp"

// #include "../graphics/bar/BarShape.hpp"

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
    TTF_Font *font = nullptr;
    // sf::Text debugText(font);
    int characterSize;

    bool load_resourses()
    {
        // loading sound
        // if (!buffer.loadFromFile("assets/audio/beep.wav"))
        //     return false;

        // loading font
        // if (!font.openFromFile("assets/fonts/roboto.ttf"))
        //     return false;
        TTF_Init();
        font = TTF_OpenFont("assets/fonts/roboto.ttf", characterSize);
        if (font == nullptr)
            return false;

        return true;
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
        load_resourses();

        return 0;
        // debugText.setFont(font);
        // debugText.setCharacterSize(characterSize);
        // debugText.setFillColor(sf::Color::Red);
        // debugText.setOutlineColor(sf::Color::Black);
        // debugText.setOutlineThickness(5);
    }

    void renderText(SDL_Renderer *renderer, const std::string &text, int x, int y, SDL_Color color = {255, 0, 0, 255})
    {
        if (!font)
            return;

        SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);
        if (!surface)
            return;

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (!texture)
        {
            SDL_FreeSurface(surface);
            return;
        }

        SDL_Rect dst = {x, y, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, nullptr, &dst);

        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
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
//     SmartArray<BarShape> bars;

//     InsertionSort insersion(bars);
//     MergeSort mergeSort(bars);
//     HeapSort heapSort(bars);
//     QuickSort quickSort(bars);
//     BubbleSort bubbleSort(bars);

//     Algorithm *sortingAlgorithm;

//     void setAlgorithm(int algorithmChoice)
//     {
//         switch (algorithmChoice)
//         {
//         case 0:
//             sortingAlgorithm = &insersion;
//             break;
//         case 1:
//             sortingAlgorithm = &heapSort;
//             break;
//         case 2:
//             sortingAlgorithm = &mergeSort;
//             break;
//         case 3:
//             sortingAlgorithm = &quickSort;
//             break;
//         case 4:
//             sortingAlgorithm = &bubbleSort;
//             break;

//         default:
//             sortingAlgorithm = &insersion;
//             break;
//         }
//     }
// }

#endif // GLOBAL_H
