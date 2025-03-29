#ifndef BULLETOBJECT_H_INCLUDED
#define BULLETOBJECT_H_INCLUDED

#include "CommonFunction.h"
#include "Base.h"

class BulletObject : public Base
{
public:
    BulletObject();
    ~BulletObject();

    enum BulletDir
    {
        DIR_RIGHT = 20,
        DIR_LEFT = 21,
        DIR_UP = 22,
        DIR_UP_LEFT = 23,
        DIR_UP_RIGHT = 24,
        DIR_DOWN_LEFT = 25,
        DIR_DOWN_RIGHT = 26,
    };
    enum BulletType
    {
        circle_bullet = 52,
        Straight_bullet = 50,
        Laze_bullet = 51,
    };

    void Set_x_val(const int& xVal) {x_val_ = xVal;}
    void Set_y_val(const int& yVal) {y_val_ = yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    void set_is_move(const bool& isMove) {is_move_ = isMove;}
    bool get_is_move()const {return is_move_;}

    void set_bullet_dir(const unsigned int& bulletDir) {bullet_dir = bulletDir;}
    unsigned int get_bullet_dir() const {return bullet_dir;}

    void set_bullet_type(const unsigned int& bulletType) {bullet_type = bulletType;}
    unsigned int get_bullet_type() const {return bullet_type;}

    void HandleMove(const int& x_border, const int& y_border);
    bool LoadImgBullet(SDL_Renderer* des);

private:
    int x_val_;
    int y_val_;
    bool is_move_;
    unsigned int bullet_dir;
    unsigned int bullet_type;
};


#endif // BULLETOBJECT_H_INCLUDED
