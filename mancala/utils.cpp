//
// Created by koby on 26/10/2020.
//

#include "utils.h"

cell::cell(int stone){
    this->stone_number=stone;
}

int cell::get(){
    return this->stone_number;
}

void cell::add(){
    this->stone_number++;
}

int cell::take(){
    int num=this->stone_number;
    this->stone_number=0;
    return num;
}

player::player(char name)
{
    this->name=name;

    for (int i = 0; i < 8; ++i) {
        this->board.push_back(cell(4));
    }
    this->bank=0;
}
