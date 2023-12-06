#include "cell_test.h"

MapObj::MapObj(int lvl) { 
    alive = true;
    level = lvl;
    map_hp = 1;
}

int MapObj::get_lvl(){
    return level;
}

std::string MapObj::get_name(){
    return Obj_name;
}

int MapObj::get_map_hp(){
    return map_hp;
}

bool MapObj::is_alive(){
    return alive;
}

void MapObj::decrease_map_hp(){
    if (!alive){
        std::cout<<"Already destroyed"<<std::endl;
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

// void MapObj::use(Player *player) {
//     std::cout<< "You can not use this"<<std::endl;
// }

bool Map::check_way(std::pair<int, int> xy) {
    if ((((xy.first <= lvl) && (xy.first >=0)) && ((xy.second <= lvl) && (xy.second >=0))) && (created)){
        return true;
    }
    return false;
}

// void Map::explore(Player *player){
//     if (!is_created()){
//         std::cout << "Map is not created yet.";
//         return;
//     }
//     std::pair<int, int> xy = player->get_position(); 
//     sqr_map[xy.first][xy.second].explore(player);
// }

Cell *Map::get_cell(std::pair<int, int> xy) {
    if (check_way(xy)){
        return &sqr_map[xy.first][xy.second];
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


int Cell::get_lvl(){
    return lvl;
}
int Cell::is_done(){
    return done;
}