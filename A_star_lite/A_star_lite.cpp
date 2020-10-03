//
// Created by koby on 01/10/2020.
//

#include "A_star_lite.h"


A_star_lite::A_star_lite(utils::pos start,utils::pos goal,world board, std::vector<utils::pos> obs){
    this->board=board;
    this->start=start;
    this->goal=goal;
    this->open_list.push_back({start.x,start.y});

    for(utils::pos const &pos:obs){
        this->board.set_obstacle(pos);
    }
}
void A_star_lite::print() {

    this->board.print_map();
}

void A_star_lite::sort_and_insert_to_open_list(utils::pos point){
    int i;
    for ( i = 0; i < open_list.size(); ++i) {
        if(board.get_priority(open_list[i]).f>this->board.get_priority(point).f)
            break;
    }
    open_list.insert(open_list.begin()+i,point);
}

void A_star_lite::remove(){
    this->open_list.erase(open_list.begin());
}

utils::pos A_star_lite::pop(){
    return this->open_list[0];
}

std::vector<utils::pos> A_star_lite::get_all_cells(utils::pos father) {
    std::vector<utils::pos> list = utils::get_movements(father);

    for (int i = list.size() - 1; i > -1; --i) {
        if (!this->board.in_bounds({list[i].x, list[i].y})) {
            list.erase(list.begin() + i);
        } else if (this->board.get_priority({list[i].x, list[i].y}).g == 0 ||
                   this->board.get_priority({list[i].x, list[i].y}).g == 255) {
            list.erase(list.begin() + i);
        }
    }
        return list;
    }
    std::vector<utils::pos> A_star_lite::filtered_move(utils::pos father) {
        std::vector<utils::pos> list = utils::get_movements(father);
        for (int i = list.size() - 1; i > -1; --i) {
            if (!this->board.in_bounds({list[i].x, list[i].y})) {
                list.erase(list.begin() + i);
            } else if (this->board.get_priority({list[i].x, list[i].y}).g > 0) {
                list.erase(list.begin() + i);
            }

        }

        return list;
    }

    void A_star_lite::path_search() {
        while (this->open_list.size() || (this->pop().x!= this->goal.x||this->pop().y!= this->goal.y)) {
            utils::pos father = this->pop();
            this->remove();
            for (utils::pos const &new_pos:this->filtered_move(father)) {
                this->board.set_priority(new_pos, this->goal, father);
                for (utils::pos const &i:this->get_all_cells(new_pos)) {
                    if (this->board.get_priority(new_pos).g >
                        this->board.get_priority(i).g + utils::heuristic(new_pos, i)) {
                        this->board.change_g(new_pos,
                                             this->board.get_priority(new_pos).g + utils::heuristic(new_pos, i));
                    }
                }
                this->sort_and_insert_to_open_list(new_pos);
                this->print();
            }
        }
    }


