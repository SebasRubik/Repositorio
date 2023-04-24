#include "Curiosity.h"
#include "Quadtree.h"
#include "archivoFunciones.h"
#include <iostream>
#include <fstream>
#include <vector>

/*#define MAX_ELEMENTOS_POR_QUADTREE = 10;
#define MAX_NIVEL_QUADTREE = 10;*/

using namespace std;


Quadtree::Quadtree(float x, float y, float w, float h, int level)
    : x_(x), y_(y), w_(w), h_(h), level_(level)
{
    for (int i = 0; i < 4; ++i) {
        children_[i] = nullptr;
    }
}

Quadtree::Quadtree()
{
}

Quadtree::~Quadtree()
{
    for (int i = 0; i < 4; ++i) {
        delete children_[i];
    }
}

void Quadtree::insert(sElemento elemento)
{
    if (!contains(elemento.coorDx, elemento.coorDy, elemento.tamanio, elemento.tamanio)) {
        return;
    }
    if (children_[0] != nullptr) {
        for (int i = 0; i < 4; ++i) {
            children_[i]->insert(elemento);
        }
        return;
    }
    elementos_.push_back(elemento);
    if (elementos_.size() > 10 && level_ < 10) {
        if (children_[0] == nullptr) {
            float nw = w_ / 2, nh = h_ / 2;
            children_[0] = new Quadtree(x_, y_, nw, nh, level_ + 1);
            children_[1] = new Quadtree(x_ + nw, y_, nw, nh, level_ + 1);
            children_[2] = new Quadtree(x_, y_ + nh, nw, nh, level_ + 1);
            children_[3] = new Quadtree(x_ + nw, y_ + nh, nw, nh, level_ + 1);
        }
        for (auto& e : elementos_) {
            for (int i = 0; i < 4; ++i) {
                children_[i]->insert(e);
            }
        }
        elementos_.clear();
    }
}

vector<sElemento> Quadtree::query(float x, float y, float w, float h)
{
    vector<sElemento> result;
    if (!contains(x, y, w, h)) {
        return result;
    }
    for (auto& e : elementos_) {
        if (e.coorDx + e.tamanio > x && e.coorDx < x + w && e.coorDy + e.tamanio > y && e.coorDy < y + h) {
            result.push_back(e);
        }
    }
    if (children_[0] == nullptr) {
        return result;
    }
    vector<vector<sElemento>> child_results(4);
    float nw = w_ / 2, nh = h_ / 2;
    child_results[0] = children_[0]->query(x, y, w, h);
    child_results[1] = children_[1]->query(x, y, w, h);
    child_results[2] = children_[2]->query(x, y, w, h);
    child_results[3] = children_[3]->query(x, y, w, h);
    for (int i = 0; i < 4; ++i) {
    result.insert(result.end(), child_results[i].begin(), child_results[i].end());
    }
    return result;
}

bool Quadtree::contains(float x, float y, float w, float h)
{
return (x_ <= x && x + w <= x_ + w_ && y_ <= y && y + h <= y_ + h_);
}

void Quadtree::print()
{
    //imprime el quadtree en inorder
    if (children_[0] != nullptr) {
        for (int i = 0; i < 4; ++i) {
            children_[i]->print();
        }
    }
    for (auto& e : elementos_) {
        cout << e.coorDx << " " << e.coorDy << " " << e.tamanio << endl;
    }
}
