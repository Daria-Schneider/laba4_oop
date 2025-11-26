#pragma once
#include <memory>
#include <cmath>
#include <iostream>
#include "point.h"

template<typename T>
class Figure {
public:
    Figure(size_t vertex_count);
    virtual ~Figure() = default;
    
    Figure(const Figure&) = delete;
    Figure& operator=(const Figure&) = delete;
    Figure(Figure&&) = default;
    Figure& operator=(Figure&&) = default;
    
    virtual T area() const = 0;
    virtual Point<T> center() const = 0;
    
    virtual explicit operator double() const;
    
    Point<T>& vertex(size_t index);
    const Point<T>& vertex(size_t index) const;
    
    size_t vertex_count() const;
    
    template<typename U>
    friend bool operator==(const Figure<U>& a, const Figure<U>& b);
    
    template<typename U>
    friend bool operator!=(const Figure<U>& a, const Figure<U>& b);
    
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Figure<U>& fig);
    
    template<typename U>
    friend std::istream& operator>>(std::istream& is, Figure<U>& fig);

protected:
    T calculateArea() const;
    Point<T> calculateCenter() const;

protected:
    std::shared_ptr<Point<T>[]> _vertices;
    size_t _vertex_count;
};

#include "../src/figure.ipp"