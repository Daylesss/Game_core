#pragma(once)
#include "Player.h"

class Shadow: public Player{
    private:
    int dex = 0;
    void level_up();
    void decrease_health(int x);
    public:
        Shadow (int lvl, std::string name): Player(lvl, name){
        Obj_name = name;
        alive = true;
        map_hp = 1;
        level = lvl;
        health = 15;
        max_health = 15;
        dex = 2;
        };
};