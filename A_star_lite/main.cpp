#include <iostream>
#include "grid.h"
#include "A_star_lite.h"

using namespace std;
int main() {
    short x_size=10;
    short y_size=10;

    utils::pos start={0,0};
    utils::pos goal={5,5};

    vector<utils::pos> obs;
   // obs.push_back({1,2});
    //obs.push_back({1,3});
    A_star_lite b(start,goal,world(x_size,y_size),obs);
    b.path_search();
    return 0;
}
