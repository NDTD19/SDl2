#include <bits/stdc++.h>
#include "image_icon.h"

ImageIcon::ImageIcon()
{
    number_ = 0;
    max_lives = 3;
}

ImageIcon::~ImageIcon()
{

}

void ImageIcon::AddPos(const int& xPos)
{
    pos_list.push_back(xPos);
}

void ImageIcon::Init(SDL_Renderer* screen)
{
    bool ret = LoadImg("animation/icon.png", screen);
    if(ret == NULL)
    {
        printf("ko chay dc");
    }
    number_ = 3;
    if(pos_list.size() > 0)
    {
        pos_list.clear();
    }
    AddPos(20);
    AddPos(60);
    AddPos(100);
}

void ImageIcon::Show(SDL_Renderer* screen)
{
    for(int i = 0; i < pos_list.size(); i++)
    {
        rect_.x = pos_list.at(i);
        rect_.y = 0;
        Render(screen);
    }
}

void ImageIcon::Decrease()
{
    number_--;
    pos_list.pop_back();
}

void ImageIcon::InitCrease()
{
    number_++;
    int last_pos = pos_list.back();
    last_pos += 40;
    pos_list.push_back(last_pos);
}

Appleicon::Appleicon()
{
    x_pos = 0;
    y_pos = 0;
}

Appleicon::~Appleicon()
{

}

void Appleicon::Init(SDL_Renderer* screen)
{
    bool ret = LoadImg("animation/tao.png", screen);
}

void Appleicon::Show(SDL_Renderer* screen)
{
    rect_.x = x_pos;
    rect_.y = y_pos;
    Render(screen);
}

