/*coding:WINDOWS-936*/
#include "SnakeGame.h"

int Main(int argc, char *argv[])
{
    SnakeGame *game = new SnakeGame;
    game->start();

    delete game;

    return 0;
}
