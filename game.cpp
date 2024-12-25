#include "game.h"

Game::Game()
{

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Failed at SDL_Init" << std::endl;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        std::cout << "Failed to initialize SDL_image: " << IMG_GetError() << std::endl;
        running = false;
        return;
    }

    SDL_CreateWindowAndRenderer(360, 240, 0, &win, &ren);
    SDL_SetWindowTitle(win, "Salim's First Game!!!");
    TTF_Init();
    running = true;

    // star.setDest(50, 50, 75, 75);
    // star.setSource(0, 0, 75, 75);
    // star.setImage("res/image.png", ren);
    font = TTF_OpenFont("sans.ttf", 24);

    // effect.load("res/jumpEffect.wav");
    player.setImage("res/player.png", ren);
    player.setDest(100, 100, 47 * 3, 45 * 3);
    idol = player.createCycle(1, 47, 45, 2, 20);
    shield = player.createCycle(2, 47, 45, 4, 10);
    player.setCurAnimation(idol);

    loop();
}

Game::~Game()
{
    TTF_Quit();
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

void Game::loop()
{
    std::cout << "game started in loop" << std::endl;
    while (running)
    {

        lastFrame = SDL_GetTicks();
        static int lastTime;
        if (lastFrame >= (lastTime + 1000))
        {
            lastTime = lastFrame;
            frameCount = 0;
        }

        render();
        input();
        update();
    }
}

void Game::render()
{
    SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
    SDL_Rect rect;

    rect.x = rect.y = 0;
    rect.w = 360;
    rect.h = 240;
    SDL_RenderFillRect(ren, &rect);

    draw(star);
    draw("this is our first message", 20, 30, 0, 255, 0);

    draw(player);

    frameCount++;
    int timerFPS = SDL_GetTicks() - lastFrame;
    if (timerFPS < (1000 / 60))
    {
        SDL_Delay((1000 / 60) - timerFPS);
    }

    SDL_RenderPresent(ren);
}

void Game::input()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
            running = false;

        if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE)
                running = false;

            if (e.key.keysym.sym == SDLK_w)
            {
                // effect.play();
                std::cout << "W down" << std::endl;
                player.setCurAnimation(shield);
            }
        }

        if (e.type == SDL_KEYUP)
        {
            if (e.key.keysym.sym == SDLK_w)
            {
                std::cout << "W up" << std::endl;
                player.reverse(true, idol);
            }
        }

        SDL_GetMouseState(&mouseX, &mouseY);
    }

    const Uint8 *keystates = SDL_GetKeyboardState(NULL);
}

void Game::draw(Object o)
{
    SDL_Rect dest = o.getDest();
    SDL_Rect src = o.getSource();
    SDL_RenderCopyEx(ren, o.getTex(), &src, &dest, 0, NULL, SDL_FLIP_NONE);
}

void Game::draw(const char *msg, int x, int y, int r, int g, int b)
{
    SDL_Surface *surf;
    SDL_Texture *tex;
    SDL_Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = 255;

    SDL_Rect rect;
    surf = TTF_RenderText_Solid(font, msg, color);
    tex = SDL_CreateTextureFromSurface(ren, surf);
    rect.x = x;
    rect.y = y;
    rect.w = surf->w;
    rect.h = surf->h;

    SDL_FreeSurface(surf);
    SDL_RenderCopy(ren, tex, NULL, &rect);
    SDL_DestroyTexture(tex);
}

void Game::update()
{
    player.updateAnimation();
}