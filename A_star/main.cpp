#include <iostream>
#include "grid.h"
#include "A_star_lite.h"

using namespace std;
int main() {
    short x_size=10;
    short y_size=10;

    utils::pos start={0,0};
    utils::pos goal={1,1};

    world borad(x_size,y_size);
    A_star_lite b(start,goal,borad);

    borad.set_obstacle({0,0});
    borad.print_map();
    return 0;
}
