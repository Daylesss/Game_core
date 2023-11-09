#include "Player.h"

#pragma(once)


class Werewolf: public Player{
    void level_up();
    void decrease_health(int x);
    void transformation();
    public:
        Werewolf (int lvl, std::string name): Player(lvl, name){
        Obj_name = name;
        alive = true;
        map_hp = 2;
        level = lvl;
        health = 10;
        max_health = 10;
        damage = 2;
        };
};