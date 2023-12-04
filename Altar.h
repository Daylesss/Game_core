#pragma(once)
#include "Player.h"
#include "MapObj.h"



class Altar: public MapObj {
    int cost = 0;
    int heal = 0;
    public:

        Altar(int _lvl): MapObj(_lvl){
            Obj_name = "Altar";
            alive = true;
            map_hp = _lvl;
            level = _lvl;
            cost = (rand() % 5 + 1) * level;
            heal = (rand() % 7 + 1) * level;
        };
        void use(Player *player);
};