#include "SnakeGame.h"

SnakeGame::SnakeGame():SDLWindow(SDL_INIT_VIDEO,"\xe8\xb4\xaa\xe5\x90\x83\xe8\x9b\x87",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,WIDTH,HEIGHT,SDL_WINDOW_SHOWN)
{
    imageSurface = NULL;
    imageTexture = NULL;
    gameState = START;
    fp = fopen("SnakeGame.log","w");
    if (!fp)
    {
        perror("fopen");
        exit(1);
    }

    snake = new Snake;
    food = new FOOD;
}

SnakeGame::~SnakeGame()
{
    if (fp != NULL)
    {
        fclose(fp);
    }

    if (imageSurface != NULL)
    {
        SDL_FreeSurface(imageSurface);
        imageSurface = NULL;
    }

    if (imageTexture != NULL)
    {
        SDL_DestroyTexture(imageTexture);
        imageTexture = NULL;
    }
}

void SnakeGame::draw()
{
    SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xFF);
    SDL_RenderClear(renderer);

    switch (gameState)
    {
    case START:
        imageSurface = SDL_LoadBMP("start_game.bmp");
        if (!imageSurface)
        {
            fprintf(fp,"Cannot open start_game.bmp!\n");
            exit(1);
        }
        imageTexture = SDL_CreateTextureFromSurface(renderer,imageSurface);
        SDL_FreeSurface(imageSurface);
        imageSurface = NULL;
        SDL_RenderCopy(renderer,imageTexture,NULL,NULL);
        break;

    case WIN:
        if (imageTexture != NULL)
        {
            SDL_DestroyTexture(imageTexture);
            imageTexture = NULL;
        }
        imageSurface = SDL_LoadBMP("win.bmp");
        if (!imageSurface)
        {
            fprintf(fp,"Cannot open win.bmp!\n");
            exit(1);
        }
        imageTexture = SDL_CreateTextureFromSurface(renderer,imageSurface);
        SDL_FreeSurface(imageSurface);
        imageSurface = NULL;
        SDL_RenderCopy(renderer,imageTexture,NULL,NULL);
        break;

    case LOSE:
        if (imageTexture != NULL)
        {
            SDL_DestroyTexture(imageTexture);
            imageTexture = NULL;
        }
        imageSurface = SDL_LoadBMP("lose.bmp");
        if (!imageSurface)
        {
            fprintf(fp,"Cannot open lose.bmp!\n");
            exit(1);
        }
        imageTexture = SDL_CreateTextureFromSurface(renderer,imageSurface);
        SDL_FreeSurface(imageSurface);
        imageSurface = NULL;
        SDL_RenderCopy(renderer,imageTexture,NULL,NULL);
        break;

    case PLAYING:
        update();

        if (snake->body[0].x <= 0 || snake->body[0].x >= WIDTH || snake->body[0].y <= 0 || snake->body[0].y >= HEIGHT)
        {
            gameState = LOSE;
        }

        for (int i = 1; i < snake->size; ++i)
        {
            if (snake->body[0].x == snake->body[i].x && snake->body[0].y == snake->body[i].y)
            {
                gameState = LOSE;
                break;
            }
        }

        if (snake->body[0].x == food->x && snake->body[0].y == food->y)
        {
            ++snake->size;
            initFood();
            if (dy == 10)
            {
                snake->body[snake->size - 1].x = snake->body[snake->size - 2].x;
                snake->body[snake->size - 1].y = snake->body[snake->size - 2].y - 10;
            }
            else if (dy == -10)
            {
                snake->body[snake->size - 1].x = snake->body[snake->size - 2].x;
                snake->body[snake->size - 1].y = snake->body[snake->size - 2].y + 10;
            }
            else if (dx == 10)
            {
                snake->body[snake->size - 1].x = snake->body[snake->size - 2].x - 10;
                snake->body[snake->size - 1].y = snake->body[snake->size - 2].y;
            }
            else if (dx == -10)
            {
                snake->body[snake->size - 1].x = snake->body[snake->size - 2].x + 10;
                snake->body[snake->size - 1].y = snake->body[snake->size - 2].y;
            }
        }

        if (gameState == LOSE)
        {
            break;
        }

        SDL_Rect headrect = {snake->body[0].x,snake->body[0].y,10,10};
        SDL_SetRenderDrawColor(renderer, 0x00,0xFF,0xFF,0xFF);
        SDL_RenderFillRect(renderer,&headrect);
        for (int i = 1; i < snake->size; ++i)
        {
            SDL_Rect rect = {snake->body[i].x,snake->body[i].y,10,10};
            SDL_SetRenderDrawColor(renderer, 0xFF,0xFF,0xFF,0xFF);
            SDL_RenderFillRect(renderer,&rect);
        }
        SDL_Rect foodRect = {food->x,food->y, 10,10};
        SDL_SetRenderDrawColor(renderer,0x00,0xFF,0x00,0xFF);
        SDL_RenderFillRect(renderer,&foodRect);
        break;
    }

    SDL_RenderPresent(renderer);
}

void SnakeGame::start()
{
    while (true)
    {
        SDL_Event event;

        int begin = SDL_GetTicks();

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                return;

            case SDL_MOUSEBUTTONDOWN:
                if (gameState == START)
                {
                    dx = 0;
                    dy = -10;
                    initSnake();
                    initFood();
                    gameState = PLAYING;
                }
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    return;
                case SDLK_s:
                    dx = 0;
                    dy = -10;
                    initSnake();
                    initFood();
                    gameState = PLAYING;
                    break;
                case SDLK_LEFT:
                    dx = -10;
                    dy = 0;
                    break;

                case SDLK_RIGHT:
                    dx = 10;
                    dy = 0;
                    break;

                case SDLK_UP:
                    dx = 0;
                    dy = -10;
                    break;
                case SDLK_DOWN:
                    dx = 0;
                    dy = 10;
                    break;
                }
            }
        }

        draw();

        int end = SDL_GetTicks();
        int time_ = end - begin;
        int rate = 1000 / FRAMERATE;
        int delay = rate - time_;

        if (delay > 0)
        {
            SDL_Delay(delay);
        }
    }
}

void SnakeGame::initFood()
{
    srand((unsigned)time(NULL) + rand()); // 更新随机数种子
    food->x = (rand() % (WIDTH / 10)) * 10;
    food->y = (rand() % (HEIGHT / 10)) * 10;
}

void SnakeGame::initSnake()
{
    snake->size = 2; // 一个蛇头，一个蛇身
    snake->body[0].x = WIDTH / 2;
    snake->body[0].y  = HEIGHT / 2;
    snake->body[1].x = snake->body[0].x;
    snake->body[1].y = snake->body[0].y + 10;
}

void SnakeGame::update()
{
    for (int i = snake->size; i > 0; --i)
    {
        snake->body[i].x = snake->body[i - 1].x;
        snake->body[i].y = snake->body[i - 1].y;
    }
    // 更新蛇头
    snake->body[0].x += dx;
    snake->body[0].y += dy;
}
