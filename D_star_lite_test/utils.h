#ifndef D_STAR_LITE_TEST_UTILS_H
#define D_STAR_LITE_TEST_UTILS_H
#include<bits/stdc++.h>

struct K{float k1;float k2;};
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

class Vertex{
private:
    std::map<key,float>edges_and_costs;
public:
    short pos[2];
    Vertex(short pos_chois[2]);
    void add_edge_with_cost(short succ[2],float cost);
    std::map<key,float> edges_and_c_old() ;

    };

class Vertices{
    std::vector<Vertex>list;
public:
   // Vertices();
    void add_vertex(Vertex v);
    std::vector<Vertex> get_vertices();

};

class ouder {
public:
    ouder();
    static float heuristic(short p[2], short q[0]);
    static short ** get_movements_8n(short x,short y);
    static bool lexicographic(K first,K secand);
};
#endif //D_STAR_LITE_TEST_UTILS_H
