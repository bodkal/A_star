#include<bits/stdc++.h>
#include "utils.h"
#include "grid.h"
#include "priority_queue.h"
#include "d_star_lite.h"

using namespace std;


int main()
{
    // Create a graph given in the above diagram
    OccupancyGridMap mapp(5,6) ;
    short g[]={0,0};
    DStarLite f(mapp,g,g);
    SLAM s(mapp,5);
    Priority p(5,6);
    PriorityNode p1();
    PriorityQueue pp;
    short vertex1[2];//{4,4};
    pp.insert(vertex1,{p.k1,p.k2});

    mapp.set_obstacle(10,11);
    short a[]={11,11};

       map<key,short>b=mapp.local_observation(a,5);
       s.update_changed_edge_costs(b);


       for (short i = 6; i <  17; ++i) {
           for (short j = 6; j < 17; ++j) {
               cout<<i<<","<<j<<"\t"<<b[{i,j}]<<endl;
           }
       }
    return 0;
}