/*coding:WINDOWS-936*/
#include "SDLWindow.h"

SDLWindow::SDLWindow(Uint32 init_flags, const char *title, int width, int height, Uint32 flags):w(width),h(height)
{
    window = nullptr;
    renderer = nullptr;

    if (SDL_Init(init_flags) < 0)
    {
        SDL_Log("Cannot init SDL! Error: %s",SDL_GetError());
        exit(1);
    }
    else
    {
        window = SDL_CreateWindow(title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w,h,flags);
        if (!window)
        {
            SDL_Log("Cannot create window! Error: %s",SDL_GetError());
            exit(1);
        }
        else
        {
            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if (!renderer)
            {
                SDL_Log("Cannot create renderer! Error: %s",SDL_GetError());
                exit(1);
            }
        }
    }
}

SDLWindow::~SDLWindow()
{
    if (renderer)
        SDL_DestroyRenderer(renderer);

    if (window)
        SDL_DestroyWindow(window);

    SDL_Quit();
}
