#include <windows.h>
#include <conio.h>
#include <iostream>
#include <ostream>
#include <string>

void get_map(std::pair<int, int> pos, int lvl){
    std::string line_o(lvl +1, '-');
    std::cout << "\n-------------\n";
    for (int i=0; i < (lvl + 1); i++){
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

int main() {
    std::pair<int, int> pos = {2, 3};

    int lvl = 5;

    get_map(pos, lvl);

    return 0;
}