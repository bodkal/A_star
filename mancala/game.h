//
// Created by koby on 26/10/2020.
//

#ifndef MANCALA_GAME_H
#define MANCALA_GAME_H
#include "utils.h"
#include <iostream>



class game {
private:
public:
    game(player a,player b);
    player a{' '};
    player b{' '};
    void change_turn();
    void print_board();

};


#endif //MANCALA_GAME_H
