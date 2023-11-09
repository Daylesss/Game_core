#include "map.h"

EnemyData Enemy::get_enemy_data(){
    return enemy_data;
}

std::string Enemy::get_inp(){
    DWORD start_time = GetTickCount();  // получаем текущее время
    DWORD wait_time = (10 - level + 1)*1000;  // время ожидания в миллисекундах (10 секунд)
    std::string player_inp= " ";

    while(true) {
        if (_kbhit()) { 
            char ch = _getch();
            player_inp += ch;
            std::cout<<ch;
        }

        if (GetTickCount() - start_time > wait_time) {
            std::cout << "\n";
            break;
        }
    }

    return player_inp;
}


void Enemy::die(){
    alive = false;
    std::cout << Obj_name << " has defeated!" << std::endl;
    std::cout << "You won: " << enemy_data.points << " points" << std::endl;
    map_hp = 0;
    Obj_name += " (Killed)";
    enemy_data.name = Obj_name;
    enemy_data.health = 0;
}

std::pair<int, int> Enemy::gen_nums(){
    int c = 1;
    if (enemy_data.boss == true){
        c = 1000;
    }
    else{
        c = 100;
    }

    std::pair<int, int> nums = {(rand() % c), (rand() % c)};
    return nums;
}

void Enemy::decrease_health(int x){
    if (x <= 0){
        return;
    }

    int temp_health = enemy_data.health - x;

    if (temp_health <= 0){
        die();
    }
    else{
        enemy_data.health -= x; 
    }
}

void Enemy::get_enemy_info(){
    std::cout <<"\n" <<Obj_name << ": " << level << "lvl\n";
    std::cout << "Health: " << enemy_data.health << "\n";
    std::cout << "Damage: " << enemy_data.damage << "\n\n";
    std::cout << "Points: " << enemy_data.points << "\n\n";
}


void Enemy::fight(Player *player){
    while (enemy_data.health > 0){
        std::pair<int, int> nums = gen_nums();
        int sum = nums.first + nums.second;
        get_player_info(player);
        get_enemy_info();
        std::cout << "Ready to " << enemy_data.name << " attack" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));

        std::cout << nums.first<<" + "<<nums.second<<" = ";
        
        std::string answer;
        answer = get_inp();

        // std::cout << answer;

        if (answer == (" " + std::to_string(sum))){
            std::cout<<"Cool!" << std::endl;
            decrease_health(player->get_damage());
            std::cout << enemy_data.health;
        }
        else if (answer != " s"){
            std::cout << "Oh no..." << std::endl;
            player->decrease_health(enemy_data.damage);
        }
        else{
            if (player->decrease_mana(1, false)){
                std::cout << "You are using magic!" << std::endl;
                if (player->is_mage()){
                    std::cout << "Your knowledge in magic helps you to attack the "<<Obj_name<<"!" << std::endl;
                    decrease_health(player->get_damage());
                }
                std::this_thread::sleep_for(std::chrono::seconds(2));
                system("cls");
                continue;
            }
            else{
                std::cout << "Oh no..." << std::endl;
                player->decrease_health(enemy_data.damage);
            }
        }

        if (!alive){
            std::cout << "You got " << enemy_data.points << " points\n";
            player->change_points(enemy_data.points);
            std::this_thread::sleep_for(std::chrono::seconds(2));
            break;
        }

        if (!player->is_alive()){
            break;
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
        system("cls");
    }

    if (player->is_alive()){
        std::cout << "You're walking away from the " << Obj_name << std::endl;
    }
    else{
        std::this_thread::sleep_for(std::chrono::seconds(2));
        system("cls");
        std::cout << "Restart program to try again" << std::endl;
    }
}

void Enemy::use(Player *player){

    while (true){
        std::cout<<"---------------------\n"<<"You find a "<<Obj_name<<"!!\n"<<"---------------------\n"<<std::endl;
        std::cout<<"Do you want to fight with him?\n"<<"(Y/N)"<<std::endl;
        std::string choice; 
        std::cin>>choice;
        if (choice == "N"){
            std::cout<<"You're walking away from the "<<Obj_name<<std::endl;
            system("cls");
            return;
        }
        if ((choice!="Y") and (choice!="N")){
            system("cls");
            std::cout<<"Wrong input. Input Y or N"<<std::endl;

            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        if (choice == "Y"){
            system("cls");
            break;
        }
    }
    fight(player);

}