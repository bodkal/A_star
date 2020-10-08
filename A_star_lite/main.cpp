#include <iostream>
#include "grid.h"

#include  "A_star_lite.h"

#include <matplotlib-cpp/matplotlibcpp.h>

using namespace std;
namespace plt = matplotlibcpp;

using namespace std::chrono;
int main() {
    for (int k = 0; k < 50; ++k) {

    short x_size = 1000;
    short y_size = 1000;

    utils::pos start = {0, 0};
    utils::pos goal = {x_size, y_size};
        goal.x-=1;
        goal.y-=1;

        vector<utils::pos> obs=vector<utils::pos>();


        for (int i = 0; i < x_size ; ++i) {
            short x = rand() % (x_size-1) + 1;
            short y = rand() % (x_size-1) + 1;
            short num = rand() % (x_size-1) + 1;
            for (short i = num; i < num + rand() % (y_size - num) + 1; ++i) {
                obs.push_back({x, i});
            }
            num = rand() %(x_size-1) + 1;
            for (short i = num; i < num + rand() % (x_size - num) + 1; ++i) {
                obs.push_back({i, y});
            }
        }

        vector<short> x;
        vector<short> y;
        vector<short> x_o;
        vector<short> y_o;
        for (int i = 0; i < obs.size(); ++i) {
            x_o.push_back(obs[i].x);
            y_o.push_back(obs[i].y);
        }

        A_star_lite A_star(start, goal, world(x_size, y_size), obs);

        auto on = high_resolution_clock::now();
        A_star.path_search();
        auto stop = high_resolution_clock::now();

        auto duration = duration_cast<milliseconds>(stop - on);
        cout<<k <<"\t"<< duration.count() / 1000.0 << endl;

        auto on1 = high_resolution_clock::now();
        for (utils::pos const &i:A_star.get_path()) {
            x.push_back(i.x);
            y.push_back(i.y);
        }
        auto stop1 = high_resolution_clock::now();

        auto duration1 = duration_cast<milliseconds>(stop1 - on1);
        cout << duration1.count() << endl;
        plt::plot(x,y,"bs");
        plt::plot(x_o,y_o,"rs");

        plt::show();
    }

    return 0;
}
