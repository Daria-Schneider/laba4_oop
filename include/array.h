#pragma once
#include <memory>
#include <utility>
#include <stdexcept>

template<class T>
class Array {
public:
    Array() : _size{0}, _capacity{1}, _data{std::make_unique<T[]>(1)} {}
    
    Array(const Array& other) 
        : _size{other._size}
        , _capacity{other._capacity}
        , _data{std::make_unique<T[]>(other._capacity)} {
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = other._data[i];
        }
    }
    
    Array(Array&& other) noexcept 
        : _size{other._size}
        , _capacity{other._capacity}
        , _data{std::move(other._data)} {
        other._size = 0;
        other._capacity = 0;
    }
    
    Array& operator=(const Array& other) {
        if (this != &other) {
            _size = other._size;
            _capacity = other._capacity;
            _data = std::make_unique<T[]>(_capacity);
            for (size_t i = 0; i < _size; ++i) {
                _data[i] = other._data[i];
            }
        }
        return *this;
    }
    
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            _size = other._size;
            _capacity = other._capacity;
            _data = std::move(other._data);
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }
    
    ~Array() = default;
    
    void push_back(const T& value) {
        if (_size >= _capacity) {
            resize(_capacity == 0 ? 1 : 2 * _capacity);
        }
        _data[_size++] = value;
    }
    
    void push_back(T&& value) {
        if (_size >= _capacity) {
            resize(_capacity == 0 ? 1 : 2 * _capacity);
        }
        _data[_size++] = std::move(value);
    }
    
    void erase(size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        
        for (size_t i = index; i < _size - 1; ++i) {
            _data[i] = std::move(_data[i + 1]);
        }
        --_size;
    }
    
    T& operator[](size_t index) {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }
    
    const T& operator[](size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }
    
    size_t size() const { return _size; }
    size_t capacity() const { return _capacity; }
    
    void clear() {
        _size = 0;
        _capacity = 1;
        _data = std::make_unique<T[]>(1);
    }
    
    bool empty() const { return _size == 0; }

private:
    void resize(size_t new_capacity) {
        std::unique_ptr<T[]> new_data = std::make_unique<T[]>(new_capacity);
        
        for (size_t i = 0; i < _size; ++i) {
            new_data[i] = std::move(_data[i]);
        }
        
        _data = std::move(new_data);
        _capacity = new_capacity;
    }

private:
    size_t _size;
    size_t _capacity;
    std::unique_ptr<T[]> _data;
};