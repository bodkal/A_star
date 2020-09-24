#include<bits/stdc++.h>
//#include "utils.h"
#include "grid.h"
#include "priority_queue.h"
#include "d_star_lite.h"
#define x_dims 20
#define y_dims 20

using namespace std;


void print_game(vector<short*> path,vector<pair<short,short>> obs,short view_range,short x,short y) {
    char bord[x_dims][y_dims];
    for (int j = 0; j < y_dims; ++j) {
        for (int i = 0; i < x_dims; ++i) {
            bord[j][i]=' ';
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

    for ( pair<short,short> const &i : obs) {
        bord[i.first][i.second] = '#';
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
    for (int j = 0; j < x_dims*2+1; ++j) {
        cout << '_';
    }
    cout<<endl;
}
int main()
{

    short x_dim = x_dims;
    short y_dim = y_dims;
    short start[] = {3, 3};
    short goal []= {8, 19};
    short view_range = 5;

    OccupancyGridMap  new_map(x_dim,y_dim);
    OccupancyGridMap  old_map = new_map;

    short new_position[]={start[0],start[1]};
    short last_position[]={start[0],start[1]};

    DStarLite dstar(new_map,start,goal);
    SLAM slam(new_map,view_range) ;
    vector<pair<short,short>> obs;


   /* short t[2]={2,5};
    //dstar.sensed_map.set_obstacle(2,5);
    for (int i = 0; i < x_dim; ++i) {
        for (int j = 0; j < y_dim; ++j) {
            cout << "\t" << round(dstar.rhs[i][j]);
        }
        cout <<endl;
    }
    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            cout << "\t" << new_map.get_map()[i][j];
        }
        cout << endl;
    }

*/
    //print_game(path,obs,5,start[0],start[1]) ;
    vector<short*> path = dstar.move_and_replan(new_position);
    new_map.set_obstacle(1, 5);
    new_map.set_obstacle(2, 5);
    new_map.set_obstacle(3, 5);
    new_map.set_obstacle(4, 5);
    obs.push_back({1,5});
    obs.push_back({2,5});
    obs.push_back({3,5});
    obs.push_back({4,5});

    slam.set_ground_truth_map(new_map);
    using namespace std;

    int chois;
    short row;
    short col;
    while (path.size()){
        print_game(path,obs,5,new_position[0],new_position[1]) ;

        cout << "\t1- insert obstical \n\t2- remove obstical \n\t3- move";
        cin >> chois;
        switch(chois) {
            case 1: {
                cout << "insert row col:";
                cin >> row >> col;
                obs.push_back({row,col});
                new_map.set_obstacle(row, col);
                slam.set_ground_truth_map(new_map);
                break;
            }
            case 2: {
                cout << "insert row col:";
                cin >> row >> col;
                for (int i = 0; i < obs.size(); ++i) {
                    if (obs[i].first == row && obs[i].second == col)
                        obs.erase(obs.begin() + i);
                }
                new_map.remove_obstacle(row, col);
                slam.set_ground_truth_map(new_map);
                break;
            }
            case 3:{

            new_position[0] = path[1][0];
            new_position[1] = path[1][1];
            SLAM::all tmp = slam.rescan(new_position);

            dstar.new_edges_and_old_costs = tmp.vertices;
            dstar.sensed_map = tmp.tmp_map;
            path = dstar.move_and_replan(new_position);
            print_game(path, obs, 5, new_position[0], new_position[1]);
                break;}
            default: {
                cout << "wrong input";
            }
        }
    }
    return 0;
}