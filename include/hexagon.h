#pragma once
#include "figure.h"
#include <cmath>

template<typename T>
class Hexagon : public Figure<T> {
public:
    Hexagon();
    Hexagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3,
            const Point<T>& p4, const Point<T>& p5, const Point<T>& p6);
    
    T area() const override;
    Point<T> center() const override;
};

#include "../src/hexagon.ipp"