#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <SDL2/SDL.h>
#include <iostream>

#ifdef _WIN32/*coding:WINDOWS-936*/
#ifndef SDLWINDOW_H
#define SDLWINDOW_H

#include <SDL2/SDL.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>

#ifdef _WIN32
#define Main SDL_main
#endif // _WIN32

#ifdef __linux__
#define Main main
#endif // __linux__

class SDLWindow
{
    public:
        SDLWindow(Uint32 init_flags,const char *title,int x, int y, int w,int h, Uint32 window_flags);
        virtual ~SDLWindow();

        SDL_Window *window;
        SDL_Renderer *renderer;

        FILE *log; // 日志

        void show();

    protected:

    private:
};

#endif // SDLWINDOW_H

#define Main SDL_main
#endif // _WIN32

#ifdef __linux__
#define Main main
#endif // __linux__

class SDLWindow
{
    public:
        SDLWindow(Uint32 init_flags, const char *title, int width, int height, Uint32 flags);
        virtual ~SDLWindow();

        int w,h;
        SDL_Window *window; // ´°¿Ú
        SDL_Renderer *renderer; // äÖÈ¾Æ÷

    protected:

    private:
};

#endif // SDLWINDOW_H
