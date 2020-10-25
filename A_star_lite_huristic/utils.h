//
// Created by koby on 01/10/2020.
//

#ifndef D_STAR_LITE_TEST_UTILS_H
#define D_STAR_LITE_TEST_UTILS_H
#include<bits/stdc++.h>


class utils {


public:

    struct pos{
        short x;
        short y;

/*        bool  operator==(const pos &o) const{
            return x == o.x && y == o.y;
        }*/
    };

    struct node{
        short x;
        short y;
        float f;

    };

    /*struct priority{
        float g;
        float h;
        float f;
    };

    struct key{
        short x;
        short y;

        bool  operator==(const key &o) const{
            return x == o.x && y == o.y;
        }

        bool  operator<(const key &o) const{
            return x < o.x || (x == o.x && y < o.y);
        }
    };*/

    static std::vector<pos> list;
    static bool  is_equal_array(short u[2],short v[2]);

    static float inf();
    static bool is_equal(pos u,pos v);

    static float heuristic(pos u,pos v);


    //static utils::pos * get_movements(pos point);
    static std::vector<utils::pos> get_movements(pos point);
};


#endif //A_STAR_SEARCH_H
