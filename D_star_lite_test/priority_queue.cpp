//
// Created by koby on 07/09/2020.
//

#include "priority_queue.h"

    Priority::Priority(float tmp_k1,float tmp_k2){
        this->k1=tmp_k1;
        this->k2=tmp_k2;
    }

    bool Priority::bigger(K other){
        return this->k1 < other.k1 or (this->k1 == other.k1 and this->k2 < other.k2);
    }
bool Priority::smoler(K other){
    return this->k1 > other.k1 or (this->k1 == other.k1 and this->k2 > other.k2);
}
    bool Priority::__le__(K other){
        return this->k1 < other.k1 or (this->k1 == other.k1 and this->k2 <= other.k2);
    }



PriorityNode::PriorityNode(K tmp_priority,short tmp_vertex[2]){
        this->priority=tmp_priority;
        this->vertex[0]=tmp_vertex[0];
        this->vertex[1]=tmp_vertex[1];
    }

    bool PriorityNode::__le__(K other) {
        return this->priority.k1 < other.k1 or (this->priority.k1 == other.k1 and this->priority.k2 < other.k2);
    }
    bool PriorityNode::smoler(K other){
    return this->priority.k1 > other.k1 or (this->priority.k1 == other.k1 and this->priority.k2 > other.k2);
}
    bool PriorityNode::bigger(K other) {
        return this->priority.k1 < other.k1 or (this->priority.k1 == other.k1 and this->priority.k2 <= other.k2);
    }


    Vertex PriorityQueue::top(){
        return this->heap[0].vertex;
    }
    K PriorityQueue::top_key(){
        if(!this->heap.size()){
            return {std::numeric_limits<float>::infinity(),std::numeric_limits<float>::infinity()};
        }
        return this->heap[0].priority;
    }

    void PriorityQueue::insert(short vertex[2],K priority){
        PriorityNode  item(priority, vertex);
        this->vertices_in_heap.push_back(vertex);
        int i;
        for (i=0; i <this->heap.size() ; ++i) {
            if(this->heap[i].smoler(priority)){
                break;
            }
        }
        this->heap.insert(this->heap.begin()+i,item);//push_back(item);
     //  this->_siftdown(0, this->heap.size() - 1);
    }

    void PriorityQueue::remove(short vertex[2]){
        this->vertices_in_heap.erase(std::remove( this->vertices_in_heap.begin(),  this->vertices_in_heap.end(), vertex),  this->vertices_in_heap.end());
        for (int i = 0; i < this->heap.size(); ++i) {
            if (this->heap[i].vertex[0]==vertex[0]&&this->heap[i].vertex[1]==vertex[1]) {
                this->heap.erase(this->heap.begin()+i);
                break;
            }
        }
        for (int i = 0; i < this->vertices_in_heap.size(); ++i) {
            if(this->vertices_in_heap[i][0]==vertex[0] &&this->vertices_in_heap[i][1]==vertex[1]){
                this->vertices_in_heap.erase(this->vertices_in_heap.begin()+i);
                break;
            }
        }
     //   this->build_heap();
    }
    void PriorityQueue::update(short vertex[2],K priority) {
        for (int i = 0; i < this->heap.size(); ++i) {

            if (this->heap[i].vertex[0]==vertex[0]&&this->heap[i].vertex[1]==vertex[1]) {
                this->heap[i].priority = priority;
            }
            break;
        }
      //  this->build_heap();

    }
    void PriorityQueue::build_heap(){
        for (int i = int(this->heap.size()/2); i > 0; --i) {
            this->_siftup(i);
        }
    }

    void PriorityQueue::_siftdown(short startpos,short pos){
        PriorityNode  newitem = this->heap[pos];
        short tmp[]={0,0};
        PriorityNode parent({0,0},tmp) ;
        short parentpos;
        while (pos>startpos){
            parentpos=(pos - 1) >> 1;
            parent=this->heap[parentpos];
            if(newitem.bigger(parent.priority)){
                this->heap[pos]=parent;
                pos = parentpos;
                continue;
            }
            break;
        }
        this->heap[pos]=newitem;

    }
    void PriorityQueue::_siftup(short pos){
        short endpos = this->heap.size();
        PriorityNode  newitem = this->heap[pos];
        short rightpos;
        short startpos = pos;
        short childpos = 2 * pos + 1;
        while( childpos < endpos){
            rightpos = childpos + 1;
            if (rightpos < endpos && !(this->heap[childpos].bigger(this->heap[rightpos].priority))) {
                childpos = rightpos;
            }
            this->heap[pos] = this->heap[childpos];
            pos = childpos;
            childpos = 2 * pos + 1;

        }
        this->heap[pos] = newitem;
        this->_siftdown(startpos, pos);
    }

/* -----------------need to modfay-------------------
    def PriorityQueue::pop(self):
    """!!!THIS CODE WAS COPIED AND MODIFIED!!! Source: Lib/heapq.py"""
    """Pop the smallest item off the heap, maintaining the heap invariant."""
    lastelt = self.heap.pop()  # raises appropriate IndexError if heap is empty
            self.vertices_in_heap.remove(lastelt)
    if self.heap:
            returnitem = self.heap[0]
    self.heap[0] = lastelt
            self._siftup(0)
    else:
    returnitem = lastelt
    return returnitem*/
