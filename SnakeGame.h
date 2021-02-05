#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include "SDLWindow.h"
#include <cstdlib>
#include <ctime>
#define WIDTH 400
#define HEIGHT 400
#define FRAMERATE 10

// 食物
struct FOOD
{
    int x;
    int y;
};

// 身体
struct BODY
{
    int x;
    int y;
};

// 蛇
struct Snake
{
    int size; // 身体长度
    BODY body[(WIDTH / 10) * (HEIGHT / 10)];
};

// 游戏状态
enum GameState
{
    START,
    WIN,
    LOSE,
    PLAYING
};

class SnakeGame : public SDLWindow
{
    public:
        SnakeGame();
        virtual ~SnakeGame();

        GameState gameState;

        void start(); // 开始游戏（相当于事件循环）

    protected:

    private:
        void draw(); // 绘图

        SDL_Surface *imageSurface;
        SDL_Texture *imageTexture;
        FILE *fp; // 日志

        Snake *snake;
        FOOD *food;

        void initSnake();
        void initFood();
        void update(); // 更新坐标

        int dx; // x轴的增量
        int dy; // y轴的增量
};

#endif // SNAKEGAME_H
