#include "map.h"

int main()
{   
    srand(time(0));
    Map map(1);
    map.create_map();

    Player player(1);

    explore_map(player, map);
};