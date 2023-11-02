#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <Algorithm>

#pragma(once)

class Cell{
    int lvl = 1;
    int done = 0;
    public:
        Cell(int level);
        int get_lvl();
        int is_done();
};

class Map {
    int lvl = 1;
    bool created = false;
    std::string game_status = "-";
    std::vector<std::vector<Cell>> sqr_map;
    class WrongPoint{};
    public:
        Map(int level);
        bool check_way(std::pair<int, int> xy);
        Cell get_cell(std::pair<int, int> xy);
        void create_map();
        bool is_created();
        std::string get_game_status();
};

class MapObj {
    protected:
        int level = 0;
        std::string Obj_name = "Unknown";
        bool alive = false;
        int map_hp = 0;

        class WrongInput {};
        class NegativeHealth {};

    public:

        MapObj(int lvl);
        int get_lvl();
        std::string get_name();
        int get_map_hp();
        bool is_alive();
        virtual void decrease_hp();
        virtual void use();
};
struct ItemData{
    std::string item_name;
    int data[5];
    ItemData();
};


class Altar;
class Item;

class Player: public MapObj {
    friend MapObj;
    friend Altar;
    friend Item;
    protected:
        std::pair<int, int> xy = {0,0};
        int points = 100;
        int health = 5;
        int damage = 1;
        int mana = 0;
        ItemData item_data{};

        void change_xy(Map &map, std::pair<int, int> _xy);
    public:
        Player (Map& map, std::pair<int, int> _xy, int lvl): MapObj(lvl){
        alive = true;
        map_hp = 1;
        level = lvl;


        if (map.check_way(_xy)){
            xy = _xy;
        }
        else{
            std::cerr<<"Wrong input x or y"<< std::endl;
            throw WrongInput();
        }
        };
        void throw_out_item();
        std::pair<int, int> get_xy();
        int get_points();
        int get_health();
        int get_mana();
        int get_damage();

        void set_item(ItemData _item_data);

        void go_left(Map& map);
        void go_right(Map& map);
        void go_up(Map& map);
        void go_down(Map& map);
};

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
            void use(Player &player);
            virtual void decrease_hp();
};

class Altar: public MapObj {
    int cost = 0;
    int heal = 0;
    public:

        Altar(int _lvl): MapObj(_lvl){
            Obj_name = "Altar";
            alive = true;
            map_hp = _lvl;
            srand(time(0));
            level = _lvl;
            cost = (rand() % 5 + 1) * level;
            heal = (rand() % 7 + 1) * level;
        };
        void use(Player &player);
};


struct EnemyData{
    std::string name = "Unknown";
    bool boss = false;
    int damage = 0;
    int health = 5;
};

class Enemy: public MapObj{
    EnemyData enemy_data;

    void fight(Player &player);

    public:
    Enemy (int lvl): MapObj(lvl){
        srand(time(0));
        std::string names[4] = {"Bandit", "Monster", "Knight", "Elemental"}; 
        Obj_name = names[rand() % 5];
        alive = true;
        map_hp = 1;
        if ((rand() % 5) > 3){
            enemy_data.boss = true;
            enemy_data.name +=" (boss)";
            level+=1;
        }

        enemy_data.damage = (rand() % 3 + 1) * level;
        enemy_data.health = (rand() % 10 + 1) * level;

    };

    EnemyData get_enemy_data();
    
    void use(Player & player);

};
