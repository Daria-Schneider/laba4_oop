#pragma once
#include "figure.h"
#include <cmath>

template<Scalar T>
class Hexagon : public Figure<T> {
public:
    Hexagon() : Figure<T>(6) {
        for (int i = 0; i < 6; ++i) {
            T angle = 2 * 3.14159265358979323846 * i / 6;
            this->_vertices[i] = Point<T>(std::cos(angle), std::sin(angle));
        }
    }
    
    Hexagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3,
            const Point<T>& p4, const Point<T>& p5, const Point<T>& p6) : Figure<T>(6) {
        this->_vertices[0] = p1;
        this->_vertices[1] = p2;
        this->_vertices[2] = p3;
        this->_vertices[3] = p4;
        this->_vertices[4] = p5;
        this->_vertices[5] = p6;
    }
    
    T area() const override {
        return this->calculateArea();
    }
    
    Point<T> center() const override {
        return this->calculateCenter();
    }
};