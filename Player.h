#include <iostream>
#include <string>
#include "MapObj.h"
#include "Map1.h"
#include "Altar.h"
#include "Item.h"
#include "Enemy.h"

#pragma(once)


class Player: public MapObj {
    friend Map;
    friend MapObj;
    friend Altar;
    friend Item;
    friend Enemy;
    friend void explore_map(Player *player, Map &map);

    protected:
        std::pair<int, int> position = {0,0};
        int points = 10;
        int health = 5;
        int damage = 1;
        int mana = 0;
        int max_health = 5;
        int max_mana = 0;
        ItemData item_data{};

        void die();
        virtual void decrease_health(int x);
        void increase_health(int x);
        bool decrease_mana(int x, bool change);
        void increase_mana(int x);
        void change_max_health(int x);
        void change_max_mana(int x);
        bool change_xy(Map &map, std::pair<int, int> _xy);
        void change_damage(int x);

        virtual void level_up();
    public:
        Player (int lvl, std::string name): MapObj(lvl){
        Obj_name = name;
        alive = true;
        map_hp = 1;
        level = lvl;
        };
        void throw_out_item();
        std::pair<int, int> get_position();
        int get_points();
        int get_health();
        int get_max_health();
        int get_mana();
        int get_max_mana();
        int get_damage();
        virtual bool is_mage();

        bool change_points(int x); 
        void set_item(ItemData _item_data);

        bool go_left(Map& map);
        bool go_right(Map& map);
        bool go_up(Map& map);
        bool go_down(Map& map);

};