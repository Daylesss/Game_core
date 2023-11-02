#include "map.h"

void Altar::use(Player &player){

    char choice = '\0';
    while (true){
        std::cout<<"---------------------\n"<<"You find an Altar!!\n"<<"---------------------"<<std::endl;

        std::cout<<"Heal "<<heal<<"hp?\n Cost: "<<cost<<" points\n (Y/N)"<<std::endl;

        std::cin>>choice;
        if (choice=='Y'){
            if(player.change_points(-cost)){
                player.increase_health(heal);
                decrease_map_hp();
                system("cls");
                return;
            }
            return;
        }

        if (choice=='N'){
            system("cls");
            std::cout<<"You're walking away from the altar"<<std::endl;
            return;
        }

        std::cout<<"Wrong input. Input Y or N"<<std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));
        system("cls");
    }
}