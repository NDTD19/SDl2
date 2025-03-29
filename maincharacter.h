#ifndef MAINCHARACTER_H_INCLUDED
#define MAINCHARACTER_H_INCLUDED

#include<vector>

#include "CommonFunction.h"
#include "Base.h"
#include "Bulletobject.h"
#include "image_icon.h"
#include "game_map.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALLSPEED 10
#define PLAYER_SPEED 9
#define PLAYER_JUMP_VALUE 19;

class Mainobject : public Base
{
public:
    Mainobject();
    ~Mainobject();

    enum WalkType
    {
        WALK_RIGHT = 0,
        WALK_LEFT = 1,
    };

    bool LoadImg(std::string path, SDL_Renderer* screen, int& stt);
    void Show(SDL_Renderer* des, int& stt);
    void HandelInputAction(SDL_Event events, SDL_Renderer* screen, int& stt);
    void set_clips(int& stt); // xử lý hình ảnh cho frame

    void Doplayer(Map& map_data, ImageIcon& icon_image); //check giới hạn bản đồ kiểm tra va chạm
    void CheckMap(Map& map_data, ImageIcon& icon_image); // check nó rơi xuống chạm vào map
    void SetMapXY(const int mapx, const int mapy) { map_x_ = mapx; map_y_ = mapy; }
    void EntityOnMap(Map& map_data);

    SDL_Rect GetRectFrame();

    void set_bullet_list(std::vector<BulletObject*> bullet_list)
    {
        p_bullet_list = bullet_list;
    }
    std::vector<BulletObject*> get_bullet_list() const {return p_bullet_list;}
    void HandleBullet(SDL_Renderer* des);
    void RemoveBullet(const int & idx);
    void increaseMoney();
    void increaseFlag();
    int get_frame_width()const {return width_frame;}
    int get_frame_height() const {return height_frame;}
    void set_comeback_time(const int& cb_time) {comeback_time = cb_time;}
    int Getapplecount()const {return money_count;}
    int Getflagcount()const {return flag_count;}

    bool LoadSound();  // Hàm load âm thanh
    void FreeSound();  // Hàm giải phóng âm thanh

private:

    int money_count;
    int flag_count;
    std::vector<BulletObject*> p_bullet_list;
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame;
    int height_frame;

    SDL_Rect frame_clip[12]; // lưu frame;

    Input input_type_;
    int frame_; // chỉ số của frame;
    int status_; //lưu trạng thái di chuyển;
    bool on_ground;
    int map_x_;
    int map_y_;

    int comeback_time;
    bool is_respawning_;
    Mix_Chunk* g_shoot_sound = NULL;
    Mix_Chunk* g_jump_sound = NULL;
    Mix_Chunk* g_apple_sound = NULL;
};


#endif // MAINCHARACTER_H_INCLUDED
