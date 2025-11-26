template<typename T>
Figure<T>::Figure(size_t vertex_count) 
    : _vertices{new Point<T>[vertex_count]}
    , _vertex_count{vertex_count} {}

template<typename T>
Figure<T>::operator double() const {
    return static_cast<double>(area());
}

template<typename T>
Point<T>& Figure<T>::vertex(size_t index) {
    if (index >= _vertex_count) throw std::out_of_range("Vertex index out of range");
    return _vertices[index];
}

template<typename T>
const Point<T>& Figure<T>::vertex(size_t index) const {
    if (index >= _vertex_count) throw std::out_of_range("Vertex index out of range");
    return _vertices[index];
}

template<typename T>
size_t Figure<T>::vertex_count() const { return _vertex_count; }

template<typename U>
bool operator==(const Figure<U>& a, const Figure<U>& b) {
    if (a._vertex_count != b._vertex_count) return false;
    
    for (size_t i = 0; i < a._vertex_count; ++i) {
        if (a._vertices[i] != b._vertices[i]) return false;
    }
    return true;
}

template<typename U>
bool operator!=(const Figure<U>& a, const Figure<U>& b) {
    return !(a == b);
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Figure<U>& fig) {
    os << "[";
    for (size_t i = 0; i < fig._vertex_count; ++i) {
        os << fig._vertices[i];
        if (i < fig._vertex_count - 1) os << ", ";
    }
    os << "]";
    return os;
}

template<typename U>
std::istream& operator>>(std::istream& is, Figure<U>& fig) {
    for (size_t i = 0; i < fig._vertex_count; ++i) {
        Point<U> p;
        is >> p;
        fig._vertices[i] = p;
    }
    return is;
}

template<typename T>
T Figure<T>::calculateArea() const {
    if (_vertex_count < 3) return 0;
    
    T area = 0;
    
    for (size_t i = 0; i < _vertex_count; ++i) {
        const Point<T>& current = _vertices[i];
        const Point<T>& next = _vertices[(i + 1) % _vertex_count];
        area += current.x() * next.y() - next.x() * current.y();
    }
    
    return std::abs(area) / 2;
}

template<typename T>
Point<T> Figure<T>::calculateCenter() const {
    if (_vertex_count == 0) return Point<T>();
    
    T centerX = 0, centerY = 0;
    
    for (size_t i = 0; i < _vertex_count; ++i) {
        centerX += _vertices[i].x();
        centerY += _vertices[i].y();
    }
    
    return Point<T>(centerX / _vertex_count, centerY / _vertex_count);
}