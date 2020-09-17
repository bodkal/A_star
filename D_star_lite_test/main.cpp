#include<bits/stdc++.h>
#include "utils.h"
#include "grid.h"
#include "priority_queue.h"
#include "d_star_lite.h"
#define x_dims 20
#define y_dims 20

using namespace std;


void print_game(vector<short*> path,vector<short*> obs,short view_range,short x,short y) {
    char bord[x_dims][y_dims];
    for (int j = 0; j < y_dims; ++j) {
        for (int i = 0; i < x_dims; ++i) {
            bord[i][j]=' ';
        }
    }

    for (short *const &i: path) {
        bord[i[0]][i[1]] = '&';
    }

    for (int i = x-view_range; i <= x+view_range; ++i) {
        if (i < x_dims && i>=0&& y + view_range<y_dims)
            bord[i][y + view_range] = '*';

    }

    for (int i = x-view_range; i < x+view_range; ++i) {
        if (i < x_dims && i>=0&& y - view_range >0)
            bord[i][y - view_range] = '*';

    }

    for (int i = y-view_range; i < y+view_range; ++i) {
        if (i < y_dims && i>=0&&x - view_range>0)
            bord[x - view_range][i] = '*';
    }

    for (int i = y-view_range; i < y+view_range; ++i) {
        if (i < y_dims && i >= 0 && x + view_range<x_dims)
            bord[x + view_range][i] = '*';

    }

    for (short *const &i: obs) {
        bord[i[0]][i[1]] = '#';
    }

    bord[x][y] = '@';

    for (int j = 0; j < x_dims*2+1; ++j) {
        cout << '_';
    }
    cout<<endl;
    for (int j = 0; j < y_dims; ++j) {
        cout<<'|';

        for (int i = 0; i < x_dims; ++i) {
            cout<<bord[i][j]<<' ';
        }
        cout <<'|'<<endl;
    }
    for (int j = 0; j < 20*2+1; ++j) {
        cout << '_';
    }
}
int main()
{

    short x_dim = x_dims;
    short y_dim = y_dims;
    short start[] = {3, 3};
    short goal []= {18, 19};
    short view_range = 5;

    OccupancyGridMap  new_map(x_dim,y_dim);
    OccupancyGridMap  old_map = new_map;

    short new_position[]={start[0],start[1]};
    short last_position[]={start[0],start[1]};

    DStarLite dstar(new_map,start,goal);
    SLAM slam(new_map,view_range) ;
    vector<short*> obs;


    //print_game(path,obs,5,goal[0],goal[1]) ;

    vector<short*> path = dstar.move_and_replan(new_position);

    //  vector<short*> path = dstar.move_and_replan(new_position);

    while (!path.size()){

        new_position[0]=path[0][0];
        new_position[1]=path[0][1];
        dstar.new_edges_and_old_costs=slam.rescan(new_position);
        dstar.sensed_map=slam.slam_map;
        path = dstar.move_and_replan(new_position);
        print_game(path,obs,5,goal[0],goal[1]) ;
    }
    return 0;
}