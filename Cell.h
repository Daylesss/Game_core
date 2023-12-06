// #include "Player.h"
// #include "Enemy.h"
// #include "Altar.h"
// #include "Item.h"

// #pragma(once)
// #include "map.h"

// class Cell{
//     friend Map;
//     int lvl = 1;
//     int done = 0;
//     std::unique_ptr<MapObj> map_obj;

//     void explore(Player *player);
//     public:
//         Cell(int level){
//             lvl = level;

//             int key = rand() % 3;

//             if (key == 0){
//                 map_obj = std::make_unique<Altar>(lvl);
//             }
//             else if (key == 1){
//                 map_obj = std::make_unique<Item>(lvl);
//             }
//             else{
//                 map_obj = std::make_unique<Enemy>(lvl);
//             }
//         }  
//         int get_lvl();
//         int is_done();
// };