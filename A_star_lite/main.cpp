#include <iostream>
#include "grid.h"

#include  "A_star_lite.h"

#include <matplotlib-cpp/matplotlibcpp.h>

using namespace std;
namespace plt = matplotlibcpp;

using namespace std::chrono;
int main() {

    short x_size = 1000;
    short y_size = 1000;

    utils::pos start = {0, 0};
    utils::pos goal = {900, 560};

    vector<utils::pos> obs;

    for (short i = 0; i <6; ++i) {
        obs.push_back({2, i});
    }
    for (short i = 1; i <7; ++i) {
        obs.push_back({i, 3});
    }
    for (short i = 0; i <300; ++i) {
        obs.push_back({150, i});
    }
    for (short i = 100; i <151; ++i) {
        obs.push_back({i, 300});
    }
    for (short i = 100; i <151; ++i) {
        obs.push_back({i, 4});
    }

    vector<short> x;
    vector<short> y;
    vector<short> x_o;
    vector<short> y_o;
    for (int i = 0; i < obs.size(); ++i) {
    x_o.push_back(obs[i].x);
    y_o.push_back(obs[i].y);
    }

    A_star_lite b(start,goal,world(x_size,y_size),obs);
    auto on = high_resolution_clock::now();
    b.path_search();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(stop - on);
    cout << duration.count() << endl;
    auto on1 = high_resolution_clock::now();

    for(utils::pos const& i:b.get_path()){
        x.push_back(i.x);
        y.push_back(i.y);
    }

    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<seconds>(stop1 - on1);
    cout << duration1.count() << endl;
    plt::plot(x,y,"bs");
    plt::plot(x_o,y_o,"rs");

    plt::show();
    return 0;
}
