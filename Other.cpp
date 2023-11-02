
#include "map.h"

ItemData::ItemData(){
        for (int i=0; i<5; i++){
            data[i] = 0;
        }
}

char get_input(){
    while(true) {
        if (_kbhit()) { 
            char ch = _getch();
            if ((ch=='w') or (ch=='a') or (ch=='s') or (ch=='d')){
                return ch;
            }
        }
    }
}

void explore_map(Player &player, Map &map){
    while(true){
    char side = get_input();
    if (side == 'w'){
        if(!player.go_up(map)){
            continue;
        }
    }
    if (side == 'a'){
        if(!player.go_left(map)){
            continue;
        }
    }
    if (side == 's'){
        if(!player.go_down(map)){
            continue;
        }
    }
    if (side == 'd'){
            if(!player.go_right(map)){
                continue;
            }
    }
    map.explore(player);
    }
}