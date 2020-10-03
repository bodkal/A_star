//
// Created by koby on 01/10/2020.
//

#include "grid.h"

world::world(short x_size,short y_size){
    this->x_dim=x_size;
    this->y_dim=y_size;
    GridMap.assign(this->y_dim, std::vector < utils::priority >(this->x_dim, {0,0,0}));
    }



std::vector<std::vector<utils::priority>> world::get_map(){
    return this->GridMap;
}
bool world::is_unoccupied(struct utils::pos point){
    return this->GridMap[point.y][point.x].g<255;
}

bool  world::in_bounds(struct utils::pos point){
return (point.x>=0 && point.x < this->x_dim) && (point.y>=0 && point.y < this->y_dim);
}

void world::set_obstacle(struct utils::pos point){
    this->GridMap[point.y][point.x].g=255;
}

utils::priority world::get_priority(struct utils::pos point){
    return this->GridMap[point.y][point.x];
}
void world::set_priority(utils::pos new_point,utils::pos goal,utils::pos father){
    this->GridMap[new_point.y][new_point.x].h=utils::heuristic(new_point,goal);
    this->GridMap[new_point.y][new_point.x].g=utils::heuristic(new_point,father)+this->GridMap[father.y][father.x].g;
    this->GridMap[new_point.y][new_point.x].f= this->GridMap[new_point.y][new_point.x].g+ this->GridMap[new_point.y][new_point.x].h;
}
void world::change_g(utils::pos new_point,float g){
    this->GridMap[new_point.y][new_point.x].g=g;
}
void world::remove_obstacle(struct utils::pos point){
    this->GridMap[point.y][point.x]={0,0,0};
}

void world::print_map(){
    std::cout<<"\t";
    for (int i = 0; i < this->x_dim; ++i) {
        std::cout<<i<<"\t";
    }
    std::cout<<std::endl;
    std::cout<<"\t";

    for (int i = 0; i < this->x_dim; ++i) {
        std::cout<<"_\t";
    }
    std::cout<<std::endl;
        for (int i = 0; i < this->y_dim; ++i) {
            std::cout<<i<<"|\t";
            for (int j = 0; j < this->x_dim; ++j) {
            std::cout<<this->GridMap[i][j].g<<"\t";
        }
        std::cout<<std::endl;
    }
}
