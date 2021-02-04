/*coding:WINDOWS-936*/
#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "SDLWindow.h"
#include <time.h>
#include <stdlib.h>
#define WIDTH 400
#define HEIGHT 400
#define FRAMESTATE 10

enum GameState
{
    START,
    WIN,
    LOSE,
    PLAYING
};

// 蛇身
struct BODY
{
    int x;
    int y;
};

// 食物
struct FOOD
{
    int x;
    int y;
};

// 蛇
struct Snake
{
    unsigned int size; // 蛇身长度
    BODY body[(WIDTH / 10) * (HEIGHT / 10)];
};

class SnakeGame : public SDLWindow
{
    public:
        SnakeGame();
        ~SnakeGame();

        GameState gameState;

        void draw(int dx,int dy);
        void eventLoop();
        void start();

        SDL_Surface *image;
        SDL_Texture *imageTexture;

        Snake *snake;

        void init_snake();
        void init_food();

        FOOD food;

    protected:

    private:
};

#endif // SNAKEGAME_H
