template<class T>
Array<T>::Array() 
    : _size{0}, _capacity{1}, 
      _data{new T[1], std::default_delete<T[]>()} {}

template<class T>
Array<T>::Array(const Array& other) 
    : _size{other._size}
    , _capacity{other._capacity}
    , _data{new T[other._capacity], std::default_delete<T[]>()} {
    for (size_t i = 0; i < _size; ++i) {
        _data.get()[i] = other._data.get()[i];
    }
}

template<class T>
Array<T>::Array(Array&& other) noexcept 
    : _size{other._size}
    , _capacity{other._capacity}
    , _data{std::move(other._data)} {
    other._size = 0;
    other._capacity = 0;
}

template<class T>
Array<T>& Array<T>::operator=(const Array& other) {
    if (this != &other) {
        _size = other._size;
        _capacity = other._capacity;
        _data = std::shared_ptr<T>(new T[_capacity], std::default_delete<T[]>());
        for (size_t i = 0; i < _size; ++i) {
            _data.get()[i] = other._data.get()[i];
        }
    }
    return *this;
}

template<class T>
Array<T>& Array<T>::operator=(Array&& other) noexcept {
    if (this != &other) {
        _size = other._size;
        _capacity = other._capacity;
        _data = std::move(other._data);
        other._size = 0;
        other._capacity = 0;
    }
    return *this;
}

template<class T>
void Array<T>::push_back(const T& value) {
    if (_size >= _capacity) {
        resize(_capacity == 0 ? 1 : 2 * _capacity);
    }
    _data.get()[_size++] = value;
}

template<class T>
void Array<T>::push_back(T&& value) {
    if (_size >= _capacity) {
        resize(_capacity == 0 ? 1 : 2 * _capacity);
    }
    _data.get()[_size++] = std::move(value);
}

template<class T>
void Array<T>::erase(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    
    for (size_t i = index; i < _size - 1; ++i) {
        _data.get()[i] = std::move(_data.get()[i + 1]);
    }
    --_size;
}

template<class T>
T& Array<T>::operator[](size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data.get()[index];
}

template<class T>
const T& Array<T>::operator[](size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return _data.get()[index];
}

template<class T>
size_t Array<T>::size() const { return _size; }

template<class T>
size_t Array<T>::capacity() const { return _capacity; }

template<class T>
void Array<T>::clear() {
    _size = 0;
    _capacity = 1;
    _data = std::shared_ptr<T>(new T[1], std::default_delete<T[]>());
}

template<class T>
bool Array<T>::empty() const { return _size == 0; }

template<class T>
void Array<T>::resize(size_t new_capacity) {
    std::shared_ptr<T> new_data(new T[new_capacity], std::default_delete<T[]>());
    
    for (size_t i = 0; i < _size; ++i) {
        new_data.get()[i] = std::move(_data.get()[i]);
    }
    
    _data = std::move(new_data);
    _capacity = new_capacity;
}