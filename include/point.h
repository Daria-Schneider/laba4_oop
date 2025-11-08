#pragma once
#include <iostream>
#include "concepts.h"

template<Scalar T>
class Point {
public:
    Point() : _x{0}, _y{0} {}
    Point(T x, T y) : _x{x}, _y{y} {}
    
    T x() const { return _x; }
    T y() const { return _y; }
    
    void setX(T x) { _x = x; }
    void setY(T y) { _y = y; }
    
    friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os << '(' << p._x << ' ' << p._y << ')';
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Point& p) {
        is >> p._x >> p._y;
        return is;
    }
    
    bool operator==(const Point& other) const {
        return _x == other._x && _y == other._y;
    }
    
    bool operator!=(const Point& other) const {
        return !(*this == other);
    }

private:
    T _x, _y;
};