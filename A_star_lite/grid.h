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
    std::vector<std::vector<utils::priority>> GridMap;

public:
    world(short x_size,short y_size);
    utils::priority get_priority(struct utils::pos point);
    void set_priority(utils::pos new_point,utils::pos goal,utils::pos father);
    void change_g(utils::pos new_point,float g);

        std::vector<std::vector<utils::priority>> get_map();
    bool is_unoccupied(struct utils::pos point);
    bool in_bounds(struct utils::pos point);
    void set_obstacle(struct utils::pos point) ;
    void remove_obstacle(struct utils::pos point);
    void print_map();
    bool vesited(utils::pos point);

  //  std::vector <short*> neighbors(utils::pos);


};
/*
class OccupancyGridMap{
private:
    short ** occupancy_grid_map;
    std::vector <short*> filter(short ** neighbors ,bool avoid_obstacles);

public:
    short x_dim;
    short y_dim;
    OccupancyGridMap(short row,short col);
    short ** get_map();
    void set_map( short ** new_ogrid);
    bool is_unoccupied(int row, int col);
    bool in_bounds(int row, int col);
    std::vector <short*> succ(short vertex[2],bool avoid_obstacles=false);

};
*/
#endif //A_STAR_SEARCH_H
