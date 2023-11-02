#include "map.h"


void Item::set_params(int key){

    std::vector<std::string> names = {"Red relic", "Heal potion", "Blue relic", "White relic", "Black relic", "Rainbow relic"};
    map_hp = key % 3 + 1;
    cost  = (key % 10 + 1) * level;
    int choice = key % 6;
    Obj_name = names[choice];
    int modif = (key % 5 + 1) * level;

    if (choice==0){
        damage = modif;
    }

    if (choice==1){
        health = modif*3;
    }

    if (choice==2){
        mana = modif;
    }

    if (choice==3){
        health = modif*2;
        mana = modif;
    }

    if (choice==4){
        health = modif;
        damage = modif;
    }

    if (choice==5){
        health = modif*2;
        mana = modif;
        damage = modif;
    }

    item_data.item_name = Obj_name;
    item_data.data[0] = cost;
    item_data.data[1] = level;
    item_data.data[2] = damage;
    item_data.data[3] = health;
    item_data.data[4] = mana;
}

ItemData Item::get_item_data(){
    return item_data;
}

void Item::use(Player &player) {
    char choice = '\0';
    while (true){
        std::cout<<"---------------------\n"<<"You find a "<<Obj_name<<"!!"<<"---------------------\n"<<std::endl;


        std::cout<<"Cost: "<<cost<<"points"<<std::endl;
        std::cout<<"+ "<<damage<<" damage"<<std::endl;
        std::cout<<"+ "<<health<<" health"<<std::endl;
        std::cout<<"+ "<<mana<<" mana"<<std::endl;
        std::cout<<"---------------------\n\n"<<"Do you want to pick it?\n"<<"(Y/N)"<<std::endl;

        std::cin>>choice;
        if (choice=='Y'){
            if (cost> player.points){
                std::cout<<"You have not got enough points...";
                return;
            }
            player.throw_out_item();
            player.points -= cost;
            player.health += health;
            player.damage += damage;
            player.mana += mana;
            
            //ДОБАВЛЕНИЕ  ITEM  К PLAYER СДЕЛАТЬ В ФУНКЦИИ!!!
            player.set_item(item_data);
            this->decrease_hp();
            return;
        }

        if (choice=='N'){
            std::cout<<"You're walking away from the "<<Obj_name<<std::endl;
            return;
        }

        std::cout<<"Wrong input. Input Y or N"<<std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void Item::decrease_hp(){
    if (!alive){
        std::cout<<"Already empty"<<std::endl;
        return;
    }
    
    if (map_hp <= 0){
        throw NegativeHealth();
    }
    
    map_hp -=1;

    if (map_hp==0){
        alive = false;
        std::cout<< Obj_name<< " empty now."<<std::endl;
        Obj_name = Obj_name + " (empty)";
    }
}