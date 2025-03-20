#include<bits/stdc++.h>
#include "Threatobject.h"

ThreatsObject::ThreatsObject()
{
    width_frame = 0;
    height_frame = 0;
    x_val_ = 0.0;
    y_val_ = 0.0;
    x_pos_ = 0.0;
    y_pos_ = 0.0;
    on_ground = 0;
    come_back_time = 0;
    frame_ = 0;

    animation_a_ = 0;
    animation_b_ = 0;
    input_type_.left_ = 0;
    type_move_ = STATIC_THREAT;
}

ThreatsObject::~ThreatsObject()
{

}

bool ThreatsObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = Base::LoadImg(path, screen);
    if(ret)
    {
        width_frame = rect_.w/THREAT_FRAME_NUM;
        height_frame = rect_.h;
    }
    return ret;
}

SDL_Rect ThreatsObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame;
    rect.h = height_frame;

    return rect;
}

void ThreatsObject::Set_clips()
{
    if(width_frame > 0 && height_frame > 0)
    {
        frame_clip[0].x = 0;
        frame_clip[0].y = 0;
        frame_clip[0].w = width_frame;
        frame_clip[0].h = height_frame;

        frame_clip[1].x = width_frame;
        frame_clip[1].y = 0;
        frame_clip[1].w = width_frame;
        frame_clip[1].h = height_frame;

        frame_clip[2].x = 2*width_frame;
        frame_clip[2].y = 0;
        frame_clip[2].w = width_frame;
        frame_clip[2].h = height_frame;

        frame_clip[3].x = 3*width_frame;
        frame_clip[3].y = 0;
        frame_clip[3].w = width_frame;
        frame_clip[3].h = height_frame;

        frame_clip[4].x = 4*width_frame;
        frame_clip[4].y = 0;
        frame_clip[4].w = width_frame;
        frame_clip[4].h = height_frame;

        frame_clip[5].x = 5*width_frame;
        frame_clip[5].y = 0;
        frame_clip[5].w = width_frame;
        frame_clip[5].h = height_frame;

        frame_clip[6].x = 6*width_frame;
        frame_clip[6].y = 0;
        frame_clip[6].w = width_frame;
        frame_clip[6].h = height_frame;

        frame_clip[7].x = 7*width_frame;
        frame_clip[7].y = 0;
        frame_clip[7].w = width_frame;
        frame_clip[7].h = height_frame;
    }
}

void ThreatsObject::Show(SDL_Renderer* des)
{
    if(come_back_time == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;
        frame_++;
        if(frame_ >= 8)
        {
            frame_ = 0;
        }

        SDL_Rect* current_clip = &frame_clip[frame_];// frame hiện tại
        SDL_Rect rendquad = {rect_.x, rect_.y, width_frame, height_frame}; // kích thước
        SDL_RenderCopy(des, p_object_, current_clip, &rendquad); // đưa lên màn hình
    }

}

void ThreatsObject::Do_Player(Map& map_data)
{
    if(come_back_time == 0)
    {
        x_val_ = 0;
        y_val_ += GRAVITY_SPEED;
        if(y_val_ >= MAX_FALLSPEED)
        {
            y_val_ = MAX_FALLSPEED;
        }

        if(input_type_.left_ == 1)
        {
            x_val_ -= THREAT_SPEED;
        }
        else if(input_type_.right_ == 1)
        {
            x_val_ += THREAT_SPEED;
        }

        ChecktoMap(map_data);
    }
    else if(come_back_time > 0)
    {
        come_back_time--;
        if(come_back_time == 0)
        {
            InitThreat();
        }
    }
}

void ThreatsObject::InitThreat()
{
    x_val_ = 0;
    y_val_ = 0;
    if(x_pos_ > 256)
    {
        x_pos_ -= 256;
        animation_a_ -= 256;
        animation_b_ -= 256;
    }
    else
    {
        x_pos_ = 0;
    }
    y_pos_ = 0;
    come_back_time = 0;
    input_type_.left_ = 1;
}

void ThreatsObject::RemoveBullet(const int & idx)
{
    int size = bullet_list_.size();
    if(size > 0 && idx < size)
    {
        BulletObject* p_bullet = bullet_list_.at(idx);
        bullet_list_.erase(bullet_list_.begin() + idx);

        if(p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}


void ThreatsObject::ChecktoMap(Map& map_data)
{
    int x1 = 0;// giới hạn ktra theo chiều x
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;

    // check theo chiều x
    int height_min = height_frame < MAP_SIZE ? height_frame : MAP_SIZE;

    x1 = (x_pos_ + x_val_)/ MAP_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame - 1) / MAP_SIZE;

    y1 = (y_pos_) / MAP_SIZE;
    y2 = (y_pos_ + height_min - 1) / MAP_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(x_val_ > 0) // nvat đi về bên phải
        {

            int val1 = map_data.T[y1][x2];
            int val2 = map_data.T[y2][x2];
            if((val1 != BLANK_TYPE && val1 != STATE_MONEY) || (val2 != BLANK_TYPE && val2 != STATE_MONEY))
            {
                x_pos_ = x2 * MAP_SIZE;
                x_pos_ -= width_frame + 1;
                x_val_ = 0;
            }

        }
        if(x_val_ < 0)
        {
            int val1 = map_data.T[y1][x1];
            int val2 = map_data.T[y2][x1];
            if((val1 != BLANK_TYPE && val1 != STATE_MONEY)|| (val2 != BLANK_TYPE &&val2 != STATE_MONEY))
            {
                x_pos_ = (x1 + 1)*MAP_SIZE;
                x_val_ = 0;
            }
        }
    }
    // check chiều y

    int width_min = width_frame < MAP_SIZE ? width_frame : MAP_SIZE;
    x1 = (x_pos_)/MAP_SIZE;
    x2 = (x_pos_ +width_min)/MAP_SIZE;

    y1 = (y_pos_ +y_val_)/MAP_SIZE;
    y2 = (y_pos_ + y_val_ +height_frame-1)/MAP_SIZE;

    if(x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
    {
        if(y_val_ > 0)
        {
            int val1 = map_data.T[y2][x1];
            int val2 = map_data.T[y2][x2];

            if((val1 != BLANK_TYPE && val1 != STATE_MONEY)|| (val2 != BLANK_TYPE &&val2 != STATE_MONEY))
            {
                y_pos_ = y2*MAP_SIZE;
                y_pos_ -= (height_frame + 1);
                y_val_ = 0;
                on_ground = true;
            }
        }
        else if(y_val_ < 0)
        {
            int val1 = map_data.T[y1][x1];
            int val2 = map_data.T[y1][x2];

            if((val1 != BLANK_TYPE && val1 != STATE_MONEY)|| (val2 != BLANK_TYPE &&val2 != STATE_MONEY))
            {
                y_pos_ = (y1 + 1)*MAP_SIZE;
                y_val_ = 0;
            }
        }
    }
    x_pos_ += x_val_;
    y_pos_ += y_val_;
    if(x_pos_ < 0)
    {
        x_pos_ = 0;
    }
    else if(x_pos_ + width_frame > map_data.map_x)
    {
        x_pos_ = map_data.map_x - width_frame -1;
    }
    if(y_pos_ > map_data.map_y)
    {
        come_back_time = 60;
    }
}

void ThreatsObject::ImpMoveType(SDL_Renderer* screen)
{
    if(type_move_ == STATIC_THREAT)
    {
        ;
    }
    else
    {
        if(on_ground == true)
        {
            if(x_pos_ > animation_b_)
            {
                input_type_.left_ = 1;
                input_type_.right_ = 0;
                LoadImg("animation//skeletonleft.png", screen);
            }
            else if(x_pos_ < animation_a_)
            {
                input_type_.right_ = 1;
                input_type_.left_ = 0;
                LoadImg("animation//skeletonright.png", screen);
            }
        }
        else
        {
            if(input_type_.left_ == 1)
            {
                LoadImg("animation//skeletonleft.png", screen);

            }
        }
    }
}

void ThreatsObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen)
{
    if(p_bullet != NULL)
    {
        p_bullet->set_bullet_type(BulletObject::Laze_bullet);
        bool ret = p_bullet->LoadImgBullet(screen);
        if(ret)
        {
            p_bullet->set_is_move(true);
            p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
            p_bullet->SetRect(x_pos_+30, y_pos_+30);
            p_bullet->Set_x_val(15);
            bullet_list_.push_back(p_bullet);
        }
    }
}

void ThreatsObject::MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit)
{
    for(int i = 0; i < bullet_list_.size(); i++)
    {
        BulletObject* p_bullet = bullet_list_.at(i);
        if(p_bullet != NULL)
        {
            if(p_bullet->get_is_move())
            {
                int bullet_distance = x_pos_ + width_frame - p_bullet->GetRect().x;
                if(bullet_distance < 400 && bullet_distance > 0)
                {
                    p_bullet->HandleMove(x_limit, y_limit);
                    p_bullet->Render(screen);
                }
                else
                {
                    p_bullet->set_is_move(false);
                }

            }
            else
            {
                p_bullet->set_is_move(true);
                p_bullet->SetRect(x_pos_ +30, y_pos_+30);
            }
        }
    }
}
