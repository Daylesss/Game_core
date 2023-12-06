#include "cell_test.h"

int main()
{   

    srand(time(0));
    Map map(3);
    map.create_map();

    std::pair<int, int> xy{1,2};

    int a = map.get_cell(xy)->get_lvl();

    std::cout<<a;

    // Player * player = choose_class();

    // explore_map(player, map);
    // // Player player(1, "TEST!");
    // // std:: cout << player.get_points() << "\n";
    // // player.change_points(10000);
    // // std:: cout << player.get_points() << "\n";
};