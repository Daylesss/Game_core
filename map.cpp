#include <unordered_map>
#include <string>
#include <map>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <Algorithm>
// #include "map.h"


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
    std::string game_status = "-";
    std::vector<std::vector<Cell>> sqr_map;

    class WrongPoint{};
    public:
        
        Map(int level){
            if (level<=0){
                std::cerr<<"Level must be positive. Setting it to 1.";
                lvl = 1;
                created = false;
                game_status = "start";
            }
            else{
                created = false;
                lvl = level;
                game_status = "start";
            }
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
            return created;
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

        class WrongInput {};
        class NegativeHealth {};

    public:

        MapObj(int lvl) { 
            alive = true;
            level = lvl;
            map_hp = 1;
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

        virtual void decrease_hp(){
            if (!alive){
                std::cout<<"Already destroyed";
                return;
            }
            
            if (map_hp <= 0){
                throw NegativeHealth();
            }
            
            map_hp -=1;

            if (map_hp==0){
                alive = false;
                std::cout<< Obj_name<< " destructed"<<std::endl;
                Obj_name = Obj_name + " (destroyed)";
            }
        }

        virtual void use(){
            std::cout<< "You can not use this";
        }
};
class Player: MapObj{
    int points;
    int health;
    int damage;
    int mana;
    Item item;
    public:
        void throw_out();
};
class Item: public MapObj {
    
        int cost = 0;
        int damage = 0;
        int health = 0;
        int mana = 0;
        int item_data[5] ={cost, level, damage, health, mana};

        void set_params(int key){

            std::vector<std::string> names = {"Red relic", "Green relic", "Blue relic", "White relic", "Black relic", "Rainbow relic"};
            map_hp = key % 3 + 1;
            cost  = (key % 10 + 1) * level;
            int choice = key % 6;
            Obj_name = names[choice];
            int modif = (key % 5 + 1) * level;

            if (choice==0){
                damage = modif;
            }

            if (choice==1){
                health = modif;
            }

            if (choice==2){
                mana = modif;
            }

            if (choice==3){
                health = modif;
                mana = modif;
            }

            if (choice==4){
                health = modif;
                damage = modif;
            }

            if (choice==5){
                health = modif;
                mana = modif;
                damage = modif;
            }

            item_data[0] = cost;
            item_data[1] = level;
            item_data[2] = damage;
            item_data[3] = health;
            item_data[4] = mana;
        }



    public:
        
        Item(int _lvl): MapObj(_lvl) {
            level = _lvl;
            srand(time(0));
            int random_key = rand();
            alive = true;

            set_params(random_key);
        }

        int* get_item_data(){
            return item_data;
        }

        

        void use(Player * player){
            char choice = '\0';
            while (true){
                std::cout<<"---------------------\n"<<"You find a "<<Obj_name<<"!!"<<"---------------------\n"<<std::endl;


                std::cout<<"Cost: "<<cost<<"points"<<std::endl;
                std::cout<<"+ "<<damage<<" damage"<<std::endl;
                std::cout<<"+ "<<health<<" health"<<std::endl;
                std::cout<<"+ "<<mana<<" mana"<<std::endl;
                std::cout<<"---------------------\n\n"<<"Do you want to pick it?\n"<<"(Y/N)"<<std::endl;

                std::cin>>choice;
                if (choice=='Y'){
                    if (cost> player->points){
                        std::cout<<"You have not got enough points...";
                        return;
                    }
                    player->throw_out();
                    player->points -= cost;
                    player->health += health;
                    player->damage += damage;
                    player->mana += mana;
                    //
                    // ДОБАВЛЕНИЕ  ITEM  К PLAYER СДЕЛАТЬ В ФУНКЦИИ!!!
                    //
                    this->decrease_hp();
                    return;
                }

                if (choice=='N'){
                    std::cout<<"You're walking away from the "<<Obj_name<<std::endl;
                    return;
                }

                std::cout<<"Wrong input. Input Y or N";

                std::this_thread::sleep_for(std::chrono::seconds(2));
            }
        }

        virtual void decrease_hp(){
            if (!alive){
                std::cout<<"Already empty";
                return;
            }
            
            if (map_hp <= 0){
                throw NegativeHealth();
            }
            
            map_hp -=1;

            if (map_hp==0){
                alive = false;
                std::cout<< Obj_name<< " empty now."<<std::endl;
                Obj_name = Obj_name + " (empty)";
            }
        }

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
        }

        void use(Player *player){

            char choice = '\0';
            while (true){
                std::cout<<"---------------------\n"<<"You find an Altar!!"<<"---------------------\n"<<std::endl;

                std::cout<<"Heal "<<heal<<"hp?\n Cost: "<<cost<<" points\n (Y/N)";

                std::cin>>choice;
                if (choice=='Y'){
                    if (cost> player->points){
                        std::cout<<"You have not got enough points...";
                        return;
                    }
                    player->health += heal;
                    player->points -= cost;
                    this->decrease_hp();
                    return;
                }

                if (choice=='N'){
                    std::cout<<"You're walking away from the altar";
                    return;
                }

                std::cout<<"Wrong input. Input Y or N";

                std::this_thread::sleep_for(std::chrono::seconds(2));
            }


        }

        

};
class Player: public MapObj {
    friend MapObj;
    friend Altar;
    friend Item;
    protected:
        std::pair<int, int> xy = {0,0};
        int points = 0;
        int health = 5;
        int damage = 1;
        int mana = 0;
        Item item{0};

        void change_xy(Map &map, std::pair<int, int> _xy){
            if (map.check_way(_xy)){
                xy = _xy;
            }
            else{
                std::cout<<"You can not go to this cell."<<std::endl;
            }
        }

    public:
        Player (Map& map, std::pair<int, int> _xy, int lvl): MapObj(lvl) {
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
            }

        void throw_out(){
            int *item_data = item.get_item_data(); // int item_data[5] ={cost, level, damage, health, mana};
            damage -= item_data[2];
            mana -= item_data[4];

            if (health > item_data[3]){
                health -= item_data[3];
            }
            else{
                health = 1;
            }
            item = Item(0);
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

        std::pair<int, int> get_xy(){
            return xy;
        }

        int get_points(){
            return points;
        }

        int* get_player_data(){
            int data[3] ={health,damage, mana};
            return data;
        }

        void set_item(Item &_item){
            item = _item;
        }
};





int main()
{
    Map map(1);
    std::pair<int, int> th = {1, 0};
    // aaa.create_map();
    // Player map_obj(aaa, th, 1);

    Item item(1);
    Altar altar(1);
    Player player(map, th, 1);

    std::cout <<"Item "<< item.get_item_data()[3]<<std::endl;
    std::cout <<"Player "<< player.get_player_data()[0]<<std::endl;
    item.use(&player);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout <<"New player "<< player.get_player_data()[0]<<std::endl;

    player.set_item(item);

    player.throw_out();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::cout <<"Throw player "<< player.get_player_data()[0]<<std::endl;



    // item.decrease_hp();
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    // std::cout << item.get_map_hp()<<std::endl;


    // for(int i = 0; i<5; i++)
    // {
    //     std::cout<< item.get_item_data()[i]<<"  ";
    // }
    // std::cout<<std::endl;


    // std::cout<< item.get_name()<<std::endl;




    // map_obj.go_right(aaa);
    // map_obj.go_up(aaa);
    // std::cout << "X: "<<map_obj.get_xy().first<<" Y: " <<map_obj.get_xy().second<<std::endl;

    // std::this_thread::sleep_for(std::chrono::seconds(2));
    // system("cls");
};
