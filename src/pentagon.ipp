template<typename T>
Pentagon<T>::Pentagon() : Figure<T>(5) {
    static constexpr T PI = 3.14159265358979323846;
    for (int i = 0; i < 5; ++i) {
        T angle = 2 * PI * i / 5;
        this->_vertices[i] = Point<T>(std::cos(angle), std::sin(angle));
    }
}

template<typename T>
Pentagon<T>::Pentagon(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3, 
                      const Point<T>& p4, const Point<T>& p5) : Figure<T>(5) {
    this->_vertices[0] = p1;
    this->_vertices[1] = p2;
    this->_vertices[2] = p3;
    this->_vertices[3] = p4;
    this->_vertices[4] = p5;
}

template<typename T>
T Pentagon<T>::area() const {
    return this->calculateArea();
}

template<typename T>
Point<T> Pentagon<T>::center() const {
    return this->calculateCenter();
}