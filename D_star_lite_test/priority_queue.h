//
// Created by koby on 07/09/2020.
//
#include "utils.h"
#include "grid.h"
#ifndef D_STAR_LITE_TEST_PRIORITY_QUEUE_H
#define D_STAR_LITE_TEST_PRIORITY_QUEUE_H

//struct K{float k1;float k2;};

class Priority {
public:
    float k1;
    float k2;
    Priority(float tmp_k1, float tmp_k2);
    bool bigger(K other);
    bool smoler(K other);

        bool __le__(K other);
};

class PriorityNode {
public:
    K priority;
    short vertex[2];
    PriorityNode(K tmp_priority,short tmp_vertex[2]);
    bool __le__(K other);
    bool smoler(K other);

    bool bigger(K other);
};

class PriorityQueue {
public:
    std::vector<PriorityNode> heap;
    //std::vector<short*> vertices_in_heap;

  //  PriorityQueue();
    Vertex top();
    K top_key();
    void insert(short vertex[2],K priority);
    void remove(short vertex[2]);
    void update(short vertex[2],K priority);
    void build_heap();
    void _siftdown(short startpos,short pos);
    void _siftup(short pos);
};
#endif //D_STAR_LITE_TEST_PRIORITY_QUEUE_H
