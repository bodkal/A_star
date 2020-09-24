// first update
// Created by koby on 07/09/2020.
//

#include "d_star_lite.h"
#define inf std::numeric_limits<float>::infinity();
#include <stdio.h>

DStarLite::DStarLite(OccupancyGridMap map,short s_start[2],short s_goal[2]):rhs(std::vector<std::vector<float>>(map.y_dim)),sensed_map(map.x_dim,map.x_dim){
        s_last[0]= this->s_start[0]=s_start[0];
        s_last[1]=this->s_start[1]=s_start[1];

        this->s_goal[0]=s_goal[0];
        this->s_goal[1]=s_goal[1];

        for (int i = 0; i < map.y_dim; ++i) {
            rhs[i]=std::vector<float>(map.x_dim);
            for (int j = 0; j < map.x_dim; ++j) {
                this->rhs[i][j]=inf;
            }
        }
        this->g=this->rhs;

    this->rhs[s_goal[0]][s_goal[1]] = 0;

        this->U.insert(s_goal, {ouder::heuristic(s_start,s_goal),0});
    }

    K  DStarLite::calculate_key(short s[2]){
        float k1 = std::min(this->g[s[0]][s[1]], this->rhs[s[0]][s[1]]) + ouder::heuristic(this->s_start,s) + this->k_m;
        float k2 = std::min(this->g[s[0]][s[1]], this->rhs[s[0]][s[1]]);
        return {k1, k2};
    }

    float DStarLite::c(short u[2],short v[2]) {
        if (!this->sensed_map.is_unoccupied(u[0], u[1]) || !this->sensed_map.is_unoccupied(v[0], v[1])) {
            return inf;
        }
        else {
            return ouder::heuristic(u, v);
        }
    }

    bool DStarLite::contain(short u[2]) {
        for (int i = 0; i < this->U.vertices_in_heap.size(); ++i) {
            if(this->U.vertices_in_heap[i][0]==u[0] &&this->U.vertices_in_heap[i][1]==u[1]){
                return true;
            }
                //return  std::count(this->U.vertices_in_heap.begin(), this->U.vertices_in_heap.end(), u);
            }
        return false;
    }

    bool DStarLite::update_vertex(short u[2]){
        if (this->g[u[0]][u[1]] != this->rhs[u[0]][u[1]] &&  this->contain(u)){
            this->U.update(u, this->calculate_key(u));
        }
        else if (this->g[u[0]][u[1]] != this->rhs[u[0]][u[1]] && !this->contain(u)) {
            this->U.insert(u, this->calculate_key(u));
        }
        else if( this->g[u[0]][u[1]] == this->rhs[u[0]][u[1]] && this->contain(u))
            this->U.remove(u);
    }

    bool DStarLite::compute_shortest_path(){
        short tmp[]={-1,-1};
        Vertex u(tmp);
        short * tmp1=u.pos;

        K k_old;
        K k_new;
        float min_s;
        float g_old;
        float temp;
        std::vector <short * > pred;
        while (ouder::lexicographic(this->U.top_key() , this->calculate_key(this->s_start)) || this->rhs[this->s_start[0]][this->s_start[1]] > this->g[this->s_start[0]][this->s_start[1]]){
            u = this->U.top();
            k_old = this->U.top_key();
            k_new = this->calculate_key(u.pos);
            if (ouder::lexicographic(k_old , k_new)){
                this->U.update(u.pos, k_new);
            }
            else if (this->rhs[u.pos[0]][u.pos[1]] < this->g[u.pos[0]][u.pos[1]]){
                this->g[u.pos[0]][u.pos[1]]=this->rhs[u.pos[0]][u.pos[1]];

                this->U.remove(u.pos);

                pred = this->sensed_map.succ(u.pos);
                for (short* const& s:pred){
                    if(s[0]!= this->s_goal[0] ||  s[1]!= this->s_goal[1]){
                        this->rhs[s[0]][s[1]] =std::min(this->rhs[s[0]][s[1]], this->c(s, u.pos) + this->g[u.pos[0]][u.pos[1]]);
                    }

                    this->update_vertex(s);
                }

            }
            else{
                g_old =this->g[u.pos[0]][u.pos[1]];
                this->g[u.pos[0]][u.pos[1]]=inf;
                pred = this->sensed_map.succ(u.pos);
                pred.push_back(u.pos);
                for (short* const& s:pred) {
                    if (this->rhs[s[0]][s[1]] == this->c(s, u.pos) + g_old){
                        if (s[0] !=this->s_goal[0] && s[1] !=this->s_goal[1]){
                            min_s = inf;
                            for (short* const& s_ : this->sensed_map.succ(s)) {
                                temp =this->c(s, s_) + this->g[s_[0]][s_[1]];
                                if (min_s > temp){
                                    min_s = temp;
                                }

                            }
                            this->rhs[s[0]][s[1]] = min_s;

                        }

                    }
                    this->update_vertex(u.pos);

                }
            }
        }
    }

Vertices DStarLite::rescan(){
    Vertices tmp_new_edges_and_old_costs =  this->new_edges_and_old_costs;
    this->new_edges_and_old_costs = Vertices();
    return  tmp_new_edges_and_old_costs;
}
std::vector<short*> DStarLite::move_and_replan(short robot_position[]){
        Vertices changed_edges_with_old_cost;
    std::vector<Vertex> temp_vec;
        short temp_list[2];
        short arg_min[2];
        float min_s;
        float temp;
        short v[2];
        float c_new;
    std::vector<short*> path;
        path.push_back(robot_position);
        this->s_last[0]=this->s_start[0] = robot_position[0];
        this->s_last[1]=this->s_start[1] = robot_position[1];
        this->compute_shortest_path();
        while (this->s_start[0] != this->s_goal[0] || this->s_start[1] != this->s_goal[1]) {
     /*       for (int i = 0; i < 20; ++i) {
                for (int j = 0; j < 20; ++j) {
                    std::cout << "\t" << round(this->g[i][j]);
                }
                std::cout << std::endl;
            }*/
            bool a = this->rhs[this->s_start[0]][this->s_start[1]] == inf;
            if (a) {std::cout << "There is no known path!" << std::endl;}

            min_s = inf;
            for (short* const& s_:this->sensed_map.succ(this->s_start)) {
                temp = this->c(this->s_start, s_) + this->g[s_[0]][s_[1]];
                if (temp <= min_s) {
                    min_s = temp;
                    arg_min[0] = s_[0];
                    arg_min[1] = s_[1];
                }
            }
            this->s_start[0] = arg_min[0];
            this->s_start[1] = arg_min[1];
           // std::cout<<s_start[0]<<","<<s_start[1]<<std::endl;

            //   short * t=new short[2];
          //  short * t{};
            path.push_back(new short[2]{arg_min[0],arg_min[1]});
            changed_edges_with_old_cost = this->rescan();
            if(changed_edges_with_old_cost.get_vertices().size() !=0){
                this->k_m += ouder::heuristic(this->s_last, this->s_start);
                this->s_last[0] = this->s_start[0];
                this->s_last[1] = this->s_start[1];
                temp_vec=changed_edges_with_old_cost.get_vertices();
                for (int i = 0; i < temp_vec.size(); ++i) {

                    v[0] = temp_vec[i].pos[0];
                    v[1] = temp_vec[i].pos[1];


                    for (auto const& items: temp_vec[i].edges_and_c_old) {
                        c_new = this->c(new short [2]{items.first.x,items.first.y}, v);
                        if (items.second > c_new) {
                            if (items.first.x != this->s_goal[0] && items.first.y != this->s_goal[1]) {
                                this->rhs[items.first.x][items.first.y] = std::min(
                                        this->rhs[items.first.x][items.first.y],
                                        this->c(new short [2]{items.first.x,items.first.y}, v) + this->g[v[0]][v[1]]);
                            }
                        }
                            else if(rhs[items.first.x][items.first.y] == items.second + this->g[v[0]][v[1]]){

                                if (items.first.x != this->s_goal[0] && items.first.y != this->s_goal[1]){
                                    min_s =inf;

                                    for (short* const& s_:this->sensed_map.succ(new short [2]{items.first.x,items.first.x})) {
                                        temp_list[0] =items.first.x;
                                        temp_list[1]=items.first.y;
                                        temp = this->c(temp_list, s_) + this->g[s_[0]][s_[1]];
                                        if (min_s > temp){
                                            min_s = temp;
                                        }
                                    }
                                    this->rhs[items.first.x][items.first.y] = min_s;

                                }
                                temp_list[0] =items.first.x;
                                temp_list[1]=items.first.y;
                                this->update_vertex(temp_list);

                            }


                        }

                    }


            }
            this->compute_shortest_path();
        }

    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            std::cout << "\t" << round(this->rhs[j][i]);
        }
        std::cout << std::endl;
    }
    std::cout << "----------------------------------------------"<<std::endl;
        std::cout<<"path found!"<<std::endl;
    for(auto const& i: path){

        std::cout<<i[0]<<","<<i[1]<<std::endl;
    }
        return path;
    }


