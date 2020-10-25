//
// Created by koby on 01/10/2020.
//convert from stract to array improve time

#include "A_star_lite.h"


A_star_lite::A_star_lite(utils::pos start,utils::pos goal,world board, std::vector<utils::pos> obs){
    this->board=board;
    this->view= 10;
    this->start=start;
    this->goal=goal;
    this->obs=obs;
   // this->open_list.push_back({start.x,start.y,0});
   // this->board.set_priority(start,goal,start);
   // this->board.change_g(start,0);

    for(utils::pos const &pos:this->obs){
        this->board.set_obstacle(pos);
    }
    //std::vector<utils::pos> move = {{ 1,1 }, { 1, -1 }, { -1,1 }, { -1,-1 }, { 1,0 }, { 0, 1 }, { -1,0 }, { 0,-1 } };

}

void  A_star_lite::start_plning(){

    //utils::pos view[5]={{sizeview,sizeview},{sizeview,-sizeview},{-sizeview,-sizeview},{-sizeview,sizeview},{sizeview,sizeview}};
    std::vector<short> x;
    std::vector<short> y;
    std::vector<short> x_o;
    std::vector<short> y_o;
    while (this->start.x!= this->goal.x&&this->start.y!= this->goal.y) {

        for (int i = 0; i < 1 ; ++i) {
            short x = rand() % (199) + 1;
            short y = rand() % (199) + 1;
            short num = rand() % (199) + 1;
            for (short i = num; i < num + rand() % (200 - num) + 1; ++i) {
                this->obs.push_back({x, i});
                this->board.set_obstacle(this->obs.back());

            }
            num = rand() %(199) + 1;
            for (short i = num; i < num + rand() % (200 - num) + 1; ++i) {
                this->obs.push_back({i, y});
                this->board.set_obstacle(this->obs.back());
            }
        }

        this->board.scan_and_reweight(this->start);
        this->board.change_g(this->start,0);
        this->path_search();
        std::vector<utils::pos> path=this->get_path();
        this->board.print_map(path);
        this->start=path[path.size()-2];//{x[x.size()-2],y[y.size()-2]}; //this->get_path().back();
    }
}
void A_star_lite::sort_and_insert_to_open_list(utils::pos point){
   static float f;
    int i;
    if(this->slam_in_bounds(point)) {
         f = utils::heuristic(point, goal) + this->board.get_new_priority(point);
    } else{
         f = utils::heuristic(point, goal) + this->board.maxval;
    }

    for ( i = 0; i < open_list.size(); ++i) {
        if(open_list[i].f>f)
            break;
    }
    open_list.insert(open_list.begin()+i,{point.x,point.y,f});

}

void A_star_lite::remove_form_open_list(){
    this->open_list.erase(open_list.begin());
}


bool A_star_lite::father_check(utils::pos u,utils::pos v){
//return  this->board.get_g(u) >this->board.get_g(v) + utils::heuristic(u, v);
    return  this->board.get_new_priority(u) >this->board.get_new_priority(v) + utils::heuristic(u, v);

};


utils::pos A_star_lite::get_father(){
    return {this->open_list[0].x,this->open_list[0].y};
}

    void A_star_lite::path_search() {
    utils::pos father;
        this->open_list.clear();
        this->open_list.push_back({this->start.x,this->start.y,0});

        while (this->open_list.size()){

            father= this->get_father();
            this->remove_form_open_list();

            if(utils::is_equal(father, this->goal)){
                //std::cout<<"find path"<<std::endl;
                return;
            }

            this->board.get_all_cells(father);

            for (utils::pos const &g_improve:this->board.vesit_node){

                if (father_check(g_improve,father)){
                    this->board.change_g(g_improve,
                                         this->board.get_new_priority(father) + utils::heuristic(g_improve, father));
                }
            }
            for (utils::pos const &new_pos:this->board.free_node) {
                this->board.set_priority(new_pos, this->goal, father);
                this->sort_and_insert_to_open_list(new_pos);
            }
    }
        std::cout<<"no path"<<std::endl;

    }


std::vector<utils::pos> A_star_lite::get_path(){
    utils::pos cell=this->goal;
    utils::pos tmp= {0,0};
    float minf;
    float temp_g;
    std::vector<utils::pos> path;
    path.push_back(cell);

    while(!utils::is_equal(cell, this->start)){

        minf=10000.0;

        for(utils::pos const & i:utils::get_movements(cell)){

                if(this->board.in_bounds(i) ){
                    //std::cout<<i.x<<","<<i.y<<"\t\t"<<this->board.get_new_priority(i)<<std::endl;

                    if(this->board.is_unoccupied(i)) {
                        temp_g=this->board.get_new_priority(i);

                        if ( temp_g< minf) {
                            minf = temp_g;
                            tmp = i;
                        }
                    }

                    if(utils::is_equal(i, this->start)){//utils::is_equal(i, this->start)){
                        //path.push_back(i);
                        tmp=i;
                        break;
                    }
                }
            }
            //std::cout<<"->"<<tmp.x<<","<<tmp.y<<"\t\t"<<this->board.get_priority(tmp).g<<std::endl;
            cell=tmp;
            path.push_back(cell);
        }
    return path;
    }
bool  A_star_lite::slam_in_bounds(struct utils::pos point){
    return (point.x>= this->start.x - this->view && point.x < this->start.x+ this->view) && (point.y>=this->start.y - this->view && point.y < this->start.y+this->view);
}