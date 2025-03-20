#include "menu.h"
#include <iostream>

Menu::Menu() : font(nullptr) {}

Menu::~Menu()
{
    if (font)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }
}

bool Menu::loadFont(const std::string& font_path, int font_size)
{
    if (TTF_Init() == -1)
    {
        std::cerr << "TTF_Init error: " << TTF_GetError() << std::endl;
        return false;
    }

    font = TTF_OpenFont(font_path.c_str(), font_size);
    if (!font)
    {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

bool Menu::loadBackground(const std::string& path, SDL_Renderer* screen)
{
    return background.LoadImg(path, screen);
}

void Menu::renderText(SDL_Renderer* screen, const std::string& text, int x, int y, SDL_Color color)
{
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface)
    {
        std::cerr << "Failed to create text surface: " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(screen, surface);

    // Căn giữa chữ
    int text_width = surface->w;
    int text_height = surface->h;
    SDL_Rect destRect = {SCREEN_WIDTH / 2 - text_width / 2, y, text_width, text_height};

    SDL_RenderCopy(screen, texture, nullptr, &destRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

int Menu::showMenu(SDL_Renderer* screen)
{
    bool inMenu = true;
    int selectedOption = -1;
    SDL_Event event;

    while (inMenu)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                return 1; // Thoát game
            }
            else if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_RETURN)
                {
                    selectedOption = 0; // Bắt đầu game
                    inMenu = false;
                }
                else if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    selectedOption = 1; // Thoát game
                    inMenu = false;
                }
            }
        }

        SDL_SetRenderDrawColor(screen, 0, 0, 0, 255);
        SDL_RenderClear(screen);

        // Hiển thị background menu
        background.Render(screen, NULL);

        SDL_Color white = {255, 255, 255, 255};
        renderText(screen, "Start - Press Enter", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, white);
        renderText(screen, "Quit - Press Esc", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 50, white);

        SDL_RenderPresent(screen);
    }

    return selectedOption;
}
