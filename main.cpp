#pragma(once)
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <Algorithm>
#include "Map.h"
#include "Player.h"

int main()
{   

    srand(time(0));
    Map map(3);
    map.create_map();

    Player * player = choose_class();

    explore_map(player, map);
    // Player player(1, "TEST!");
    // std:: cout << player.get_points() << "\n";
    // player.change_points(10000);
    // std:: cout << player.get_points() << "\n";
};