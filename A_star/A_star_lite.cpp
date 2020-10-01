//
// Created by koby on 01/10/2020.
//

#include "A_star_lite.h"


A_star_lite::A_star_lite(utils::pos start,utils::pos goal,world board){
    this->board=board;
    this->start=start;
    this->goal=goal;
    this->open_list.push_back({start.x,start.y,0});
}

void A_star_lite::insert(node n){
    int i;
    for ( i = 0; i < open_list.size(); ++i) {
        if(open_list[i].f>n.f)
            break;
    }
    open_list.insert(open_list.begin()+i,n);
}
void A_star_lite::remove(){
    this->open_list.erase(open_list.begin());
}

A_star_lite::node A_star_lite::pop(){
    return this->open_list[0];
}

