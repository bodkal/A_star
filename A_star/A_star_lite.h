//
// Created by koby on 01/10/2020.
//

#ifndef A_STAR_A_STAR_LITE_H
#define A_STAR_A_STAR_LITE_H

#include "utils.h"
#include "grid.h"

class A_star_lite {
private:
    utils::pos start;
    utils::pos goal;
    world board{0,0};
    struct node{
        short x;
        short y;
        float f;
    };
    std::vector<node> open_list;
public:
    A_star_lite(utils::pos start,utils::pos goal,world board);
    void insert(node n);
    void remove();
    node pop();


};


#endif //A_STAR_SEARCH_H

