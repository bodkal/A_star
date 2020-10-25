//
// Created by koby on 01/10/2020.
//

#include "utils.h"
float utils::heuristic(pos u,pos v){
    return sqrt(pow(u.x-v.x,2)+pow(u.y-v.y,2));
}


std::vector<utils::pos> utils::get_movements(pos point){
//utils::pos * utils::get_movements(utils::pos point){
    std::vector<utils::pos> list = {{ 1,1 }, { 1, -1 }, { -1,1 }, { -1,-1 }, { 1,0 }, { 0, 1 }, { -1,0 }, { 0,-1 } };

    for (int i = 0; i < 8; ++i) {
        list[i].x = list[i].x + point.x;
        list[i].y = list[i].y + point.y;
    }
        return list;
}

bool  utils::is_equal(pos u,pos v){
    return (u.x==v.x && u.y==v.y);
}

bool  utils::is_equal_array(short u[2],short v[2]){
    return (u[0]==v[0] && u[1]==v[1]);
}

float utils::inf(){
    return std::numeric_limits<float>::infinity();
}