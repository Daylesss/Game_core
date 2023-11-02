#include "map.h"

Cell::Cell(int level){
    srand(time(0));

    lvl = level;
    done = rand();
}

int Cell::get_lvl(){
    return lvl;
}
int Cell::is_done(){
    return done;
}