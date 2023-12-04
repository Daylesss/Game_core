
#include "Other.h"

ItemData::ItemData(){
        for (int i=0; i<5; i++){
            data[i] = 0;
        }
}

char get_input(){
    // while(true) {
    //     if (_kbhit()) { 
    //         char ch = _getch();
    //         if ((ch=='w') or (ch=='a') or (ch=='s') or (ch=='d')){
    //             return ch;
    //         }
    //     }
    // }
    while (true){
        char ch = '0';
        ch << std::cin;
        if ((ch=='w') or (ch=='a') or (ch=='s') or (ch=='d')){
            return ch;
    }
    
}

void get_map(std::pair<int, int> pos, int lvl){
    std::string line_o(lvl +1, '-');
    std::cout << "MAP:\n";
    std::cout << "\n-------------\n";
    for (int i = lvl; i >= 0; i--){
        if (i == pos.second){
            line_o[pos.first] = '0';
            std::cout << line_o << std::endl;
            line_o[pos.first] = '-';
        }
        else{
        std::cout << line_o << std::endl;
        }
    }
    std::cout << "-------------\n";
}

void get_player_info(Player *player){
    std::cout << player->get_name() << ": " << player->get_lvl() << " lvl\n";
    std::cout << "Health: " <<player->get_health() << "/" << player->get_max_health() << " lvl\n";
    std::cout << "Mana: " <<player->get_mana() << "/" << player->get_max_mana() << " lvl\n";
    std::cout << "Damage: " <<player->get_damage() << "\n\n";
    std::cout << "Points: " <<player->get_points() << "\n\n";
}

void explore_map(Player *player, Map &map){
    while(true){
    get_player_info(player);
    get_map(player->get_position(), map.get_level());
    char side = get_input();
    if (side == 'w'){
        if(!player->go_up(map)){
            continue;
        }
    }
    else if (side == 'a'){
        if(!player->go_left(map)){
            continue;
        }
    }
    else if (side == 's'){
        if(!player->go_down(map)){
            continue;
        }
    }
    else if (side == 'd'){
            if(!player->go_right(map)){
                continue;
            }
    }
    else{
        std::cout << "Wrong button\n" << std::endl;
    }
    map.explore(player);
    }
}

Player * choose_class(){
    while (true){
    std::cout << "Input number of your class: \n";
    std::cout << "0 - villager\n";
    std::cout << "1 - Mage\n";
    std::cout << "2 - Shadow\n";
    std::cout << "3 - Werewolf\n";
    char pl_class;
    std::cin >> pl_class;
    if (pl_class == '0'){
        Player * player = new Player(1, "TEST");
        system("cls");
        return player;
    }
    if (pl_class == '1'){
        Mage * player_class = new Mage(1, "TEST");
        Player * player = player_class;
        system("cls");
        return player;
    }
    if (pl_class == '2'){
        Shadow * player_class = new Shadow(1, "TEST");
        Player * player = player_class;
        system("cls");
        return player;
    }
    if (pl_class == '3'){
        Werewolf * player_class = new Werewolf(1, "TEST");
        Player * player = player_class;
        system("cls");
        return player;
    }
    else{
        std::cout << "Input only one number!";
        std::this_thread::sleep_for(std::chrono::seconds(2));
        system("cls");
    }
    }
}