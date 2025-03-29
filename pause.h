#ifndef PAUSE_H
#define PAUSE_H

#include "CommonFunction.h"

class PauseButton {
public:
    PauseButton();
    ~PauseButton();

    bool loadButtonTexture(SDL_Renderer* renderer, const char* filePath);
    void renderButton(SDL_Renderer* renderer, int x, int y);
    bool handleEvent(SDL_Event* event, int x, int y, int buttonWidth, int buttonHeight);
    void freeButtonTexture();

    int getWidth();
    int getHeight();

private:
    SDL_Texture* buttonTexture;
    int width;
    int height;
};

class PauseMenu {
public:
    PauseMenu();
    ~PauseMenu();

    bool loadContinueTexture(SDL_Renderer* renderer, const char* filePath);
    bool loadMenuTexture(SDL_Renderer* renderer, const char* filePath);

    void renderPauseMenu(SDL_Renderer* renderer, int screenWidth, int screenHeight);
    int handlePauseInput(SDL_Event* event, int screenWidth, int screenHeight); // Returns 1 for continue, 2 for menu, 0 for no action

    void freeTextures();

    int getContinueButtonWidth();
    int getContinueButtonHeight();
    int getMenuButtonWidth();
    int getMenuButtonHeight();

private:
    SDL_Texture* continueTexture;
    SDL_Texture* menuTexture;

    int continueWidth;
    int continueHeight;
    int menuWidth;
    int menuHeight;
};


#endif
