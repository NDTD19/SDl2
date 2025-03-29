#include "pause.h"
#include <iostream>

PauseButton::PauseButton() : buttonTexture(nullptr), width(0), height(0) {}

PauseButton::~PauseButton()
{
    freeButtonTexture();
}

bool PauseButton::loadButtonTexture(SDL_Renderer* renderer, const char* filePath)
{
    SDL_Surface* surface = IMG_Load(filePath);
    if (!surface)
    {
        std::cerr << "Failed to load button image: " << filePath << " SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    buttonTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!buttonTexture)
    {
        std::cerr << "Failed to create texture from surface! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return false;
    }

    width = surface->w;
    height = surface->h;

    SDL_FreeSurface(surface);
    return true;
}

void PauseButton::renderButton(SDL_Renderer* renderer, int x, int y)
{
    if (buttonTexture != nullptr)
    {
        SDL_Rect renderQuad = {x, y, width, height};
        SDL_RenderCopy(renderer, buttonTexture, nullptr, &renderQuad);
    }
}

bool PauseButton::handleEvent(SDL_Event* event, int x, int y, int buttonWidth, int buttonHeight)
{
    if (event->type == SDL_MOUSEBUTTONDOWN)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        bool insideButton = true;

        if (mouseX < x)
        {
            insideButton = false;
        }
        else if (mouseX > x + buttonWidth)
        {
            insideButton = false;
        }
        else if (mouseY < y)
        {
            insideButton = false;
        }
        else if (mouseY > y + buttonHeight)
        {
            insideButton = false;
        }

        return insideButton;
    }
    return false;
}

void PauseButton::freeButtonTexture()
{
    if (buttonTexture != nullptr)
    {
        SDL_DestroyTexture(buttonTexture);
        buttonTexture = nullptr;
        width = 0;
        height = 0;
    }
}

int PauseButton::getWidth()
{
    return width;
}

int PauseButton::getHeight()
{
    return height;
}

// PauseMenu implementation
PauseMenu::PauseMenu() : continueTexture(nullptr), menuTexture(nullptr), continueWidth(0), continueHeight(0), menuWidth(0), menuHeight(0) {}

PauseMenu::~PauseMenu()
{
    freeTextures();
}

bool PauseMenu::loadContinueTexture(SDL_Renderer* renderer, const char* filePath)
{
    SDL_Surface* surface = IMG_Load(filePath);
    if (!surface)
    {
        std::cerr << "Failed to load continue image: " << filePath << " SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    continueTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!continueTexture)
    {
        std::cerr << "Failed to create continue texture from surface! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return false;
    }

    continueWidth = surface->w;
    continueHeight = surface->h;

    SDL_FreeSurface(surface);
    return true;
}

bool PauseMenu::loadMenuTexture(SDL_Renderer* renderer, const char* filePath)
{
    SDL_Surface* surface = IMG_Load(filePath);
    if (!surface)
    {
        std::cerr << "Failed to load menu image: " << filePath << " SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    menuTexture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!menuTexture)
    {
        std::cerr << "Failed to create menu texture from surface! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_FreeSurface(surface);
        return false;
    }

    menuWidth = surface->w;
    menuHeight = surface->h;

    SDL_FreeSurface(surface);
    return true;
}


void PauseMenu::renderPauseMenu(SDL_Renderer* renderer, int screenWidth, int screenHeight)
{
    // Calculate positions for the "Continue" and "Menu" buttons in the center of the screen
    int continueX = (screenWidth - continueWidth) / 2;
    int continueY = (screenHeight / 2) - continueHeight - 20; // Above the center

    int menuX = (screenWidth - menuWidth) / 2;
    int menuY = (screenHeight / 2) + 20; // Below the center

    // Render the "Continue" button
    if (continueTexture != nullptr)
    {
        SDL_Rect continueRect = {continueX, continueY, continueWidth, continueHeight};
        SDL_RenderCopy(renderer, continueTexture, nullptr, &continueRect);
    }

    // Render the "Menu" button
    if (menuTexture != nullptr)
    {
        SDL_Rect menuRect = {menuX, menuY, menuWidth, menuHeight};
        SDL_RenderCopy(renderer, menuTexture, nullptr, &menuRect);
    }
}

int PauseMenu::handlePauseInput(SDL_Event* event, int screenWidth, int screenHeight)
{
    if (event->type == SDL_MOUSEBUTTONDOWN)
    {
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Calculate positions for the "Continue" and "Menu" buttons
        int continueX = (screenWidth - continueWidth) / 2;
        int continueY = (screenHeight / 2) - continueHeight - 20;
        int menuX = (screenWidth - menuWidth) / 2;
        int menuY = (screenHeight / 2) + 20;

        // Check if "Continue" button is clicked
        if (mouseX >= continueX && mouseX <= continueX + continueWidth &&
                mouseY >= continueY && mouseY <= continueY + continueHeight)
        {
            return 1; // Continue
        }

        // Check if "Menu" button is clicked
        if (mouseX >= menuX && mouseX <= menuX + menuWidth &&
                mouseY >= menuY && mouseY <= menuY + menuHeight)
        {
            return 2; // Menu
        }
    }
    return 0; // No action
}

void PauseMenu::freeTextures()
{
    if (continueTexture != nullptr)
    {
        SDL_DestroyTexture(continueTexture);
        continueTexture = nullptr;
        continueWidth = 0;
        continueHeight = 0;
    }
    if (menuTexture != nullptr)
    {
        SDL_DestroyTexture(menuTexture);
        menuTexture = nullptr;
        menuWidth = 0;
        menuHeight = 0;
    }
}

int PauseMenu::getContinueButtonWidth()
{
    return continueWidth;
}
int PauseMenu::getContinueButtonHeight()
{
    return continueHeight;
}
int PauseMenu::getMenuButtonWidth()
{
    return menuWidth;
}
int PauseMenu::getMenuButtonHeight()
{
    return menuHeight;
}
