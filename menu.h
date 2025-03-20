#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "CommonFunction.h"
#include "Base.h"

class Menu {
public:
    Menu();
    ~Menu();

    bool loadFont(const std::string& font_path, int font_size);
    bool loadBackground(const std::string& path, SDL_Renderer* screen);
    int showMenu(SDL_Renderer* screen);

    TTF_Font* getFont() const { return font; }

private:
    TTF_Font* font;
    Base background;
    void renderText(SDL_Renderer* screen, const std::string& text, int x, int y, SDL_Color color);
};

#endif // MENU_H_INCLUDED
