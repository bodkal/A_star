#include <iostream>
#include "utils.h"
#include "game.h"

int main() {
   game aa=game(player('a'),player('b'));
    aa.print_board();
    return 0;
}
