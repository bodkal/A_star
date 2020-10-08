//
// Created by koby on 01/10/2020.
//

#include "A_star_lite.h"


A_star_lite::A_star_lite(utils::pos start,utils::pos goal,world board, std::vector<utils::pos> obs){
    this->board=board;
    this->start=start;
    this->goal=goal;
    this->open_list.push_back(start);
    this->board.set_priority(start,goal,start);
    this->board.change_g(start,0);

    for(utils::pos const &pos:obs){
        this->board.set_obstacle(pos);
    }
}
void A_star_lite::print() {
    this->board.print_map();
}

void A_star_lite::sort_and_insert_to_open_list(utils::pos point){

    int i;
    float temp_f=this->board.get_f(point);

    for ( i = 0; i < open_list.size(); ++i) {
        if(board.get_f(open_list[i])>temp_f)
            break;
    }
    open_list.insert(open_list.begin()+i,point);

}

void A_star_lite::remove_form_open_list(){
    this->open_list.erase(open_list.begin());
}


void A_star_lite::get_all_cells(utils::pos father) {
    this->free_node.clear();
    this->vesit_node.clear();

    for (utils::pos const &point:utils::get_movements(father)) {

        if (this->board.in_bounds(point) && this->board.is_unoccupied(point)) {
            if (!this->board.vesited(point)) {
                this->free_node.push_back(point);
            }
            else{
                this->vesit_node.push_back(point);
            }
        }
    }
}

bool A_star_lite::father_check(utils::pos u,utils::pos v){
return  this->board.get_g(u) >this->board.get_g(v) + utils::heuristic(u, v);
};

 /*   std::vector<utils::pos> A_star_lite::filtered_move(utils::pos father) {
        std::vector<utils::pos> list = utils::get_movements(father);
        for (int i = list.size() - 1; i > -1; --i) {
            if (!this->board.in_bounds(list[i])) {
                list.erase(list.begin() + i);
            } else if (this->board.vesited(list[i])) {
                list.erase(list.begin() + i);
            }
         else if (!this->board.is_unoccupied(list[i])) {
            list.erase(list.begin() + i);
        }
        }
        return list;
    }*/

    void A_star_lite::path_search() {
        while (this->open_list.size()){// && (this->pop().x!= this->goal.x||this->pop().y!= this->goal.y)) {
            //this->print();

            utils::pos father = this->open_list.front();
            if(utils::is_equal(father, this->goal)){
                std::cout<<"find path"<<std::endl;
                return;
            }
            this->remove_form_open_list();
            this->get_all_cells(father);

            for (utils::pos const &g_improve:this->vesit_node){
                if (father_check(g_improve,father)){
                    this->board.change_g(g_improve,
                                         this->board.get_g(father) + utils::heuristic(g_improve, father));
                }
            }
            for (utils::pos const &new_pos:this->free_node) {
                this->board.set_priority(new_pos, this->goal, father);
                this->sort_and_insert_to_open_list(new_pos);
            }
    }
        std::cout<<"no path"<<std::endl;

    }
std::vector<utils::pos> A_star_lite::get_path(){
    utils::pos cell=this->goal;
    utils::pos tmp= {0,0};
    float minf=10000;
    float temp_g;
    std::vector<utils::pos> path;
    path.push_back(cell);
        while(!utils::is_equal(cell, this->start)){
            minf=10000;
            for(utils::pos const & i:utils::get_movements(cell)){
                if(this->board.in_bounds(i) ){
                    //std::cout<<i.x<<","<<i.y<<"\t\t"<<this->board.get_priority(i).g<<std::endl;

                    if(this->board.is_unoccupied(i)) {
                        temp_g=this->board.get_g(i);
                        if ( temp_g< minf) {
                            minf = temp_g;
                            tmp = i;
                        }
                    }
                    if(utils::is_equal(i, this->start)){
                        path.push_back(i);
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
