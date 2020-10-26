//
// Created by koby on 26/10/2020.
//

#ifndef MANCALA_UTILS_H
#define MANCALA_UTILS_H
#include <stdlib.h>
#include <vector>


class cell {
private:
    int stone_number;
public:
    cell(int stone);
    int get();
    void add();
    int take();

};
class player {

private:

public:
    player(char name);
    int bank;

    std::vector<cell> board;

    bool my_turn;
    char name;
};


#endif //MANCALA_UTILS_H
