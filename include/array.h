#pragma once
#include <memory>
#include <utility>
#include <stdexcept>

template<class T>
class Array {
public:
    Array();
    Array(const Array& other);
    Array(Array&& other) noexcept;
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    ~Array() = default;
    
    void push_back(const T& value);
    void push_back(T&& value);
    void erase(size_t index);
    
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    
    size_t size() const;
    size_t capacity() const;
    void clear();
    bool empty() const;

private:
    void resize(size_t new_capacity);

private:
    size_t _size;
    size_t _capacity;
    std::shared_ptr<T> _data;
};

#include "../src/array.ipp"