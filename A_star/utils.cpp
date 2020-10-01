//
// Created by koby on 01/10/2020.
//

#include "utils.h"
float utils::heuristic(pos p1,pos p2){
    return sqrt(pow(p1.x-p2.x,2)+pow(p1.y-p2.y,2));
}
std::vector<utils::pos> utils::get_movements(pos point){

    std::vector<utils::pos> list={{ 1,  0},{ 0,  1},{- 1,  0},{ 0, - 1},{ 1,   1},{ - 1,   1},{ - 1,  - 1},{ 1,  - 1}};
        for (int i = 0; i < 8; ++i) {
            list[i].x = list[i].x + point.x;
            list[i].y = list[i].y + point.y;
        }
        return list;
}