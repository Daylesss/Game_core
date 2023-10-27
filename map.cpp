#include <unordered_map>
#include <string>
#include <map>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <Algorithm>


using namespace std;


class Cell{
    int lvl = 1;
    int done = 0;
    public:
        Cell(int level){
            srand(time(0));

            lvl = level;
            done = rand();
        }

        int get_lvl(){
            return lvl;
        }
        int is_done(){
            return done;
        }
};



class Map {
    int lvl = 1;
    bool created = false;
    std::string game_status;
    std::vector<std::vector<Cell>> sqr_map;

    class WrongPoint{};
    public:
        
        Map(int level){
            created = false;
            lvl = level;
            game_status = "start";
        }

        bool check_way(std::pair<int, int> xy) {
            if ((((xy.first <= lvl) and (xy.first >=0)) and ((xy.second <= lvl) and (xy.second >=0))) and (created)){
                return true;
            }
            return false;
        }

        Cell get_cell(std::pair<int, int> xy) {
            if (check_way(xy)){
                return sqr_map[xy.first][xy.second];
            }
            else {
                std::cerr<<"Wrong coordinates"<<std::endl;
                throw WrongPoint();
            }
        }

        void create_map(){
            for (int i = 0; i<(lvl+1); i++ ){
                std::vector<Cell> frst_vec;
                sqr_map.push_back(frst_vec);

                for (int j = 0; j<(lvl+1); j++ ){
                    sqr_map[i].push_back(Cell(lvl));
                }
            }
            created = true;
        }

        bool is_created(){
            if (created){
                return true;
            }
            else{
                return false;
            }
        }

        std::string get_game_status(){
            return game_status;
        }
};



class MapObj {
    protected:
        int level = 0;
        std::string Obj_name = "Unknown";
        bool alive = false;
        int map_hp = 0;
        std::pair<int, int> xy = {0, 0};

        class WrongInput {};
        class NegativeHealth {};

    public:

        MapObj(Map& map, std::pair<int, int> _xy, int lvl) { //  std::string name, int hp,
            // Obj_name = name;
            alive = true;
            level = lvl;
            // if (hp > 0){
            //     map_hp = hp;
            // }
            // else{
            //     std::cout<<"Map_hp must be positive. Setting it to 1"<< std::endl;
            // }

            if (map.check_way(_xy)){
                xy = _xy;
            }
            else{
                std::cerr<<"Wrong input x or y"<< std::endl;
                throw WrongInput();
            }
        }

        int get_lvl(){
            return level;
        }

        std::string get_name(){
            return Obj_name;
        }

        int get_map_hp(){
            return map_hp;
        }

        bool is_alive(){
            return alive;
        }

        std::pair<int, int> get_xy(){
            return xy;
        }

        void decrease_hp(){
            if (alive){
                if (map_hp > 0){
                    map_hp -=1;

                    if (map_hp==0){
                        alive = false;
                        Obj_name = Obj_name + " (destroyed)";
                        std::cout<< Obj_name<< " destructed"<<endl;
                    }
                }
                else{
                    throw NegativeHealth();
                }
            }
        }

    protected:
        void change_xy(Map &map, std::pair<int, int> _xy){
            if (map.check_way(_xy)){
                xy = _xy;
            }
            else{
                std::cout<<"You can not go to this cell."<<endl;
            }
        }
};


class Player: public MapObj {
    protected:
        int health = 5;
        int damage = 1;
        int mana = 0;
        // Item item;

    public:
        Player (Map& map, std::pair<int, int> _xy, int lvl): MapObj(map, _xy, lvl) {
            alive = true;
            map_hp = 1;

            if (map.check_way(_xy)){
                xy = _xy;
            }
            else{
                std::cerr<<"Wrong input x or y"<< std::endl;
                throw WrongInput();
            }
            }

        void go_left(Map& map){
            std::pair<int, int> xy = get_xy();
            xy.first--;
            change_xy(map, xy);
        }

        void go_right(Map& map){
            std::pair<int, int> xy = get_xy();
            xy.first++;
            change_xy(map, xy);
        }

        void go_up(Map& map){
            std::pair<int, int> xy = get_xy();
            xy.second++;
            change_xy(map, xy);
        }

        void go_down(Map& map){
            std::pair<int, int> xy = get_xy();
            xy.second--;
            change_xy(map, xy);
        }
};


class Item: MapObj {
    
        int cost = 0;
        int lvl = 0;
        int damage = 0;
        int health = 0;
        int mana = 0;
        int item_data[5] ={cost, lvl, damage, health, mana};


    public:
        
        Item(Map& map, std::pair<int, int> _xy, int lvl): MapObj(map, _xy, lvl){
            srand(time(0));
            int random_key = rand() % 5;
            std::vector<std::string> names = {"Red relic", "Green relic", "Blue relic", "White relic", "Black relic"};
            Obj_name = names[random_key];
            alive = true;
            map_hp = random_key % 3 + 1;

            if (map.check_way(_xy)){
                xy = _xy;
            }
            else{
                std::cerr<<"Wrong input x or y"<< std::endl;
                throw WrongInput();
            }


        }

        int get_item_data(){
            int data[5];
            std::copy(std::begin(item_data), std::end(item_data), std::begin(data));
            return *data;
        }
};

class Altar: MapObj {

};


int main()
{
    Map aaa(2);
    std::pair<int, int> th = {1, 0};
    aaa.create_map();
    Player map_obj(aaa, th, 1);

    std::cout << map_obj.get_map_hp()<<std::endl;

    map_obj.go_right(aaa);
    map_obj.go_up(aaa);
    std::cout << "X: "<<map_obj.get_xy().first<<" Y: " <<map_obj.get_xy().second<<std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));
    system("cls");
};
