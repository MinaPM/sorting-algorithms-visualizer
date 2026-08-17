#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <SDL2/SDL.h>

class Renderer
{

    SDL_Point window_size;
    SDL_Window *window = nullptr;
    SDL_Renderer *gRenderer = nullptr;
    bool windowRunning = true;

public:
    SDL_Renderer *getRenderer() { return gRenderer; }

    bool isRunning()
    {
        return windowRunning;
    }

    SDL_Point getWindowSize()
    {
        return window_size;
    }

    void setWindowSize(int width, int height)
    {
        window_size.x = width;
        window_size.y = height;
    }

    int initialize()
    {
        if (SDL_Init(SDL_INIT_VIDEO) != 0)
        {
            SDL_Log("SDL_Init failed: %s", SDL_GetError());
            return 1;
        }

        window = SDL_CreateWindow("SDL2 Square",
                                  SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED,
                                  window_size.x,
                                  window_size.y,
                                  SDL_WINDOW_SHOWN);

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

        return 0;
    }

    void stop()
    {
        windowRunning = false;
    }

    void clear()
    {
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);
    }

    void present()
    {
        SDL_RenderPresent(gRenderer);
    }

    operator SDL_Renderer *() { return gRenderer; }

    ~Renderer()
    {
        SDL_DestroyRenderer(gRenderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

#endif // RENDERER_HPP