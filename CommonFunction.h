#ifndef COMMONFUNCTION_H_INCLUDED
#define COMMONFUNCTION_H_INCLUDED
#include<windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>
#include<SDL_mixer.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int FRAME_PER_SECOND = 30; // fps so pham vi tren 1 giay
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 641;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 255;

extern TTF_Font* g_font;

#define BLANK_TYPE 0
#define MAP_SIZE 64 // size của mỗi ảnh ghép vào map
#define MAX_MAP_X 400 //max size ngang của map
#define MAX_MAP_Y 10 // max size dọc của map

#define STATE_MONEY 4
#define STATE_FLAG 5
typedef struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
    int jump_;
};

typedef struct Map
{
  int start_x; //vị trí cần xét
  int start_y;

  int map_x; // chỉ số của ô đấy
  int map_y;

  int  T[MAX_MAP_Y][MAX_MAP_X]; // lưu trạng thái của vị trí
  char* file_name;
};

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
}


#endif // COMMONFUNCTION_H_INCLUDED



// map_x = max_x_   mapx = map_x    map_x_ = map_x_
