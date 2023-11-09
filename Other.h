#include "Player.h"

#pragma(once)

struct ItemData{
    std::string item_name;
    int data[5];
    ItemData();
};

void get_player_info(Player *player);
void get_map(std::pair<int, int> pos, int lvl);

Player * choose_class();