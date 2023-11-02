
#include "map.h"


void Player::change_xy(Map &map, std::pair<int, int> _xy){
    if (map.check_way(_xy)){
        xy = _xy;
    }
    else{
        std::cout<<"You can not go to this cell."<<std::endl;
    }
}


void Player::throw_out_item(){
    // int item_data[5] ={cost, level, damage, health, mana};
    damage -= item_data.data[2];
    mana -= item_data.data[4];

    if (health > item_data.data[3]){
        health -= item_data.data[3];
    }
    else{
        health = 1;
    }
    for (int i; i<5; i++){
        item_data.data[i] = 0;
    }
    item_data.item_name = "Unknown";
}


void Player::go_left(Map& map){
    std::pair<int, int> xy = get_xy();
    xy.first--;
    change_xy(map, xy);
}

void Player::go_right(Map& map){
    std::pair<int, int> xy = get_xy();
    xy.first++;
    change_xy(map, xy);
}

void Player::go_up(Map& map){
    std::pair<int, int> xy = get_xy();
    xy.second++;
    change_xy(map, xy);
}

void Player::go_down(Map& map){
    std::pair<int, int> xy = get_xy();
    xy.second--;
    change_xy(map, xy);
}

std::pair<int, int> Player::get_xy(){
    return xy;
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

void Player::set_item(ItemData _item_data){
    item_data = _item_data;
};