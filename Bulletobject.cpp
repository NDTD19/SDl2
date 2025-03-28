#include<bits/stdc++.h>
#include "Bulletobject.h"

BulletObject::BulletObject()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
    bullet_type = Straight_bullet;
}

BulletObject::~BulletObject()
{

}

bool BulletObject::LoadImgBullet(SDL_Renderer* des)
{
    bool ret = false;
    if(bullet_type == Straight_bullet)
    {
        ret = LoadImg("animation//bullet.png", des);
    }
    else if(bullet_type == Laze_bullet)
    {
        ret = LoadImg("animation//bullet1.png", des);
    }
    else if(bullet_type == circle_bullet)
    {
        ret = LoadImg("animation//bullet2.png", des);
    }

    return ret;
}

void BulletObject::HandleMove(const int& x_border, const int& y_border)
{
    if(bullet_dir == DIR_RIGHT)
    {
        rect_.x += x_val_;
        if(rect_.x > x_border)
        {
            is_move_ = false;
        }
    }
    else if(bullet_dir == DIR_LEFT)
    {
        rect_.x -= x_val_;
        if(rect_.x < 0)
        {
            is_move_ = false;
        }
    }
    else if(bullet_dir == DIR_UP)
    {
        rect_.y -= y_val_;
        if(rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if(bullet_dir == DIR_UP_LEFT)
    {
        rect_.x -= x_val_;
        if(rect_.x < 0)
        {
            is_move_ = false;
        }
        rect_.y -= y_val_;
        if(rect_.y < 0)
        {
            is_move_ = false;
        }
    }
    else if(bullet_dir == DIR_UP_RIGHT)
    {
        rect_.x += x_val_;
        if(rect_.x > x_border)
        {
            is_move_ = false;
        }
        rect_.y -= y_val_;
        if(rect_.y < 0)
        {
            is_move_ = false;
        }
    }

}
