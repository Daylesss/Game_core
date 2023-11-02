#include "map.h"

int main()
{
    Map map(1);
    std::pair<int, int> th = {1, 0};
    map.create_map();
    // Player map_obj(aaa, th, 1);

    Item item(1);
    Altar altar(1);
    Player player(map, th, 1);

    altar.use(player);

    std::cout <<"New player "<< player.get_health()<<std::endl;
};