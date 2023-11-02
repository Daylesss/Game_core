
#include "map.h"

void Player::die(){
    health = 0;
    alive = false;
    map_hp = 0;
    std::cout << "!!!!!!!!!!!!!!!!\nYOU LOSE\n!!!!!!!!!!!!!!!!"<<std::endl;
}

void Player::decrease_health(int x){
    if (x <= 0){
        return;
    }
    if (health > x){
        health -=x;
    }
    else{
        die();
    }
};

void Player::increase_health(int x){
    if (x <= 0){
        return;
    }
    int temp_health = health + x;
    if (temp_health > max_health){
        health = max_health;
    }
    else{
        health += x;
    }
}

void Player::increase_mana(int x){
    if (x <= 0){
        return;
    }
    int temp_mana = mana + x;
    if (temp_mana > max_mana){
        mana = max_mana;
    }
    else{
        mana += x;
    }
}

bool Player::decrease_mana(int x, bool change){
    if (x <= 0){
        return true;
    }
    if (x > mana){
        if (change){
            mana = 0;
        }
        return false;
    }
    else{
        mana -= x;
        return true;
    }
}

void Player::change_max_health(int x){
    int temp_max_health = x + max_health;
    if (temp_max_health <= 0){
        max_health = 1;
    }
    else{
        max_health += x;
    }
}

void Player::change_max_mana(int x){
    int temp_max_mana = x + max_mana;
    if (temp_max_mana <= 0){
        max_mana = 1;
    }
    else{
        max_mana += x;
    }
}

bool Player::change_points(int x){
    int temp_points = points + x;
    if (temp_points < 0){
        std::cout<<"You have not enought points"<<std::endl;
        return false;
    }
    else{
        points += x;
        return true;
    }
}

bool Player::change_xy(Map &map, std::pair<int, int> _xy){
    if (map.check_way(_xy)){
        position = _xy;
        std::cout <<"New: (" <<position.first<<":"<< position.second <<")" << std::endl;
        return true;
    }
    else{
        std::cout<<"You can not go to this cell."<<std::endl;
        return false;
    }
}


void Player::throw_out_item(){
    // int item_data[5] ={cost, level, damage, health, mana};
    damage -= item_data.data[2];
    change_max_mana(-item_data.data[4]);
    decrease_mana(item_data.data[4], true);
    change_max_health(-item_data.data[3]);
    decrease_health(item_data.data[3]);
    for (int i; i<5; i++){
        item_data.data[i] = 0;
    }
    item_data.item_name = "Unknown";
}


bool Player::go_left(Map& map){
    std::pair<int, int> xy = get_position();
    std::cout <<"Old: (" <<xy.first<<":"<< xy.second <<")" << std::endl;
    xy.first--;
    bool is_go= change_xy(map, xy);
    return is_go;
}

bool Player::go_right(Map& map){
    std::pair<int, int> xy = get_position();
    std::cout <<"Old: (" <<xy.first<<":"<< xy.second <<")" << std::endl;
    xy.first++;
    bool is_go= change_xy(map, xy);
    return is_go;
}

bool Player::go_up(Map& map){
    std::pair<int, int> xy = get_position();
    std::cout <<"Old: (" <<xy.first<<":"<< xy.second <<")" << std::endl;
    xy.second++;
    bool is_go = change_xy(map, xy);
    return is_go;
}

bool Player::go_down(Map& map){
    std::pair<int, int> xy = get_position();
    std::cout <<"Old: (" <<xy.first<<":"<< xy.second <<")" << std::endl;
    xy.second--;
    bool is_go= change_xy(map, xy);
    return is_go;
}

std::pair<int, int> Player::get_position(){
    return position;
}

int Player::get_points(){
    return points;
}

int Player::get_damage(){
    return damage;
}

int Player::get_health(){
    return health;
}

int Player::get_mana(){
    return mana;
}

int Player::get_max_health(){
    return max_health;
}

int Player::get_max_mana(){
    return max_mana;
}

void Player::set_item(ItemData _item_data){
    item_data = _item_data;
};