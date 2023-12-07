#pragma once
#include <windows.h>
#include <memory>
#include <conio.h>
#include <iostream>
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <Algorithm>

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
        virtual void use(Player *player);
};


void explore_map(Player *player, Map &map);
class Map {
    friend void explore_map(Player *player, Map &map);
    int lvl = 1;
    bool created = false;
    std::string game_status = "-";
    std::vector<std::vector<Cell>> sqr_map;
    class WrongPoint{};

    void explore(Player *player);

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
        int get_level();
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
    friend void explore_map(Player *player, Map &map);

    protected:
        std::pair<int, int> position = {0,0};
        int points = 10;
        int health = 5;
        int damage = 1;
        int mana = 0;
        int max_health = 5;
        int max_mana = 0;
        ItemData item_data{};

        void die();
        virtual void decrease_health(int x);
        void increase_health(int x);
        bool decrease_mana(int x, bool change);
        void increase_mana(int x);
        void change_max_health(int x);
        void change_max_mana(int x);
        bool change_xy(Map &map, std::pair<int, int> _xy);
        void change_damage(int x);

        virtual void level_up();
    public:
        Player (int lvl, std::string name): MapObj(lvl){
        Obj_name = name;
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
        virtual bool is_mage();

        bool change_points(int x); 
        void set_item(ItemData _item_data);

        bool go_left(Map& map);
        bool go_right(Map& map);
        bool go_up(Map& map);
        bool go_down(Map& map);

};

class Mage: public Player{
    protected:
        void level_up();
    public:
        Mage (int lvl, std::string name): Player(lvl, name){
        Obj_name = name;
        alive = true;
        map_hp = 1;
        level = lvl;
        max_mana = 3;
        mana = 3;
        health = 10;
        max_health = 10;
        damage = 3;
        };

        bool is_mage();
};

class Shadow: public Player{
    private:
    int dex = 0;
    void level_up();
    void decrease_health(int x);
    public:
        Shadow (int lvl, std::string name): Player(lvl, name){
        Obj_name = name;
        alive = true;
        map_hp = 1;
        level = lvl;
        health = 15;
        max_health = 15;
        dex = 2;
        };
};

class Werewolf: public Player{
    void level_up();
    void decrease_health(int x);
    void transformation();
    public:
        Werewolf (int lvl, std::string name): Player(lvl, name){
        Obj_name = name;
        alive = true;
        map_hp = 2;
        level = lvl;
        health = 10;
        max_health = 10;
        damage = 2;
        };
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
                // srand(time(0));
                int random_key = rand();
                alive = true;

                set_params(random_key);
            };
            ItemData get_item_data();
            void use(Player *player);
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
        void use(Player *player);
};

void get_player_info(Player *player);
void get_map(std::pair<int, int> pos, int lvl);
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

class Cell{
    friend Map;
    int lvl = 1;
    int done = 0;
    std::shared_ptr<MapObj> map_obj;

    void explore(Player *player);
    public:
        Cell(int level){
            lvl = level;

            int key = rand() % 4;

            if (key == 0){
                map_obj = std::make_shared<Altar>(lvl);
            }
            else if (key == 1){
                map_obj = std::make_shared<Item>(lvl);
            }
            else{
                map_obj = std::make_shared<Enemy>(lvl);
            }
        }  
        int get_lvl();
        int is_done();
};



Player * choose_class();
