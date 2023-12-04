#include "Werewolf.h"

void Werewolf::level_up(){
    level +=1;
    if (map_hp == 1){
        std::cout << "With the arrival of new forces, your cursed blood calms down." << std::endl;
        map_hp = 2;
        change_max_health(-7);
        change_damage(-3);
        decrease_health(health-max_health);
        Obj_name.erase(Obj_name.length() - 11, 11);
    }
    change_max_health(5);
    increase_health(5);
    change_damage(4);

    std::cout << "Level up!" << std::endl;
};


void Werewolf::transformation(){
    std::cout << "Because of the decline of strength, you lose control of yourself." << std::endl;
    std::cout << "Your cursed blood is boiling." << std::endl;
    map_hp = 1;
    Obj_name += " (Werewolf)";
    change_max_health(7);
    increase_health(7);
    change_damage(3);
};

void Werewolf::decrease_health(int x){
    if (x <= 0){
        return;
    }
    if (health > x){
        health -=x;
        std::cout << "You got " << std::to_string(x) << " damage"<< std::endl; 
    }
    else if (map_hp == 1){
        std::cout << "You got " << std::to_string(x) << " damage"<< std::endl;
        die();
    }
    else{
        std::cout << "You got " << std::to_string(x) << " damage"<< std::endl;
        transformation();
    }
};
