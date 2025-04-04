#include<bits/stdc++.h>
#include "maincharacter.h"

Mainobject::Mainobject()
{
    frame_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    width_frame = 0;
    height_frame = 0;
    status_ = -1;
    input_type_.left_ = 0;
    input_type_.right_ = 0;
    input_type_.down_ = 0;
    input_type_.jump_ = 0;
    input_type_.up_ = 0;
    on_ground = false;
    map_x_ = 0;
    map_y_ = 0;
    comeback_time = 0;
    money_count = 0;
    flag_count = 0;
    is_respawning_ = false;
}

Mainobject::~Mainobject()
{

}

bool Mainobject::LoadImg(std::string path, SDL_Renderer* screen, int& stt)
{
    bool ret = Base::LoadImg(path, screen);
    if(ret == true && stt == 1)
    {
        width_frame = rect_.w/12;
        height_frame = rect_.h;
    }
    else if(ret == true && stt == 2)
    {
        width_frame = rect_.w/4;
        height_frame = rect_.h;
    }
    return ret;
}

SDL_Rect Mainobject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.w = width_frame;
    rect.h = height_frame;

    return rect;
}

void Mainobject::set_clips(int& stt)
{
    if(stt == 1)
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

            frame_clip[8].x = 8*width_frame;
            frame_clip[8].y = 0;
            frame_clip[8].w = width_frame;
            frame_clip[8].h = height_frame;

            frame_clip[9].x = 9*width_frame;
            frame_clip[9].y = 0;
            frame_clip[9].w = width_frame;
            frame_clip[9].h = height_frame;

            frame_clip[10].x = 10*width_frame;
            frame_clip[10].y = 0;
            frame_clip[10].w = width_frame;
            frame_clip[10].h = height_frame;

            frame_clip[11].x = 11*width_frame;
            frame_clip[11].y = 0;
            frame_clip[11].w = width_frame;
            frame_clip[11].h = height_frame;

        }
    }
    else if(stt == 2)
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
        }
    }
}

void Mainobject::increaseMoney()
{
    money_count++;
}
void Mainobject::increaseFlag()
{
    flag_count++;
}

void Mainobject::Show(SDL_Renderer* des, int& stt)
{
//    if(on_ground == true)
//    {
    if(stt == 1)
    {
        if(status_ == WALK_LEFT)
        {
            LoadImg("animation//left.png",des, stt);
        }
        else
        {
            LoadImg("animation//right.png",des, stt);
        }
    }
    else if(stt == 2)
    {
        if(status_ == WALK_LEFT)
        {
            LoadImg("animation//nhanvatleft.png",des, stt);
        }
        else
        {
            LoadImg("animation//nhanvatright.png",des, stt);
        }
    }

//    }
    if(input_type_.left_ == 1 || input_type_.right_ == 1)
    {
        frame_++;
    }
    else
    {
        frame_ = 0;
    }

    if(frame_ >= 12 && stt == 1)
    {
        frame_ = 0;
    }
    else if(frame_ >= 4 && stt == 2)
    {
        frame_ = 0;
    }
    // vị trí
    if(comeback_time == 0)
    {
        rect_.x = x_pos_ - map_x_;
        rect_.y = y_pos_ - map_y_;

        SDL_Rect* current_clip = &frame_clip[frame_];// frame hiện tại
        SDL_Rect renderquad = {rect_.x, rect_.y, width_frame, height_frame}; // kích thước
        SDL_RenderCopy(des, p_object_, current_clip, &renderquad); // đưa lên màn hình
    }

}

bool Mainobject::LoadSound()
{
    g_shoot_sound = Mix_LoadWAV("sound/fire1.wav");
    g_jump_sound = Mix_LoadWAV("sound/jump.wav");
    g_apple_sound = Mix_LoadWAV("sound/tao.wav");

    if (g_shoot_sound == NULL || g_jump_sound == NULL || g_apple_sound == NULL)
    {
        std::cout << "Failed to load sound! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }
    return true;
}

void Mainobject::HandelInputAction(SDL_Event events, SDL_Renderer* screen, int& stt)
{
    if(events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_RIGHT:
        {
            status_ = WALK_RIGHT;
            input_type_.right_ = 1;
            input_type_.left_ = 0;
        }
        break;
        case SDLK_LEFT:
        {
            status_ = WALK_LEFT;
            input_type_.left_ = 1;
            input_type_.right_ = 0;
        }
        break;
        case SDLK_UP:  // Xử lý khi nhấn phím Space để nhảy
        {
            input_type_.jump_ = 1;
            Mix_PlayChannel(-1, g_jump_sound, 0);
        }
        break;
        //tao vien dan
        case SDLK_SPACE:
        {
            BulletObject* p_bullet = new BulletObject();
            if(stt == 1)
            {
                p_bullet->set_bullet_type(BulletObject::Straight_bullet);
                if(status_ == WALK_LEFT)
                {
                    p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                    p_bullet->SetRect(this->rect_.x, rect_.y + height_frame *0.3);
                }
                else if(status_ == WALK_RIGHT)
                {
                    p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                    p_bullet->SetRect(this->rect_.x + width_frame - 20, rect_.y + height_frame *0.3);
                }
            }
            else if(stt == 2)
            {
                p_bullet->set_bullet_type(BulletObject::circle_bullet);
                if(status_ == WALK_LEFT)
                {
                    p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                    p_bullet->SetRect(this->rect_.x, rect_.y + height_frame *0.55);
                }
                else if(status_ == WALK_RIGHT)
                {
                    p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                    p_bullet->SetRect(this->rect_.x + width_frame - 20, rect_.y + height_frame *0.55);
                }
            }
            p_bullet->LoadImgBullet(screen);


            p_bullet->Set_x_val(20);
            p_bullet->set_is_move(true);

            p_bullet_list.push_back(p_bullet);

            // Thêm âm thanh bắn đạn
            Mix_PlayChannel(-1, g_shoot_sound, 0);
        }
        break;
        default:
            break;
        }
    }
    else if(events.type == SDL_KEYUP)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_RIGHT:
        {
            input_type_.right_ = 0;
        }
        break;
        case SDLK_LEFT:
        {
            input_type_.left_ = 0;
        }
        break;

        }
    }

//    if(events.type == SDL_MOUSEBUTTONDOWN)
//    {
//        if(events.button.button == SDL_BUTTON_RIGHT)
//        {
//            input_type_.jump_ = 1;
//        }
//    }

}


void Mainobject::HandleBullet(SDL_Renderer* des)
{
    for(int i = 0; i < p_bullet_list.size(); i++)
    {
        BulletObject* p_bullet = p_bullet_list.at(i);
        if(p_bullet != NULL)
        {
            if(p_bullet->get_is_move() == true)
            {
                int bullet_distance_left = rect_.x - p_bullet->GetRect().x + width_frame;
                int bullet_distance_right = p_bullet->GetRect().x - rect_.x + width_frame;

                if((bullet_distance_left > 0 && bullet_distance_left < 700) ||
                        (bullet_distance_right > 0 && bullet_distance_right < 700))
                {
                    p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
                    p_bullet->Render(des);
                }
                else
                {
                    p_bullet->set_is_move(false);
                }
            }
            else
            {
                p_bullet_list.erase(p_bullet_list.begin() + i);
                if(p_bullet != NULL)
                {
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}

void Mainobject::RemoveBullet(const int & idx)
{
    int size = p_bullet_list.size();
    if(size > 0 && idx < size)
    {
        BulletObject* p_bullet = p_bullet_list.at(idx);
        p_bullet_list.erase(p_bullet_list.begin() + idx);

        if(p_bullet)
        {
            delete p_bullet;
            p_bullet = NULL;
        }
    }
}

void Mainobject::Doplayer(Map& map_data, ImageIcon& icon_image)
{
    if(comeback_time == 0)
    {
        x_val_ = 0;
        y_val_ += GRAVITY_SPEED;

        if(y_val_ >= MAX_FALLSPEED)
        {
            y_val_ = MAX_FALLSPEED;
        }

        if(input_type_.left_ == 1)
        {
            x_val_ -= PLAYER_SPEED;
            status_ = WALK_LEFT;
        }
        else if(input_type_.right_ == 1)
        {
            x_val_ += PLAYER_SPEED;
            status_ = WALK_RIGHT;
        }

        if(input_type_.jump_ == 1)
        {
            if(on_ground == true)
            {
                y_val_ = -PLAYER_JUMP_VALUE;
            }
            on_ground = false;
            input_type_.jump_ = 0;
        }

        CheckMap(map_data, icon_image);
        EntityOnMap(map_data);
    }
    if(comeback_time > 0)
    {
        comeback_time--;
        if(comeback_time == 0)
        {
            on_ground = false;
            is_respawning_ = false;
            if(x_pos_ > 256)
            {
                x_pos_ -= 256; // 4 o type map
//                map_x_ -= 256;
            }
            else
            {
                x_pos_ = 0;
            }
            y_pos_ = 0;
            x_val_ = 0;
            y_val_ = 0;
        }
    }
}

void Mainobject::EntityOnMap(Map& map_data)
{
    map_data.start_x = x_pos_ - (SCREEN_WIDTH/2);
    if(map_data.start_x < 0)
    {
        map_data.start_x = 0;
    }
    else if(map_data.start_x + SCREEN_WIDTH >= map_data.map_x)
    {
        map_data.start_x = map_data.map_x - SCREEN_WIDTH;
    }
    map_data.start_y = y_pos_ - (SCREEN_HEIGHT/2);
    if(map_data.start_y < 0)
    {
        map_data.start_y = 0;
    }
    else if(map_data.start_y + SCREEN_HEIGHT >= map_data.map_y)
    {
        map_data.start_y = map_data.map_y - SCREEN_HEIGHT;
    }
}

void Mainobject::CheckMap(Map& map_data, ImageIcon& icon_image)
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

            if(val1 == STATE_MONEY || val2 == STATE_MONEY)
            {
                map_data.T[y1][x2] = 0;
                map_data.T[y2][x2] = 0;
                Mix_PlayChannel(-1, g_apple_sound, 0);
                increaseMoney();
            }
            else if(val1 == STATE_FLAG || val2 == STATE_FLAG)
            {
                map_data.T[y1][x2] = 0;
                map_data.T[y2][x2] = 0;
                increaseFlag();
            }
            else
            {
                if(val1 != BLANK_TYPE || val2 != BLANK_TYPE)
                {
                    x_pos_ = x2 * MAP_SIZE;
                    x_pos_ -= width_frame + 1;
                    x_val_ = 0;
                }
            }

        }
        if(x_val_ < 0)
        {
            int val1 = map_data.T[y1][x1];
            int val2 = map_data.T[y2][x1];

            if(val1 == STATE_MONEY || val2 == STATE_MONEY)
            {
                map_data.T[y1][x1] = 0;
                map_data.T[y2][x1] = 0;
                Mix_PlayChannel(-1, g_apple_sound, 0);
                increaseMoney();
            }
            else if(val1 == STATE_FLAG || val2 == STATE_FLAG)
            {
                map_data.T[y1][x1] = 0;
                map_data.T[y2][x1] = 0;
                increaseFlag();
            }
            else
            {
                if(val1 != BLANK_TYPE || val2 != BLANK_TYPE)
                {
                    x_pos_ = (x1 + 1)*MAP_SIZE;
                    x_val_ = 0;
                }
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
            if(val1 == STATE_MONEY || val2 == STATE_MONEY)
            {
                map_data.T[y2][x1] = 0;
                map_data.T[y2][x2] = 0;
                Mix_PlayChannel(-1, g_apple_sound, 0);
                increaseMoney();
            }
            else if(val1 == STATE_FLAG || val2 == STATE_FLAG)
            {
                map_data.T[y2][x1] = 0;
                map_data.T[y2][x2] = 0;
                increaseFlag();
            }
            else
            {
                if(val1 != BLANK_TYPE || val2 != BLANK_TYPE)
                {
                    y_pos_ = y2*MAP_SIZE;
                    y_pos_ -= (height_frame + 1);
                    y_val_ = 0;
                    on_ground = true;
                }
            }
        }
        else if(y_val_ < 0)
        {
            int val1 = map_data.T[y1][x1];
            int val2 = map_data.T[y1][x2];
            if(val1 == STATE_MONEY || val2 == STATE_MONEY)
            {
                map_data.T[y1][x1] = 0;
                map_data.T[y1][x2] = 0;
                Mix_PlayChannel(-1, g_apple_sound, 0);
                increaseMoney();
            }
            else if(val1 == STATE_FLAG || val2 == STATE_FLAG)
            {
                map_data.T[y1][x1] = 0;
                map_data.T[y1][x2] = 0;
                increaseFlag();
            }
            else
            {
                if(val1 != BLANK_TYPE || val2 != BLANK_TYPE)
                {
                    y_pos_ = (y1 + 1)*MAP_SIZE;
                    y_val_ = 0;
                }
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
        if (!is_respawning_)  // Chỉ trừ mạng nếu không phải đang hồi sinh
        {
            icon_image.Decrease(); // Trừ 1 mạng
        }

        is_respawning_ = true; // Đánh dấu đang hồi sinh
        comeback_time = 60;  // Đặt thời gian hồi sinh
    }
}



void Mainobject::FreeSound()
{
    Mix_FreeChunk(g_shoot_sound);
    Mix_FreeChunk(g_jump_sound);
    g_shoot_sound = NULL;
    g_jump_sound = NULL;
}

