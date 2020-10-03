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
    };

    struct priority{
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
    };

    static float heuristic(pos u,pos v);
    static std::vector<pos>get_movements(pos point);
};


#endif //A_STAR_SEARCH_H
