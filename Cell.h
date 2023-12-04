#pragma(once)
#include "MapObj.h"
#include "Player.h"
#include "Altar.h"
#include "Item.h"
#include "Enemy.h"



class Cell{
    friend Map;
    int lvl = 1;
    int done = 0;
    MapObj * map_obj;

    void explore(Player *player);
    public:
        Cell(int level){
            lvl = level;

            int key = rand() % 3;

            if (key == 0){
                map_obj = new Altar{lvl};
            }
            else if (key == 1){
                map_obj = new Item{lvl};
            }
            else{
                map_obj = new Enemy{lvl};
            }
        }  
        int get_lvl();
        int is_done();
};