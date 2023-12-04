#include "Cell.h"


void Cell::explore(Player *player){
    if (done){
        std:: cout << "You've been here before." << std::endl;
        return;
    }

    map_obj->use(player);

    if (!(map_obj->is_alive())){
        done = true;
    }
}

int Cell::get_lvl(){
    return lvl;
}
int Cell::is_done(){
    return done;
}