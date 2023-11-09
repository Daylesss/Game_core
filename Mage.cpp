#include "map.h"

bool Mage::is_mage(){
    return true;
}

void Mage::level_up(){
    level +=1;
    change_max_health(3);
    increase_health(3);
    change_damage(2);
    change_max_mana(1);
    increase_mana(1);
};