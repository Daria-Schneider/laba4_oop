#pragma once
#include <memory>
#include <cmath>
#include <iostream>
#include "point.h"

template<Scalar T>
class Figure {
public:
    Figure(size_t vertex_count) 
        : _vertices{std::make_unique<Point<T>[]>(vertex_count)}
        , _vertex_count{vertex_count} {}
    
    virtual ~Figure() = default;
    
    Figure(const Figure&) = delete;
    Figure& operator=(const Figure&) = delete;
    Figure(Figure&&) = default;
    Figure& operator=(Figure&&) = default;
    
    virtual T area() const = 0;
    virtual Point<T> center() const = 0;
    
    virtual explicit operator double() const {
        return static_cast<double>(area());
    }
    
    Point<T>& vertex(size_t index) { 
        if (index >= _vertex_count) throw std::out_of_range("Vertex index out of range");
        return _vertices[index]; 
    }
    
    const Point<T>& vertex(size_t index) const { 
        if (index >= _vertex_count) throw std::out_of_range("Vertex index out of range");
        return _vertices[index]; 
    }
    
    size_t vertex_count() const { return _vertex_count; }
    
    friend bool operator==(const Figure& a, const Figure& b) {
        if (a._vertex_count != b._vertex_count) return false;
        
        for (size_t i = 0; i < a._vertex_count; ++i) {
            if (a._vertices[i] != b._vertices[i]) return false;
        }
        return true;
    }
    
    friend bool operator!=(const Figure& a, const Figure& b) {
        return !(a == b);
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Figure& fig) {
        os << "[";
        for (size_t i = 0; i < fig._vertex_count; ++i) {
            os << fig._vertices[i];
            if (i < fig._vertex_count - 1) os << ", ";
        }
        os << "]";
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Figure& fig) {
        for (size_t i = 0; i < fig._vertex_count; ++i) {
            Point<T> p;
            is >> p;
            fig._vertices[i] = p;
        }
        return is;
    }

protected:
    T calculateArea() const {
        if (_vertex_count < 3) return 0;
        
        T area = 0;
        
        for (size_t i = 0; i < _vertex_count; ++i) {
            const Point<T>& current = _vertices[i];
            const Point<T>& next = _vertices[(i + 1) % _vertex_count];
            area += current.x() * next.y() - next.x() * current.y();
        }
        
        return std::abs(area) / 2;
    }
    
    Point<T> calculateCenter() const {
        if (_vertex_count == 0) return Point<T>();
        
        T centerX = 0, centerY = 0;
        
        for (size_t i = 0; i < _vertex_count; ++i) {
            centerX += _vertices[i].x();
            centerY += _vertices[i].y();
        }
        
        return Point<T>(centerX / _vertex_count, centerY / _vertex_count);
    }

protected:
    std::unique_ptr<Point<T>[]> _vertices;
    size_t _vertex_count;
};