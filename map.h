#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <Algorithm>

#pragma(once)

class Map;
class Player;
class Altar;
class Item;
class Enemy;
class Cell;

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
        virtual void decrease_map_hp();
        virtual void use(Player &player);
};


void explore_map(Player &player, Map &map);
class Map {
    friend void explore_map(Player &player, Map &map);
    int lvl = 1;
    bool created = false;
    std::string game_status = "-";
    std::vector<std::vector<Cell>> sqr_map;
    class WrongPoint{};

    void explore(Player &player);

    public:
        Map(int level){
            if (level<=0){
                std::cerr<<"Level must be positive. Setting it to 1."<<std::endl;
                lvl = 1;
                created = false;
                game_status = "start";
            }
            else{
                created = false;
                lvl = level;
                game_status = "start";
            }
        };
        bool check_way(std::pair<int, int> xy);
        Cell get_cell(std::pair<int, int> xy);
        void create_map();
        bool is_created();
        std::string get_game_status();
};

struct ItemData{
    std::string item_name;
    int data[5];
    ItemData();
};



class Player: public MapObj {
    friend Map;
    friend MapObj;
    friend Altar;
    friend Item;
    friend Enemy;
    friend void explore_map(Player &player, Map &map);

    protected:
        std::pair<int, int> position = {0,0};
        int points = 10;
        int health = 5;
        int damage = 1;
        int mana = 1;
        int max_health = 5;
        int max_mana = 1;
        ItemData item_data{};

        void die();
        virtual void decrease_health(int x);
        void increase_health(int x);
        bool decrease_mana(int x, bool change);
        void increase_mana(int x);
        bool change_points(int x); 
        void change_max_health(int x);
        void change_max_mana(int x);
        bool change_xy(Map &map, std::pair<int, int> _xy);
    public:
        Player (int lvl): MapObj(lvl){
        alive = true;
        map_hp = 1;
        level = lvl;
        };
        void throw_out_item();
        std::pair<int, int> get_position();
        int get_points();
        int get_health();
        int get_max_health();
        int get_mana();
        int get_max_mana();
        int get_damage();

        void set_item(ItemData _item_data);

        bool go_left(Map& map);
        bool go_right(Map& map);
        bool go_up(Map& map);
        bool go_down(Map& map);

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
            void decrease_map_hp();
};

class Altar: public MapObj {
    int cost = 0;
    int heal = 0;
    public:

        Altar(int _lvl): MapObj(_lvl){
            Obj_name = "Altar";
            alive = true;
            map_hp = _lvl;
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
    int points = 0;
};

class Enemy: public MapObj{
    EnemyData enemy_data;
    std::string get_inp();
    std::pair<int, int> gen_nums();
    void fight(Player &player);
    void decrease_health(int x);

    void die();

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
    
    void use(Player & player);

};

class Cell{
    friend Map;
    int lvl = 1;
    int done = 0;
    MapObj * map_obj;

    void explore(Player &player);
    public:
        Cell(int level){
            lvl = level;

            int key = rand() % 3;

            if (key == 0){
                map_obj = new Altar{lvl};
            }
            else if (key == 1){
                map_obj = new Item{lvl};
            }
            else{
                map_obj = new Enemy{lvl};
            }
        }  
        int get_lvl();
        int is_done();
};

