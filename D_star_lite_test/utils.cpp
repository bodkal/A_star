#include "utils.h"
#include<bits/stdc++.h>
    Vertex::Vertex(short pos_chois[2]){//:pos() {
            this->pos[0] = pos_chois[0];
            this->pos[1] = pos_chois[1];
        }

    void Vertex::add_edge_with_cost(short succ[2],float cost){
        if (succ[0] != this->pos[0] &&succ[1] != this->pos[1])
            this->edges_and_costs[{succ[0],succ[1]}] = cost;
    }

    std::map<key,float> Vertex::edges_and_c_old() {
        return this->edges_and_costs;
    }


void  Vertices::add_vertex(Vertex v){
        this->list.push_back(v);
    }

    std::vector<Vertex> Vertices:: get_vertices() {
        return this->list;
    }

    //ouder();
     float ouder::heuristic(short p[2],short q[0]) {
        return sqrt((p[0] - q[0]) *(p[0] - q[0]) + (p[1] - q[1]) *(p[1] - q[1]));
    }

    short ** ouder::get_movements_8n(short x,short y) {

        short list[8][2]={{ 1,  0},{ 0,  1},{- 1,  0},{ 0, - 1},{ 1,   1},{ - 1,   1},{ - 1,  - 1},{ 1,  - 1}};
        short ** array2D= new short *[8];
        for (int i = 0; i < 8; ++i) {
            array2D[i] = new short[2];
            array2D[i][0] = list[i][0] + x;
            array2D[i][1] = list[i][1] + y;
        }

        return array2D;
    }
bool ouder::lexicographic(K first,K secand){
    return first.k1 < secand.k1 || (first.k1 == first.k1 && first.k2 < secand.k2);
}


