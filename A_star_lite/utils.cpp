//
// Created by koby on 01/10/2020.
//

#include "utils.h"
float utils::heuristic(pos u,pos v){
    return sqrt(pow(u.x-v.x,2)+pow(u.y-v.y,2));
}

std::vector<utils::pos> utils::get_movements(pos point){

    std::vector<utils::pos> list={{ 1,  0},{ 0,  1},{- 1,  0},{ 0, - 1},{ 1,   1},{ - 1,   1},{ - 1,  - 1},{ 1,  - 1}};
        for (int i = 0; i < 8; ++i) {
            list[i].x = list[i].x + point.x;
            list[i].y = list[i].y + point.y;
        }
        return list;
}