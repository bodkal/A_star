//
// Created by koby on 26/10/2020.
//

#include "game.h"

game::game(player a,player b) {
    this->a = a;
    this->b = b;

    if ((std::rand() % 2 + 1) % 2) {
        std::cout << "coin is ood player " << a.name << " go farst" << std::endl;
        a.my_turn = true;
        b.my_turn = false;

    } else {
        std::cout << "coin is double player " << b.name << " go farst" << std::endl;
        a.my_turn = false;
        b.my_turn = true;
    }
}

void game::change_turn(){
if(this->a.my_turn) {
    a.my_turn = false;
    b.my_turn = true;
    std::cout << "player " << b.name << " turn" << std::endl;
}
else {
    a.my_turn = true;
    b.my_turn = false;
    std::cout << "player " << a.name << " turn" << std::endl;
}
};

void game::print_board(){
    std::cout<<"\t";
    for (int i = 0; i < 8; ++i) {
        std::cout<<a.board[i].get()<<' ';
    }
    std::cout<<' '<<std::endl;
    std::cout<<a.bank<<"\t---------------\t"<<b.bank<<std::endl<<"\t";

    for (int i = 0; i < 8; ++i) {
        std::cout<<b.board[i].get()<<' ';
    }
    std::cout<<std::endl;

}

