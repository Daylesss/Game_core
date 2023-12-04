#pragma(once)
#include "MapObj.h"
#include "Player.h"

struct EnemyData{
    std::string name = "Unknown";
    bool boss = false;
    int damage = 0;
    int health = 5;
    int points = 0;
};
class Enemy: public MapObj{
    EnemyData enemy_data;
    std::string get_inp();
    std::pair<int, int> gen_nums();
    void fight(Player *player);
    void decrease_health(int x);

    void die();

    void get_enemy_info();

    public:
    Enemy (int lvl): MapObj(lvl){
        std::string names[4] = {"Bandit", "Monster", "Knight", "Elemental"}; 
        Obj_name = names[rand() % 4];
        enemy_data.name = Obj_name;
        alive = true;
        map_hp = 1;
        if ((rand() % 5) > 3){
            enemy_data.boss = true;
            enemy_data.name +=" (boss)";
            level+=1;
        }

        enemy_data.damage = (rand() % 3 + 1) * level;
        enemy_data.health = (rand() % 10 + 1) * level + 1;
        enemy_data.points = (rand() % 10 + 2) * level;
    };

    EnemyData get_enemy_data();
    
    void use(Player * player);

};