#include "map.h"

int main()
{   

    srand(time(0));
    Map map(1);
    map.create_map();

    Player * player = choose_class();

    explore_map(player, map);

};