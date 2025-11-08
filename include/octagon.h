#pragma once
#include "figure.h"
#include <cmath>

template<Scalar T>
class Octagon : public Figure<T> {
public:
    Octagon() : Figure<T>(8) {
        static constexpr T PI = 3.14159265358979323846;
        for (int i = 0; i < 8; ++i) {
            T angle = 2 * PI * i / 8;
            this->_vertices[i] = Point<T>(std::cos(angle), std::sin(angle));
        }
    }
    
    Octagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4,
            const Point<T>& p5, const Point<T>& p6, const Point<T>& p7, const Point<T>& p8) 
        : Figure<T>(8) {
        this->_vertices[0] = p1;
        this->_vertices[1] = p2;
        this->_vertices[2] = p3;
        this->_vertices[3] = p4;
        this->_vertices[4] = p5;
        this->_vertices[5] = p6;
        this->_vertices[6] = p7;
        this->_vertices[7] = p8;
    }
    
    T area() const override {
        return this->calculateArea();
    }
    
    Point<T> center() const override {
        return this->calculateCenter();
    }
};