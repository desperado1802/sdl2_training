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

    SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &win, &ren);
    SDL_SetWindowTitle(win, "Salim's First Game!!!");
    TTF_Init();
    running = true;

    font = TTF_OpenFont("res/sans.ttf", 24);

    loadMap("res/1.level");

    // effect.load("res/jumpEffect.wav");
    // player.setImage("res/player.png", ren);
    // player.setDest(100, 100, 47 * 3, 45 * 3);

    loop();
}

Game::~Game()
{
    TTF_CloseFont(font);
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
    SDL_SetRenderDrawColor(ren, 126, 192, 238, 255);
    SDL_Rect rect;

    rect.x = rect.y = 0;
    rect.w = WIDTH;
    rect.h = HEIGHT;
    SDL_RenderFillRect(ren, &rect);

    // draw(player);

    drawMap();

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
            }
        }

        if (e.type == SDL_KEYUP)
        {
            if (e.key.keysym.sym == SDLK_w)
            {
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
    // player.updateAnimation();
}

void Game::loadMap(const char *filename)
{
    std::cout << "loading map" << std::endl;
    int current, mx, my, mw, mh;
    std::ifstream in(filename);
    if (!in.is_open())
    {

        std::cout << "Failed to open map file." << std::endl;
        return;
    }

    in >> mw;
    in >> mh;
    in >> mx;
    in >> my;

    for (size_t i = 0; i < mh; i++)
    {

        for (size_t j = 0; j < mw; j++)
        {
            if (in.eof())
            {
                std::cout << "Reached end of map file too soon." << std::endl;
                return;
            }
            in >> current;
            if (current != 0)
            {
                Object temp;
                temp.setImage("res/tileset.png", ren);
                temp.setSource((current - 1) * 32, 0, 32, 32);
                temp.setDest((j * TILE_SIZE) + mx, (i * TILE_SIZE) + my, TILE_SIZE, TILE_SIZE);
                if (current == 2 || current == 4)
                    temp.setSolid(0);
                map.push_back(temp);
            }
        }
    }

    in.close();
};

void Game::drawMap()
{
    for (size_t i = 0; i < map.size(); i++)
    {
        draw(map[i]);
    }
};