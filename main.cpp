#include <bits/stdc++.h>
#include<windows.h>
#include <tchar.h>
#include "CommonFunction.h"
#include "Base.h"
#include "game_map.h"
#include "menu.h"
#include "maincharacter.h"
#include "Timer.h"
#include "Threatobject.h"
#include "Exobject.h"
#include "TextObject.h"
#include "image_icon.h"
using namespace std;

Base g_background;
TTF_Font* font_time = NULL;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if(ret < 0)
    {
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");

    g_window = SDL_CreateWindow("NDTD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags))
            {
                success = false;
            }
        }
        if(TTF_Init() == -1)
        {
            success = false;
        }

        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
            success = false;
        }

        font_time = TTF_OpenFont("font//dlxfont_.ttf", 15);
        if(font_time == NULL)
        {
            success = false;
        }
    }
    return success;
}
int stt = 0;
bool LoadBackground()
{
    if(stt == 1)
    {
        bool ret = g_background.LoadImg("animation/bautroi.png", g_screen);
        if(ret == false)
            return false;
    }
    else if(stt == 2)
    {
        bool ret = g_background.LoadImg("animation/background.png", g_screen);
        if(ret == false)
            return false;
    }


    return true;
}

void close()
{
    g_background.Free();
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;


    IMG_Quit();
    SDL_Quit();
}

std::vector<ThreatsObject*> MakeThreatList()
{
    std::vector<ThreatsObject*>list_threats;

    ThreatsObject* dynamic_threats = new ThreatsObject[30];

    for(int i = 0; i < 30; i++)
    {
        ThreatsObject* p_threat = (dynamic_threats + i);
        if(p_threat != NULL)
        {
            p_threat->LoadImg("animation/skeletonleft.png", g_screen);
            p_threat->Set_clips();
            p_threat->set_type_move(ThreatsObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(800+i*800);
            p_threat->set_y_pos(200);

            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_x_pos() + 60;
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_Input_left(1);

            list_threats.push_back(p_threat);
        }
    }

    ThreatsObject* threats_objs = new ThreatsObject[10];

    for(int i = 0 ; i < 10; i++)
    {
        ThreatsObject* p_threat = (threats_objs + i);
        if(p_threat != NULL)
        {
            p_threat->LoadImg("animation/kedich1left.png", g_screen);
            p_threat->Set_clips();
            p_threat->set_x_pos(700 + i*1200);
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatsObject::STATIC_THREAT);
            p_threat->set_Input_left(0);

            BulletObject* p_bullet = new BulletObject();
            p_threat->InitBullet(p_bullet, g_screen);
            list_threats.push_back(p_threat);
        }
    }

    return list_threats;
}
void gameOverAndExit()
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Info", "GAME OVER", NULL);
    SDL_Quit();
    exit(0);
}



int main(int argc, char *argv[])
{
    Timer fps_time;
    stt++;
    Mix_Music* g_background_music = NULL;
    Mix_Chunk* g_hit_sound = NULL;


    if(InitData() == false)
        return -1;

    g_background_music = Mix_LoadMUS("sound/amthanhnen.mp3");
    g_hit_sound = Mix_LoadWAV("sound/Explosion+1.wav");

    if (g_background_music == NULL || g_hit_sound == NULL)
    {
        cout << "Failed to load sound! SDL_mixer Error: " << Mix_GetError() << endl;
        return -1;
    }

    if(LoadBackground() == false)
        return -1;

    //chay menu

    GameMap game_map;
    Mainobject player_;
    if(stt == 1)
    {
//        cout << stt;

        Menu menu;
        if (!menu.loadFont("font//ARIAL.ttf", 60))   // Tăng cỡ chữ
        {
            cout << "Failed to load font!\n";
            return -1;
        }



        if (!menu.loadBackground("animation/background1.png", g_screen))   // Load background cho menu
        {
            cout << "Failed to load menu background!\n";
            return -1;
        }
        int menuChoice = menu.showMenu(g_screen);
        if (menuChoice == 1)
        {
            close();
            return 0;  // Người dùng chọn thoát
        }
        game_map.LoadMap("map/map02.dat");
        game_map.LoadTiles(g_screen);
        player_.LoadImg("animation//right.png", g_screen, stt);
        player_.set_clips(stt);
    }
    else if(stt == 2)
    {
        game_map.LoadMap("map/map01.dat");
        game_map.LoadTiles(g_screen);
        player_.LoadImg("animation//nhanvatright.png", g_screen, stt);
//        int x = stt-1;
        player_.set_clips(stt);
    }



    // chay nhan vat

    if (!player_.LoadSound())
    {
        return -1;
    }

    ImageIcon icon_image;
    icon_image.Init(g_screen);

    Appleicon apple_icon;
    apple_icon.Init(g_screen);
    apple_icon.SetPos(SCREEN_WIDTH*0.5-295,5);



    std::vector<ThreatsObject*> threats_list = MakeThreatList();

    ExplosionObject exp_threat;
    bool tRet = exp_threat.LoadImg("animation//exp3.png", g_screen);
    if(!tRet) return -1;
    exp_threat.set_clips();



    ExplosionObject exp_main;
    bool mRet = exp_main.LoadImg("animation//exp3.png", g_screen);
    if(!mRet) return -1;
    exp_main.set_clips();

    // chỉ số thời gian

    TextObject time_game;
    time_game.SetColor(TextObject::WHITE_TEXT);

    TextObject score_game;
    score_game.SetColor(TextObject::WHITE_TEXT);
    UINT score_value = 0;

    TextObject apple_game;
    apple_game.SetColor(TextObject::WHITE_TEXT);

    if (Mix_PlayingMusic() == 0)
    {
        Mix_PlayMusic(g_background_music, -1); // Phát nhạc nền lặp vô hạn
    }

    bool is_quit = false;
    while(!is_quit)
    {
        fps_time.start();
        while(SDL_PollEvent(&g_event) != 0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            player_.HandelInputAction(g_event, g_screen, stt);
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        Map map_data = game_map.getMap();


        player_.HandleBullet(g_screen);
        player_.SetMapXY(map_data.start_x, map_data.start_y);
        player_.Doplayer(map_data, icon_image);

        player_.Show(g_screen, stt);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        icon_image.Show(g_screen);
        apple_icon.Show(g_screen);

        for(int  i = 0; i < threats_list.size(); i++)
        {
            ThreatsObject* p_threat = threats_list.at(i);
            if(p_threat != NULL)
            {
                p_threat->SetMapXY(map_data.start_x, map_data.start_y);
                p_threat->ImpMoveType(g_screen);
                p_threat->Do_Player(map_data);
                p_threat->MakeBullet(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
                p_threat->Show(g_screen);


                SDL_Rect rect_player = player_.GetRectFrame();
                bool bCol1 = false;
                std::vector<BulletObject*> tBullet_list = p_threat->get_bullet_list();
                for (int jj = 0; jj < tBullet_list.size(); ++jj)
                {
                    BulletObject* pt_bullet = tBullet_list.at(jj);
                    if (pt_bullet)
                    {
                        bCol1 = SDLCommonFunc::CheckCollision(pt_bullet->GetRect(), rect_player);
                        if (bCol1 == true)
                        {
                            p_threat->RemoveBullet(jj, g_screen);
                            break;
                        }
                    }
                }

                SDL_Rect rect_threat = p_threat->GetRectFrame();
                bool bCol2 = SDLCommonFunc::CheckCollision(rect_player, rect_threat);
                if(bCol1  == true|| bCol2 == true)
                {
                    int width_exp_frame = exp_main.get_frame_height();
                    int height_exp_frame = exp_main.get_frame_height();
                    for(int ex = 0; ex < 4; ex++)
                    {
                        int x_pos = (player_.GetRect().x +player_.get_frame_width()*0.5) - width_exp_frame*0.5;
                        int y_pos = (player_.GetRect().y +player_.get_frame_height()*0.5) - height_exp_frame*0.5;

                        exp_main.set_frame(ex);
                        exp_main.SetRect(x_pos, y_pos);
                        exp_main.Show(g_screen);
                        SDL_RenderPresent(g_screen);
                    }
                    num_die++;
                    Mix_PlayChannel(-1, g_hit_sound, 0);
                    if(num_die <= 3)
                    {
                        player_.SetRect(0,0);
                        player_.set_comeback_time(60);
                        SDL_Delay(800);
                        icon_image.Decrease();
                        icon_image.Render(g_screen);
                        continue;
                    }
                    else
                    {
                        p_threat->Free();
                        close();
                        gameOverAndExit();
                    }

                }

            }
        }

        int solanchet = 0;
        int frame_exp_width = exp_threat.get_frame_width();
        int frame_exp_height = exp_threat.get_frame_height();
        std::vector<BulletObject*>bullet_arr = player_.get_bullet_list();
        for(int i = 0; i < bullet_arr.size(); i++)
        {
            BulletObject* p_bullet = bullet_arr.at(i);
            if(p_bullet != NULL)
            {
                for(int t = 0; t < threats_list.size(); t++)
                {
                    ThreatsObject* obj_threat = threats_list.at(t);
                    if(obj_threat != NULL)
                    {
                        SDL_Rect trect;
                        trect.x = obj_threat->GetRect().x;
                        trect.y = obj_threat->GetRect().y;
                        trect.w = obj_threat->get_width_frame();
                        trect.h = obj_threat->get_height_frame();

                        SDL_Rect bRect = p_bullet->GetRect();

                        bool bCol = SDLCommonFunc::CheckCollision(bRect, trect);
                        if(bCol && stt == 1)
                        {
                            Mix_PlayChannel(-1, g_hit_sound, 0);
                            score_value++;
                            for(int j = 0; j < 8; j++)
                            {
                                int x_pos = p_bullet->GetRect().x - frame_exp_height * 0.5;
                                int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;

                                exp_threat.set_frame(j);
                                exp_threat.SetRect(x_pos, y_pos);
                                exp_threat.Show(g_screen);
                            }

                            player_.RemoveBullet(i);
                            obj_threat->Free();
                            threats_list.erase(threats_list.begin() + t);
                        }
                        else if(bCol && stt == 2)
                        {
//                            if(solanchet == 0)
//                            {
//                                solanchet++;
//                                player_.RemoveBullet(i);
//                                break;
//                            }
                            Mix_PlayChannel(-1, g_hit_sound, 0);
                            score_value++;
                            for(int j = 0; j < 8; j++)
                            {
                                int x_pos = p_bullet->GetRect().x - frame_exp_height * 0.5;
                                int y_pos = p_bullet->GetRect().y - frame_exp_height * 0.5;

                                exp_threat.set_frame(j);
                                exp_threat.SetRect(x_pos, y_pos);
                                exp_threat.Show(g_screen);
                            }

                            player_.RemoveBullet(i);
                            obj_threat->Free();
                            threats_list.erase(threats_list.begin() + t);
//                            solanchet = 0;
                        }
                    }
                }
            }
        }

        //in thời gian
        std::string str_time = "Time: ";
        Uint32 time_val = SDL_GetTicks() / 1000;
        Uint32 val_time = 250 - time_val;
        if(val_time <= 0)
        {
            close();
            gameOverAndExit();
        }
        else
        {
            std::string str_val = std::to_string(val_time);
            str_time += str_val;

            time_game.SetText(str_time);
            time_game.LoadFromRenderText(font_time, g_screen);
            time_game.RenderText(g_screen, SCREEN_WIDTH-200, 15);
        }
        // in diem
        std::string val_str_score = std::to_string(score_value);
        std::string str_score("Score: ");
        str_score += val_str_score;
        score_game.SetText(str_score);
        score_game.LoadFromRenderText(font_time, g_screen);
        score_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 50, 15);
        // in tao
        int apple_count = player_.Getapplecount();
        std::string apple_str = std::to_string(apple_count);
        apple_game.SetText(apple_str);
        apple_game.LoadFromRenderText(font_time, g_screen);
        apple_game.RenderText(g_screen, SCREEN_WIDTH*0.5 - 250, 15);

        SDL_RenderPresent(g_screen);

        int real_time = fps_time.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND;

        if(real_time < time_one_frame)
        {
            int delay_time = time_one_frame - real_time;
            if(delay_time >= 0)
                SDL_Delay(delay_time);
        }




        int flag_count = player_.Getflagcount();
        if (flag_count != 0) // Khi nhân vật đến cuối map
        {
            if(stt == 2) stt = 0;
            if(stt == 1)
            {
                TextObject win_text;
                win_text.SetColor(TextObject::RED_TEXT);
                font_time = TTF_OpenFont("font//dlxfont_.ttf", 30);
                win_text.SetText("YOU CONTINUE TO PART 2");
                win_text.LoadFromRenderText(font_time, g_screen);

                SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 255);
                SDL_RenderClear(g_screen);
                g_background.Render(g_screen, NULL);
                win_text.RenderText(g_screen, SCREEN_WIDTH / 2 - 350, SCREEN_HEIGHT / 2 - 25);
                SDL_RenderPresent(g_screen);
                Mix_PauseMusic();
                SDL_Delay(2000);
                IMG_Quit();
                TTF_Quit();
                if (!player_.LoadSound())
                {
                    return -1;
                }
                g_background_music = Mix_LoadMUS("sound/amthanhnen.mp3");
                g_hit_sound = Mix_LoadWAV("sound/Explosion+1.wav");
                if (g_background_music == NULL || g_hit_sound == NULL)
                {
                    cout << "Failed to reload sound! SDL_mixer Error: " << Mix_GetError() << endl;
                    return -1;
                }

                Mix_ResumeMusic();  // Tiếp tục phát nhạc nền
                main(argc, argv); // Quay lại menu
            }
            // Tải ảnh chiến thắng
            Base win_image;
            if (!win_image.LoadImg("animation/win_screen.png", g_screen))
            {
                cout << "Failed to load win image!" << endl;
            }

            // Hiển thị ảnh chiến thắng
            SDL_SetRenderDrawColor(g_screen, 0, 0, 0, 255);
            SDL_RenderClear(g_screen);
            win_image.Render(g_screen, NULL);
            SDL_RenderPresent(g_screen);

            Mix_PauseMusic();
            SDL_Delay(2000);
            IMG_Quit();
            TTF_Quit();
            if (!player_.LoadSound())
            {
                return -1;
            }
            g_background_music = Mix_LoadMUS("sound/amthanhnen.mp3");
            g_hit_sound = Mix_LoadWAV("sound/Explosion+1.wav");
            if (g_background_music == NULL || g_hit_sound == NULL)
            {
                cout << "Failed to reload sound! SDL_mixer Error: " << Mix_GetError() << endl;
                return -1;
            }

            Mix_ResumeMusic();  // Tiếp tục phát nhạc nền
            main(argc, argv); // Quay lại menu
            return 0;
        }
    }

    for(int i = 0; i < threats_list.size(); i++)
    {
        ThreatsObject* p_threat = threats_list.at(i);
        if(p_threat)
        {
            p_threat->Free();
            p_threat = NULL;
        }
    }
    player_.FreeSound();
    threats_list.clear();
    Mix_FreeMusic(g_background_music);
    Mix_FreeChunk(g_hit_sound);
    g_background_music = NULL;
    g_hit_sound = NULL;
    player_.FreeSound();
    Mix_Quit();
    close();
    return 0;
}
