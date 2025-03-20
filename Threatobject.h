#ifndef THREATOBJECT_H_INCLUDED
#define THREATOBJECT_H_INCLUDED

#include "CommonFunction.h"
#include "Base.h"
#include "Bulletobject.h"

#define THREAT_FRAME_NUM 8
#define GRAVITY_SPEED 0.8
#define MAX_FALLSPEED 10
#define THREAT_SPEED 3

class ThreatsObject : public Base
{
public:
    ThreatsObject();
    ~ThreatsObject();

    enum TypeMove
    {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_THREAT = 1,
    };

    void set_x_val(const float& xval) {x_val_ = xval;}
    void set_y_val(const float& yval) {y_val_ = yval;}

    void set_x_pos(const float& xpos) {x_pos_ = xpos;}
    void set_y_pos(const float& ypos) {y_pos_ = ypos;}
    float get_x_pos() const {return x_pos_;}
    float get_y_pos() const {return y_pos_;}
    void SetMapXY(const int& mp_x, const int& mp_y) {map_x_ = mp_x; map_y_ = mp_y;}

    void Set_clips();
    bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    int get_width_frame() const {return width_frame;}
    int get_height_frame() const {return height_frame;}
    void Do_Player(Map& map_data);
    void ChecktoMap(Map& map_data);
    void InitThreat();

    void set_type_move(const int& typeMove) {type_move_ = typeMove;}
    void SetAnimationPos(const int& pos_a, const int& pos_b) {animation_a_ = pos_a; animation_b_ = pos_b;}
    void set_Input_left(const int& ipleft) {input_type_.left_ = ipleft;};
    void ImpMoveType(SDL_Renderer* screen);
    SDL_Rect GetRectFrame();

    std::vector<BulletObject*> get_bullet_list() const {return bullet_list_;}
    void set_bullet_list(const std::vector<BulletObject*>& bl_list) {bullet_list_ = bl_list;}

    void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
    void RemoveBullet(const int & idx, SDL_Renderer* screen);

private:

    int map_y_;
    int map_x_;
    float y_val_;
    float x_val_;
    float x_pos_;
    float y_pos_;
    bool on_ground;
    int come_back_time;
    SDL_Rect frame_clip[THREAT_FRAME_NUM];
    int width_frame;
    int height_frame;
    int frame_;

    int type_move_;
    int animation_a_;
    int animation_b_;
    Input input_type_;

    std::vector<BulletObject*>bullet_list_;


};


#endif // THREATOBJECT_H_INCLUDED
