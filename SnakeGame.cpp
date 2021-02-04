/*coding:WINDOWS-936*/
#include "SnakeGame.h"

SnakeGame::SnakeGame():SDLWindow(SDL_INIT_VIDEO,"\xe8\xb4\xaa\xe5\x90\x83\xe8\x9b\x87",WIDTH,HEIGHT,SDL_WINDOW_SHOWN)
{
    gameState = START;
    this->image = nullptr;

    this->snake = new Snake;
    init_snake();
    init_food();
}

void SnakeGame::init_snake()
{
    this->snake->size = 2;
    this->snake->body[0].x = WIDTH / 2 - 5;
    this->snake->body[0].y = HEIGHT / 2 - 5;

    this->snake->body[1].x = snake->body[0].x;
    this->snake->body[1].y = snake->body[0].y + 10;
}

SnakeGame::~SnakeGame()
{
    delete snake;
    if (imageTexture != nullptr)
    {
        SDL_DestroyTexture(imageTexture);
        imageTexture = nullptr;
    }
}

void SnakeGame::start()
{
    this->eventLoop();
}

void SnakeGame::draw(int dx,int dy)
{
    SDL_SetRenderDrawColor(renderer,0x00,0x00,0x00,0xFF);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawBlendMode(renderer,SDL_BLENDMODE_BLEND);

    switch (this->gameState)
    {
    case START:
        if (imageTexture != nullptr)
        {
            SDL_DestroyTexture(imageTexture);
            imageTexture = nullptr;
        }
        this->image = SDL_LoadBMP("start_game.bmp");
        if (!image)
        {
            SDL_Log("Cannot open start_game.bmp!");
            exit(1);
        }
        imageTexture = SDL_CreateTextureFromSurface(renderer,image);
        SDL_FreeSurface(this->image);
        this->image = nullptr;
        SDL_RenderCopy(renderer,imageTexture,NULL,NULL);
        break;
    case LOSE:
        if (imageTexture != nullptr)
        {
            SDL_DestroyTexture(imageTexture);
            imageTexture = nullptr;
        }
        this->image = SDL_LoadBMP("lose.bmp");
        if (!image)
        {
            SDL_Log("Cannot open lose.bmp!");
            exit(1);
        }
        imageTexture = SDL_CreateTextureFromSurface(renderer,image);
        SDL_FreeSurface(this->image);
        this->image = nullptr;
        SDL_RenderCopy(renderer,imageTexture,NULL,NULL);
        break;
    case WIN:
        if (imageTexture != nullptr)
        {
            SDL_DestroyTexture(imageTexture);
            imageTexture = nullptr;
        }
        this->image = SDL_LoadBMP("win.bmp");
        if (!image)
        {
            SDL_Log("Cannot open win.bmp!");
            exit(1);
        }
        imageTexture = SDL_CreateTextureFromSurface(renderer,image);
        SDL_FreeSurface(this->image);
        this->image = nullptr;
        SDL_RenderCopy(renderer,imageTexture,NULL,NULL);
        break;
    case PLAYING:
        if (this->snake->size == (WIDTH * HEIGHT) / 100)
        {
            gameState = WIN;
        }
        for (int i = this->snake->size - 1; i > 0; --i)
        {
            this->snake->body[i].x = this->snake->body[i - 1].x;
            this->snake->body[i].y = this->snake->body[i - 1].y;
        }
        this->snake->body[0].x += dx;
        this->snake->body[0].y += dy;

        // 蛇不能撞墙，不能撞自己
        if (this->snake->body[0].x <= 0 || this->snake->body[0].x >= WIDTH || this->snake->body[0].y <= 0 || this->snake->body[0].y >= HEIGHT)
        {
            gameState = LOSE;
            break;
        }

        for (int i = 1; i < this->snake->size; ++i)
        {
            if (this->snake->body[0].x == this->snake->body[i].x && this->snake->body[0].y == this->snake->body[i].y)
            {
                gameState = LOSE;
            }
        }

        if (gameState == LOSE)
        {
            break;
        }

        // 是否撞到食物
        if (this->snake->body[0].x >= food.x && this->snake->body[0].x <= food.x + 10 && this->snake->body[0].y >= food.y && this->snake->body[0].y <= food.y + 10)
        {
            ++this->snake->size;
            if (dx == 10)
            {
                this->snake->body[this->snake->size - 1].x = this->snake->body[this->snake->size - 2].x - 10;
                this->snake->body[this->snake->size - 1].y = this->snake->body[this->snake->size - 2].y;
            }
            else if (dx == -10)
            {
                this->snake->body[this->snake->size - 1].x = this->snake->body[this->snake->size - 2].x + 10;
                this->snake->body[this->snake->size - 1].y = this->snake->body[this->snake->size - 2].y;
            }
            else if (dy == 10)
            {
                this->snake->body[this->snake->size -1].x = this->snake->body[this->snake->size -2].x;
                this->snake->body[this->snake->size - 1].y = this->snake->body[this->snake->size - 2].y - 10;
            }
            else if (dy == -10)
            {
                this->snake->body[this->snake->size -1].x = this->snake->body[this->snake->size -2].x;
                this->snake->body[this->snake->size - 1].y = this->snake->body[this->snake->size - 2].y + 10;
            }

            init_food();
        }

        SDL_SetRenderDrawColor(renderer,0x00,0xFF,0xFF,0xFF);
        SDL_Rect rect = {this->snake->body[0].x,this->snake->body[0].y,10,10};
        SDL_RenderFillRect(renderer,&rect);
        for (int i = 1; i < snake->size; ++i)
        {
            SDL_SetRenderDrawColor(renderer,0xFF,0xFF,0xFF,0xFF);
            SDL_Rect rect = {this->snake->body[i].x,this->snake->body[i].y,10,10};
            SDL_RenderFillRect(renderer,&rect);
        }

        SDL_Rect foodrect = {food.x,food.y,10,10};
        SDL_SetRenderDrawColor(renderer,0x00,0xFF,0x00,0xFF);
        SDL_RenderFillRect(renderer,&foodrect);
    }

    SDL_RenderPresent(renderer);
}

void SnakeGame::eventLoop()
{
    static int dx = 0;
    static int dy = -10;
    while (true)
    {
        int begin = SDL_GetTicks();
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                goto END;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_s:
                    init_snake();
                    init_food();
                    this->gameState = PLAYING;
                    break;
                case SDLK_ESCAPE:
                    goto END;

                    // 蛇移动
                case SDLK_LEFT:
                    switch (gameState)
                    {
                    case PLAYING:
                        dx = -10;
                        dy = 0;
                        break;
                    case START:
                        break;
                    case WIN:
                        break;
                    case LOSE:
                        break;
                    }
                    break;

                case SDLK_RIGHT:
                    switch (gameState)
                    {
                    case PLAYING:
                        dx = 10;
                        dy = 0;
                        break;
                    case START:
                        break;
                    case WIN:
                        break;
                    case LOSE:
                        break;
                    }
                    break;

                case SDLK_UP:
                    switch (gameState)
                    {
                    case PLAYING:
                        dx = 0;
                        dy = -10;
                        break;
                    case START:
                        break;
                    case WIN:
                        break;
                    case LOSE:
                        break;
                    }
                    break;

                case SDLK_DOWN:
                    switch (gameState)
                    {
                    case PLAYING:
                        dx = 0;
                        dy = 10;
                        break;
                    case START:
                        break;
                    case WIN:
                        break;
                    case LOSE:
                        break;
                    }
                    break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (this->gameState)
                {
                case START:
                    this->gameState = PLAYING;
                    break;
                }
                break;
            }
        }

        this->draw(dx,dy);

        int end = SDL_GetTicks();
        int time_ = end - begin;
        int delay = (1000 / FRAMESTATE) - time_;

        if (delay > 0 && gameState == PLAYING)
        {
            SDL_Delay(delay);
        }
    }
END:
    return;
}

void SnakeGame::init_food()
{
    srand((unsigned)time(NULL) + rand());
    food.x = (rand() % (WIDTH / 10)) * 10;
    food.y = (rand() % (HEIGHT / 10)) * 10;
}
