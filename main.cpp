#include "map.h"

int main()
{
    Map map(1);
    map.create_map();
    std::pair<int, int> th = {1, 0};
    Item item(1);
    Altar altar(1);
    Player player(map, th, 1);
    Enemy enemy(1);
    std::cout << "Points: " << player.get_points() <<std::endl;
    std::cout << "Damage: " << player.get_damage() << std::endl;
    std::cout << "Health: " << player.get_health() << "/" << player.get_max_health() << std::endl;
    std::cout << "Mana: " << player.get_mana() << "/" << player.get_max_mana() << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));

    altar.use(player);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "Points: " << player.get_points() <<std::endl;
    std::cout << "Damage: " << player.get_damage() << std::endl;
    std::cout << "Health: " << player.get_health() << "/" << player.get_max_health() << std::endl;
    std::cout << "Mana: " << player.get_mana() << "/" << player.get_max_mana() << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));

    item.use(player);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "Points: " << player.get_points() <<std::endl;
    std::cout << "Damage: " << player.get_damage() << std::endl;
    std::cout << "Health: " << player.get_health() << "/" << player.get_max_health() << std::endl;
    std::cout << "Mana: " << player.get_mana() << "/" << player.get_max_mana() << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(5));

    enemy.use(player);

    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "Points: " << player.get_points() <<std::endl;
    std::cout << "Damage: " << player.get_damage() << std::endl;
    std::cout << "Health: " << player.get_health() << "/" << player.get_max_health() << std::endl;
    std::cout << "Mana: " << player.get_mana() << "/" << player.get_max_mana() << std::endl;
};