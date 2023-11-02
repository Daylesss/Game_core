#include "map.h"


Map::Map(int level){
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
}

bool Map::check_way(std::pair<int, int> xy) {
    if ((((xy.first <= lvl) and (xy.first >=0)) and ((xy.second <= lvl) and (xy.second >=0))) and (created)){
        return true;
    }
    return false;
}

Cell Map::get_cell(std::pair<int, int> xy) {
    if (check_way(xy)){
        return sqr_map[xy.first][xy.second];
    }
    else {
        std::cerr<<"Wrong coordinates"<<std::endl;
        throw WrongPoint();
    }
}

void Map::create_map(){
    for (int i = 0; i<(lvl+1); i++ ){
        std::vector<Cell> frst_vec;
        sqr_map.push_back(frst_vec);

        for (int j = 0; j<(lvl+1); j++ ){
            sqr_map[i].push_back(Cell(lvl));
        }
    }
    created = true;
}

bool Map::is_created(){
    return created;
}

std::string Map::get_game_status(){
    return game_status;
}
