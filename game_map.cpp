#include <bits/stdc++.h>
#include "game_map.h"
// đọc dữ liệu từ file bản đồ bên ngoài
void GameMap::LoadMap(char* name)
{
    FILE* fp = NULL;
    fopen_s(&fp, name, "rb"); // rb là chế độ để đọc file
    if(fp == NULL)
    {
        return;
    }

    game_map.map_x = 0;
    game_map.map_y = 0;

    for(int i = 0; i < MAX_MAP_Y; i++)
    {
        for(int j = 0; j < MAX_MAP_X; j++)
        {
            fscanf(fp, "%d", &game_map.T[i][j]);
            int val = game_map.T[i][j];
            if(val > 0)
            {
                if(j > game_map.map_x)
                {
                    game_map.map_x = j;
                }
                if(i > game_map.map_y)
                {
                    game_map.map_y = i;
                }
            }
        }
    }
    game_map.map_x =(game_map.map_x + 1) * MAP_SIZE; // nhân với kích cỡ của ảnh được giá trị tối đa của map
    game_map.map_y =(game_map.map_y + 1) * MAP_SIZE;

    game_map.start_x = 0;
    game_map.start_y = 0;

    game_map.file_name = name;
    fclose(fp);
}
// load các image của những ảnh tương ứng
void GameMap::LoadTiles(SDL_Renderer* screen)
{
    char file_img[30];
    FILE* fp = NULL;

    for(int i = 0; i < MAX_TILE; i++)
    {
        sprintf_s(file_img, "map/%d.png", i);// chuyển các số 0 1 2 3 thành các ảnh tương ứng trong file

        fopen_s(&fp, file_img, "rb");
        if(fp == NULL)
        {
            continue;
        }

        fclose(fp);

        // load ảnh
        tile_map[i].LoadImg(file_img, screen);
    }
}
//đưa các ảnh vào các ô tương ứng
void GameMap::DrawMap(SDL_Renderer* screen)
{
    // vị trí để đưa ảnh vào thành 1 hình lập phương
    int x1 = 0;
    int x2 = 0;

    int y1 = 0;
    int y2 = 0;
    // đưa ảnh vào đúng 1 khung bản đồ background có sẵn

    int mp_x = 0;
    int mp_y = 0;

    mp_x = game_map.start_x/MAP_SIZE;
    x1 = (game_map.start_x%MAP_SIZE)*-1;
    x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : MAP_SIZE);

    mp_y = game_map.start_y/MAP_SIZE;
    y1 = (game_map.start_y%MAP_SIZE)*-1;
    y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : MAP_SIZE);


    for(int i = y1; i < y2; i += MAP_SIZE)
    {
        mp_x = game_map.start_x/MAP_SIZE;
        for(int j = x1; j < x2; j += MAP_SIZE)
        {
            if (mp_x < 0 || mp_x >= MAX_MAP_X || mp_y < 0 || mp_y >= MAX_MAP_Y)
            {
                mp_x++;
                continue;
            }
            int val = game_map.T[mp_y][mp_x];
            if(val > 0)
            {
                tile_map[val].SetRect(j, i); //mỗi lần điền ảnh vào 1 ô
                tile_map[val].Render(screen);//render vào màn hình
            }
            mp_x++;
        }
        mp_y++;
    }
}
