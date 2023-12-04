#include "Player.h"
#include "Other.h"
#include "Cell.h"
#pragma(once)

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