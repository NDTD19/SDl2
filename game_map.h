#ifndef GAME_MAP_H_INCLUDED
#define GAME_MAP_H_INCLUDED

#include "CommonFunction.h"
#include "Base.h"

#define MAX_TILE 20
class TileMap : public Base
{
public:
    TileMap() {;}
    ~TileMap() {;}
};

class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {return game_map;};
    void SetMap(Map& map_data) {game_map = map_data;};
private:
    Map game_map;
    TileMap tile_map[MAX_TILE];
};


#endif // GAME_MAP_H_INCLUDED
