#include "SDLWindow.h"

SDLWindow::SDLWindow(Uint32 init_flags,const char *title,int x, int y, int w,int h, Uint32 window_flags)
{
    log = fopen("SDLWindow.log","w");
    window = NULL;
    renderer = NULL;
    if (!log)
    {
        perror("fopen");
        exit(1);
    }

    if (SDL_Init(init_flags) < 0)
    {
        fprintf(log,"Cannot init SDL2! Error: %s\n",SDL_GetError());
        exit(1);
    }
    else
    {
        window = SDL_CreateWindow(title,x,y,w,h,window_flags);
        if (!window)
        {
            fprintf(log,"Cannot create window! Error: %s\n",SDL_GetError());
            exit(1);
        }
        else
        {
            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if (!renderer)
            {
                fprintf(log,"Cannot create renderer! Error: %s\n",SDL_GetError());
                exit(1);
            }
        }
    }
}

SDLWindow::~SDLWindow()
{
    if (log)
    {
        fclose(log);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();
}

void SDLWindow::show()
{
    while (true)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                return;
            }
        }
    }
}
