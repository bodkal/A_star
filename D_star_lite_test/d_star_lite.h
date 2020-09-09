//
// Created by koby on 07/09/2020.
//
#include "utils.h"
#include "grid.h"
#include "priority_queue.h"

#ifndef D_STAR_LITE_TEST_D_STAR_LITE_H
#define D_STAR_LITE_TEST_D_STAR_LITE_H


class DStarLite {
public:
    short s_start[2];
    short s_goal[2];
    short s_last[2];
    float  k_m = 0;
    PriorityQueue U;
    std::vector<std::vector<float>> rhs;
    std::vector<std::vector<float>> g;
    OccupancyGridMap sensed_map{0, 0};
    Vertices new_edges_and_old_costs;
    DStarLite(OccupancyGridMap map,short s_start[2],short s_goal[2]);
    K  calculate_key(short s[2]);
    float c(short u[2],short v[2]);
    bool contain(short u[2]);
    bool update_vertex(short u[2]);
    bool compute_shortest_path();
    Vertices rescan();
    std::vector<short*> move_and_replan(short robot_position[]);
    };


#endif //D_STAR_LITE_TEST_D_STAR_LITE_H
