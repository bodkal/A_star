//
// Created by koby on 01/10/2020.
//
#include <matplotlib-cpp/matplotlibcpp.h>

namespace plt = matplotlibcpp;

#include "grid.h"
world::world(short x_size,short y_size,short view){
    this->view=view;

    this->x_dim=x_size;
    this->y_dim=y_size;
    this->maxval=x_size*y_size/10;

    this->new_GridMap = new  float * [y_dim];
    this->old_GridMap = new  float * [y_dim];

    for (short i = 0; i < y_dim; i++) {
        this->new_GridMap[i] = new float [x_dim];
        this->old_GridMap[i] = new float [x_dim];
        for (short j = 0; j < x_dim; j++) {
            this->new_GridMap[i][j] = this->maxval;
            this->old_GridMap[i][j] = this->maxval;
        }
    }

}



bool world::is_unoccupied(struct utils::pos point){
   // return this->GridMap[point.y][point.x].g<utils::inf();
    return this->new_GridMap[point.y][point.x]<utils::inf();

}

bool  world::in_bounds(struct utils::pos point){
return (point.x>=0 && point.x < this->x_dim) && (point.y>=0 && point.y < this->y_dim);
}



bool  world::vesited(utils::pos point){
    //return (this->get_g(point) < maxval);
    return (this->new_GridMap[point.y][point.x] < this->maxval);

}

void world::set_obstacle(struct utils::pos point){
   // this->GridMap[point.y][point.x]={utils::inf(),utils::inf(),utils::inf()};
    this->old_GridMap[point.y][point.x]=utils::inf();

}

float world::get_old_priority(struct utils::pos point){
    return this->old_GridMap[point.y][point.x];
}

float world::get_new_priority(struct utils::pos point){
    return this->new_GridMap[point.y][point.x];
}
void  world::get_all_cells(utils::pos father) {
    this->free_node.clear();
    this->vesit_node.clear();
    utils::pos  point;

    for (utils::pos const  &i:this->move){
        point.x=i.x + father.x;
        point.y=i.y + father.y;
        if (this->in_bounds(point) && this->is_unoccupied(point)) {
            if (!this->vesited(point)) {
                this->free_node.push_back(point);
            }
            else{
                this->vesit_node.push_back(point);
            }
        }
    }
}


void world::set_priority(utils::pos point,utils::pos goal,utils::pos father){
       this->new_GridMap[point.y][point.x]=utils::heuristic(point,father)+this->new_GridMap[father.y][father.x];
}


void world::change_g(utils::pos new_point,float g){
    this->new_GridMap[new_point.y][new_point.x]=g;

}
void world::remove_obstacle(struct utils::pos point){
    this->old_GridMap[point.y][point.x]=this->maxval;

}

void world::print_map(std::vector<utils::pos> path){
   // plt::plot(0, 0,"o");
    std::vector<float> o_x;
    std::vector<float> o_y;

    for (short i = 0; i < this->x_dim; ++i) {
        for (short j = 0; j < this->y_dim; ++j) {
            if(!this->is_unoccupied({i,j})){
                o_x.push_back(i);
                o_y.push_back(j);
            }
            }
        }
    plt::clf();

    plt::subplot(1, 2, 1);
    plt::plot(o_x,o_y,"rs");

    std::vector<float> p_x;
    std::vector<float> p_y;

    for(utils::pos const&i:path){
        p_x.push_back(i.x);
        p_y.push_back(i.y);

    }
    plt::plot(p_x,p_y,"bo");

    std::vector<float> v_x;
    std::vector<float> v_y;

    v_x.push_back( path.back().x+ this->view);
    v_y.push_back( path.back().y+ this->view);
    v_x.push_back(path.back().x- this->view);
    v_y.push_back( path.back().y+ this->view);
    v_x.push_back( path.back().x- this->view);
    v_y.push_back( path.back().y- this->view);
    v_x.push_back( path.back().x+ this->view);
    v_y.push_back( path.back().y- this->view);
    v_x.push_back( path.back().x+ this->view);
    v_y.push_back( path.back().y+ this->view);
    plt::plot(v_x,v_y,"k");

    o_x.clear();
    o_y.clear();
    plt::xlim(0, int(this->x_dim));
    plt::ylim(0, int(this->y_dim));
    plt::subplot(1, 2, 2);
    std::vector<float> o_x1;
    std::vector<float> o_y1;
    for (short i = 0; i < this->x_dim; ++i) {
        for (short j = 0; j < this->y_dim; ++j) {
            if(this->get_old_priority({i,j})==utils::inf()){
                o_x1.push_back(i);
                o_y1.push_back(j);
            }
        }
    }
    plt::plot(p_x,p_y,"bo");
    plt::plot(o_x1,o_y1,"rs");

    v_x.push_back( path.back().x+ this->view);
    v_y.push_back( path.back().y+ this->view);
    v_x.push_back(path.back().x - this->view);
    v_y.push_back( path.back().y+ this->view);
    v_x.push_back( path.back().x- this->view);
    v_y.push_back( path.back().y- this->view);
    v_x.push_back( path.back().x+ this->view);
    v_y.push_back( path.back().y- this->view);
    v_x.push_back( path.back().x+ this->view);
    v_y.push_back( path.back().y+ this->view);
    plt::plot(v_x,v_y,"k");

    plt::xlim(0, int(this->x_dim));
    plt::ylim(0, int(this->y_dim));

    plt::pause(0.01);

    //plt::show();

}




void world::scan_and_reweight(utils::pos point){
    this->remove_world_priority();

    for (short i = 0; i < this->x_dim; ++i) {
        for (short j = 0; j <  this->y_dim; ++j) {
            if(this->is_unoccupied({i,j})){
                this->change_g({i,j}, this->maxval);//remove_obstacle({i,j});
            }
        }
    }
    for (short i = point.x- this->view; i <point.x+ this->view ; ++i) {
        for (short j = point.y-this->view;j < point.y+this->view; ++j) {
            if(this->in_bounds({i,j})) {
                //std::cout << this->get_old_priority({i, j}) << "," << this->get_new_priority({i, j}) << std::endl;
            }
            if(this->in_bounds({i,j}) && this->get_old_priority({i,j})!= this->get_new_priority({i,j})){
                this->change_g({i,j},get_old_priority({i,j}));
            }
        }
    }
    this->change_g(point,0);
};

void world::remove_world_priority(){
for (short i = 0; i < this->x_dim; ++i) {
for (short j = 0; j < this->x_dim; ++j) {
    if(this->is_unoccupied({i,j})){
        this->change_g({i,j},maxval);
    }
}

}
};