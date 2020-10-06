//
// Created by koby on 01/10/2020.
//

#include "grid.h"
#define maxval 9999
world::world(short x_size,short y_size){
    this->x_dim=x_size;
    this->y_dim=y_size;
    GridMap.assign(this->y_dim, std::vector < utils::priority >(this->x_dim, {maxval,maxval,maxval}));
    }



std::vector<std::vector<utils::priority>> world::get_map(){
    return this->GridMap;
}
bool world::is_unoccupied(struct utils::pos point){
    return this->GridMap[point.y][point.x].g<utils::inf();
}

bool  world::in_bounds(struct utils::pos point){
return (point.x>=0 && point.x < this->x_dim) && (point.y>=0 && point.y < this->y_dim);
}

bool  world::vesited(utils::pos point){
    return !(this->get_priority({point.x, point.y}).g == maxval);
}

void world::set_obstacle(struct utils::pos point){
    this->GridMap[point.y][point.x]={utils::inf(),utils::inf(),utils::inf()};
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
    this->GridMap[point.y][point.x]={maxval,maxval,maxval};
}

void world::print_map(){
    std::cout<<"\t\t";
    for (int i = 0; i < this->x_dim; ++i) {
        std::cout<<i<<"\t\t";
    }
    std::cout<<std::endl;
    std::cout<<"\t\t";

    for (int i = 0; i < this->x_dim; ++i) {
        std::cout<<"_\t";
    }
    std::cout<<std::endl;
        for (int i = 0; i < this->y_dim; ++i) {
            std::cout<<i<<"|\t";
            for (int j = 0; j < this->x_dim; ++j) {
                if(this->GridMap[i][j].f<10)
                    std::cout<<truncf(this->GridMap[i][j].f*10)/10<<" \t";
                else
                std::cout<<truncf(this->GridMap[i][j].f*10)/10<<"\t";
        }
        std::cout<<std::endl;
    }
}
