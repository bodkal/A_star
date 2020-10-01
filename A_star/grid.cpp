//
// Created by koby on 01/10/2020.
//

#include "grid.h"

world::world(short x_size,short y_size){
    this->x_dim=x_size;
    this->y_dim=y_size;
    GridMap.assign(this->y_dim, std::vector < int >(this->x_dim, 0));
    }



std::vector<std::vector<int>> world::get_map(){
    return this->GridMap;
}
bool world::is_unoccupied(struct utils::pos point){
    return this->GridMap[point.y][point.x]<255;
}

bool  world::in_bounds(struct utils::pos point){
return (point.x>=0 && point.x < this->x_dim) && (point.y>=0 && point.y < this->y_dim);
}

void world::set_obstacle(struct utils::pos point){
    this->GridMap[point.y][point.x]=255;
}

void world::remove_obstacle(struct utils::pos point){
    this->GridMap[point.y][point.x]=0;
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
            std::cout<<this->GridMap[i][j]<<"\t";
        }
        std::cout<<std::endl;
    }
}
