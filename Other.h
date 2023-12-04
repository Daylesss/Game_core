#pragma(once)
#include "Player.h"
#include "Map.h"


struct ItemData{
    std::string item_name;
    int data[5];
    ItemData();
};

void explore_map(Player *player, Map &map)
void get_player_info(Player *player);
void get_map(std::pair<int, int> pos, int lvl);

Player * choose_class();