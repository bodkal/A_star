
#include "grid.h"
#include "utils.h"

#define OBSTACLE  255
#define UNOCCUPIED  0

//---------------class OccupancyGridMap-------------------------
    std::vector <short*> OccupancyGridMap::filter(short ** neighbors ,bool avoid_obstacles){
        std::vector <short*> good_neighbors;
        if (avoid_obstacles){
            for (int i = 0; i < 8; ++i) {
                if (this->in_bounds(neighbors[i][0],neighbors[i][0])&& this->is_unoccupied(neighbors[i][0],neighbors[i][0]))
                    good_neighbors.push_back(neighbors[i]);
            }
            return good_neighbors;
        }
        for (int i = 0; i < 8; ++i) {
            if (this->in_bounds(neighbors[i][0],neighbors[i][0]))
                good_neighbors.push_back(neighbors[i]);
        }
        return good_neighbors;
    }

    OccupancyGridMap::OccupancyGridMap(short row,short col) {
        x_dim= row;
        y_dim = col;
        short map_extents[2] = {row,col};
        occupancy_grid_map = new short* [row];
        for (int i = 0; i < row; ++i) {
            occupancy_grid_map[i] = new short[col];
        }
        std::vector<short [2]> visited ;

    }

    short ** OccupancyGridMap::get_map(){
        return this->occupancy_grid_map;
    }

    void OccupancyGridMap::set_map( short ** new_ogrid) {
        this->occupancy_grid_map = new_ogrid;
    }

    bool OccupancyGridMap::is_unoccupied(int row, int col){
        return this->occupancy_grid_map[row][col] == UNOCCUPIED;

    }

    bool OccupancyGridMap::in_bounds(int row, int col){
        return 0 <= row &&row < this->x_dim && 0 <= col &&col< this->y_dim;
    }

    std::vector <short*> OccupancyGridMap::succ(short vertex[2],bool avoid_obstacles) {
        int x= vertex[0];
        int y= vertex[1];

        short ** movements=ouder::get_movements_8n(x,y);

        //  if ((x + y) % 2 == 0){
        //     movements.reverse()}

        std::vector <short*> filtered_movements = this->filter(movements,avoid_obstacles);
        return filtered_movements;

    }

    void OccupancyGridMap::set_obstacle( short row, short col ) {
        this->occupancy_grid_map[row][col] = OBSTACLE;
    }

    void OccupancyGridMap::remove_obstacle(short row ,short col) {
        this->occupancy_grid_map[row][col]  = UNOCCUPIED;
    }

    //  map< array<short, 2>,short> local_observation(short global_position[2],short view_range = 2) {
    std::map< key,short> OccupancyGridMap::local_observation(short global_position[2],short view_range ) {

        std::map< key, short> nodes;
        short px = global_position[0];
        short py = global_position[1];

        // array<short, 2> tmp={0,0};

        for (short x = px - view_range; x <  px + view_range + 1; ++x) {
            for (short y = py - view_range; y < py + view_range + 1; ++y) {
                if(this->in_bounds(x,y)){
                    //tmp[0]=x;
                    // tmp[1]=y;
                    nodes[{x,y}]=(1-this->is_unoccupied(x,y))*255;
                }
            }
        }
        return nodes;
    }


//---------------class SLAM-------------------------

    SLAM::SLAM(OccupancyGridMap map, short view_range_choice) {
        ground_truth_map = map;
        slam_map = OccupancyGridMap(map.x_dim, map.y_dim);
        view_range = view_range_choice;
    }

    void SLAM::set_ground_truth_map(OccupancyGridMap gt_map) {
        this->ground_truth_map = gt_map;
    }

    float  SLAM::c(short u[2], short v[2]) {
        if (this->slam_map.is_unoccupied(u[0], u[1]) || !slam_map.is_unoccupied(v[0], v[1]))
            return std::numeric_limits<float>::infinity();
        else
            return ouder::heuristic(u, v);
    }

    Vertices SLAM::update_changed_edge_costs(std::map<key, short> local_grid) {
        short tmp[2];
        Vertices vertices;
        for (auto const &i:local_grid) {
            if (i.second == OBSTACLE) {
                if (this->slam_map.is_unoccupied(i.first.x, i.first.y)) {
                    tmp[1] = i.first.y;
                    tmp[0] = i.first.x;
                    Vertex v(tmp);
                    std::vector<short *> succ = this->slam_map.succ(tmp);
                    for (auto const &u:succ) {
                        v.add_edge_with_cost(u, this->c(u, v.pos));
                    }
                    vertices.add_vertex(v);
                    this->slam_map.set_obstacle(i.first.x, i.first.y);
                }
            } else {
                if (!this->slam_map.is_unoccupied(i.first.x, i.first.y)) {
                    tmp[1] = i.first.y;
                    tmp[0] = i.first.x;
                    Vertex v(tmp);
                    std::vector<short *> succ = this->slam_map.succ(tmp);
                    for (auto const &u:succ) {
                        v.add_edge_with_cost(u, this->c(u, v.pos));
                    }
                    vertices.add_vertex(v);
                    this->slam_map.remove_obstacle(i.first.x, i.first.y);
                }
            }
        }
        return vertices;
    }
