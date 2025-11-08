#pragma once
#include "figure.h"
#include <cmath>

template<Scalar T>
class Pentagon : public Figure<T> {
public:
    Pentagon() : Figure<T>(5) {
        static constexpr T PI = 3.14159265358979323846;
        for (int i = 0; i < 5; ++i) {
            T angle = 2 * PI * i / 5;
            this->_vertices[i] = Point<T>(std::cos(angle), std::sin(angle));
        }
    }
    
    Pentagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, 
             const Point<T>& p4, const Point<T>& p5) : Figure<T>(5) {
        this->_vertices[0] = p1;
        this->_vertices[1] = p2;
        this->_vertices[2] = p3;
        this->_vertices[3] = p4;
        this->_vertices[4] = p5;
    }
    
    T area() const override {
        return this->calculateArea();
    }
    
    Point<T> center() const override {
        return this->calculateCenter();
    }
};