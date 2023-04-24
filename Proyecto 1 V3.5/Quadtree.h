#ifndef QUADTREE_H
#define QUADTREE_H

#include "Curiosity.h"
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

class Quadtree {
public:
    Quadtree();
    Quadtree(float x, float y, float w, float h, int level);
    ~Quadtree();
    void insert(sElemento elemento);
    vector<sElemento> query(float x, float y, float w, float h);
    void print();
private:
    float x_, y_, w_, h_;
    int level_;
    vector<sElemento> elementos_;
    Quadtree* children_[4];
    bool contains(float x, float y, float w, float h);
    
};

#endif // QUADTREE_H