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

private:
    int number_;
    std::vector<int> pos_list;//vi tri them chi so mang


};

#endif // IMAGE_ICON_H_INCLUDED
