#ifndef IMAGE_ICON_H_INCLUDED
#define IMAGE_ICON_H_INCLUDED

#include "CommonFunction.h"
#include "Base.h"

class ImageIcon : public Base
{
public:
    ImageIcon();
    ~ImageIcon();

    void SetNum(const int& num) {number_ = num;}
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);
    void InitCrease();
    void Decrease();
    int GetMaxLives() const { return max_lives; }

private:
    int number_;
    std::vector<int> pos_list;//vi tri them chi so mang
    int max_lives;

};

class Appleicon: public Base
{
public:
    Appleicon();
    ~Appleicon();

    void Init(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetPos(const int& x, const int & y) {x_pos = x, y_pos = y;}

private:
    int x_pos;
    int y_pos;

};

#endif // IMAGE_ICON_H_INCLUDED
