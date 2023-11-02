#include "map.h"

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

void MapObj::use() {
    std::cout<< "You can not use this"<<std::endl;
}
