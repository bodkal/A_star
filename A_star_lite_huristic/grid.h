//
// Created by koby on 01/10/2020.
//

#ifndef D_STAR_LITE_TEST_GRID_H
#define D_STAR_LITE_TEST_GRID_H
#include<bits/stdc++.h>
#include "utils.h"



class world {
private:
    short x_dim;
    short y_dim;
    float ** old_GridMap;
    float ** new_GridMap;
   // float ** slam_GridMap;
    short view;
    void remove_world_priority();

public:
    float maxval;

    world(short x_size,short y_size,short view);
    std::vector<utils::pos> free_node;
    std::vector<utils::pos> vesit_node;
    utils::pos move[8]= {{ 1,1 }, { 1, -1 }, { -1,1 }, { -1,-1 }, { 1,0 }, { 0, 1 }, { -1,0 }, { 0,-1 } };
    void get_all_cells(utils::pos father);
    float get_old_priority(struct utils::pos point);
    float get_new_priority(struct utils::pos point);

    void set_priority(utils::pos new_point,utils::pos goal,utils::pos father);
    void change_g(utils::pos new_point,float g);

    bool is_unoccupied(struct utils::pos point);
    bool in_bounds(struct utils::pos point);
    void set_obstacle(struct utils::pos point) ;
    void remove_obstacle(struct utils::pos point);
    void print_map(std::vector<utils::pos> path);
    bool vesited(utils::pos point);
    void scan_and_reweight(utils::pos point);


};



#endif //A_STAR_SEARCH_H
