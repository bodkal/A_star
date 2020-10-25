#include <iostream>
#include "grid.h"

#include  "A_star_lite.h"

#include <matplotlib-cpp/matplotlibcpp.h>
//#define  sizeview 10
using namespace std;
namespace plt = matplotlibcpp;

using namespace std::chrono;
int main() {
    short sizeview=20;
    short x_size = 200;
    short y_size =200;
    utils::pos start = {0, 0};
    utils::pos goal = {x_size, y_size};
    goal.x-=1;
    goal.y-=1;

    vector<utils::pos> obs=vector<utils::pos>();


        A_star_lite A_star(start, goal, world(x_size, y_size,sizeview), obs);
        auto on = high_resolution_clock::now();
        A_star.start_plning();//path_search();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - on);
        cout<< duration.count() / 1000.0 << endl;



    return 0;
}
