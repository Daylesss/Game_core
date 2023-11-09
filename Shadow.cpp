#include "map.h"

void Shadow::level_up(){
    level +=1;
    change_max_health(5);
    increase_health(5);
    change_damage(3);
    dex += 1;
};

void Shadow::decrease_health(int x){
    if (x <= 0){
        return;
    }
    int a = rand() % 10;
    if ((a + dex)>= 9){
        std::cout << "Your disembodied body helps you avoid the attack" << std::endl;
        return;
    }
    if (health > x){
        health -=x;
        std::cout << "You got " << std::to_string(x) << " damage"<< std::endl; 
    }
    else{
        std::cout << "You got " << std::to_string(x) << " damage"<< std::endl;
        die();
    }
};