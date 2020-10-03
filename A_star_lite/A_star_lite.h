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
   /* struct node{
        short x;
        short y;
        float f;
    };*/
    std::vector<utils::pos> open_list;
public:
    world board{0,0};
    std::vector<utils::pos> get_all_cells(utils::pos father);
    A_star_lite(utils::pos start,utils::pos goal,world board,std::vector<utils::pos> obs);
    void sort_and_insert_to_open_list(utils::pos point);
    void remove();
    utils::pos pop();
    std::vector<utils::pos> filtered_move(utils::pos father);
    void print();
    void path_search();
};


#endif //A_STAR_SEARCH_H

