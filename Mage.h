#include "Player.h"
#pragma(once)

class Mage: public Player{
    protected:
        void level_up();
    public:
        Mage (int lvl, std::string name): Player(lvl, name){
        Obj_name = name;
        alive = true;
        map_hp = 1;
        level = lvl;
        max_mana = 3;
        mana = 3;
        health = 10;
        max_health = 10;
        damage = 3;
        };

        bool is_mage();
};