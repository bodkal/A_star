//
// Created by koby on 02/09/2020.
//

#ifndef D_STAR_LITE_TEST_GRID_H
#define D_STAR_LITE_TEST_GRID_H
#include "utils.h"
#include<bits/stdc++.h>


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
    void set_obstacle( short row, short col ) ;
    void remove_obstacle(short row ,short col);
    std::map< key,short> local_observation(short global_position[2],short view_range) ;

    };

class SLAM {
private:
    OccupancyGridMap ground_truth_map{0, 0};
    short view_range;

public:

    OccupancyGridMap slam_map{0, 0};
    struct all{
        OccupancyGridMap tmp_map{0, 0};
        Vertices vertices;
    };
    SLAM(OccupancyGridMap map, short view_range_choice);
    void set_ground_truth_map(OccupancyGridMap gt_map);
    float c(short u[2], short v[2]);
    all rescan(short global_position[2]);
    Vertices update_changed_edge_costs(std::map<key, short> local_grid);


    };
#endif //D_STAR_LITE_TEST_GRID_H
