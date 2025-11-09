#pragma once
#include "figure.h"
#include <cmath>

template<typename T>
class Pentagon : public Figure<T> {
public:
    Pentagon();
    Pentagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, 
             const Point<T>& p4, const Point<T>& p5);
    
    T area() const override;
    Point<T> center() const override;
};

#include "../src/pentagon.ipp"