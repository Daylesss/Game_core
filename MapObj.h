#pragma(once)
class Player;
class MapObj {
    protected:
        int level = 0;
        std::string Obj_name = "Unknown";
        bool alive = false;
        int map_hp = 0;

        class WrongInput {};
        class NegativeHealth {};

    public:

        MapObj(int lvl);
        int get_lvl();
        std::string get_name();
        int get_map_hp();
        bool is_alive();
        virtual void decrease_map_hp();
        virtual void use(Player *player);
};