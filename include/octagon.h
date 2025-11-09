#pragma once
#include "figure.h"
#include <cmath>

template<typename T>
class Octagon : public Figure<T> {
public:
    Octagon();
    Octagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, const Point<T>& p4,
            const Point<T>& p5, const Point<T>& p6, const Point<T>& p7, const Point<T>& p8);
    
    T area() const override;
    Point<T> center() const override;
};

#include "../src/octagon.ipp"