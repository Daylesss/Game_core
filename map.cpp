#include "map.h"

bool Map::check_way(std::pair<int, int> xy) {
    if ((((xy.first <= lvl) and (xy.first >=0)) and ((xy.second <= lvl) and (xy.second >=0))) and (created)){
        return true;
    }
    return false;
}

void Map::explore(Player *player){
    if (!is_created()){
        std::cout << "Map is not created yet.";
        return;
    }
    std::pair<int, int> xy = player->get_position(); 
    sqr_map[xy.first][xy.second].explore(player);
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

int Map::get_level(){
    return lvl;
}

