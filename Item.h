#include "Player.h"
#pragma(once)

class Item: public MapObj {
    
        int cost = 0;
        int damage = 0;
        int health = 0;
        int mana = 0;
        ItemData item_data{};

        void set_params(int key);
        public:
            Item(int _lvl): MapObj(_lvl){
                level = _lvl;
                srand(time(0));
                int random_key = rand();
                alive = true;

                set_params(random_key);
            };
            ItemData get_item_data();
            void use(Player *player);
            void decrease_map_hp();
};