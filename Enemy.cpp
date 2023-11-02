#include "map.h"

EnemyData Enemy::get_enemy_data(){
    return enemy_data;
}



void Enemy::use(Player &player){
    while (true){
        std::cout<<"---------------------\n"<<"You find a "<<Obj_name<<"!!"<<"---------------------\n"<<std::endl;
        std::cout<<"Do you want to fight with him?\n"<<"(Y/N)"<<std::endl;
        std::string choice; 
        std::cin>>choice;
        if (choice == "Y"){
            fight(player);
        }
        if (choice == "N"){
            std::cout<<"You're walking away from the "<<Obj_name<<std::endl;
                return;
        }

        std::cout<<"Wrong input. Input Y or N"<<std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}