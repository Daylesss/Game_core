#pragma once
#include <memory>
#include <string>
#include <vector>
#include <iostream>

class Cell;

class Map {
    // friend void explore_map(Player *player, Map &map);
    int lvl = 1;
    bool created = false;
    std::string game_status = "-";
    std::vector<std::vector<Cell>> sqr_map;
    class WrongPoint{};

    // void explore(Player *player);

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
        Cell *get_cell(std::pair<int, int> xy);
        void create_map();
        bool is_created();
        std::string get_game_status();
        int get_level();
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
        virtual void decrease_map_hp();
        // virtual void use(Player *player);
};

class Altar:public MapObj{
    public:
    Altar(int _lvl): MapObj(_lvl){
    Obj_name = "Altar";
    }
};

class Item:public MapObj{
    public:
    Item(int _lvl): MapObj(_lvl){
    Obj_name = "Item";
    }
};

class Enemy:public MapObj{
    public:
    Enemy(int _lvl): MapObj(_lvl){
    Obj_name = "Enemy";
    }
};

class Cell{
    friend Map;
    int lvl = 1;
    int done = 0;
    std::shared_ptr<MapObj> map_obj;

    // void explore(Player *player);

    public:
        Cell(int level){
            lvl = level;

            int key = rand() % 3;

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