#pragma once

#include <iostream>

template <typename T>
class Vector {
private:
    T* data_;
    size_t size_;
    size_t capacity_;

    void grow() {
        capacity_ *= 2;
        T* new_data_ = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            new_data_[i] = data_[i];
        }

        delete[] data_;
        data_ = new_data_;
    }

public:
    Vector(size_t cap = 0) {
        capacity_ = (cap > 0) ? cap : 2;
        size_ = 0;
        data_ = new T[capacity_];
    }

    void push_back(const T& value) {
        if (size_ >= capacity_) grow();

        data_[size_] = value;
        size_++;
    }

    void pop_back() {
        size_--;
    }

    size_t size() {
        return size_;
    }

    T& operator[](size_t index) {
        if (index >= size_) {
            std::cerr << "index is out of bound" << std::endl;
            return data_[0];
        }
        return data_[index];
    }

    void clear() {
        delete[] data_;
        capacity_ = 2;
        size_ = 0;
        data_ = new T[capacity_];
    }

    Vector& operator=(const Vector<T>& other) {
        if (this == &other) return *this;

        capacity_ = other.capacity_;
        size_ = other.size_;

        delete[] data_;

        data_ = new T[capacity_];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = other.data_[i];
        }

        return *this;
    }

    void show() {
        for (size_t i = 0; i < size_; i++) {
            std::cout << data_[i] << " ";
        }
        std::cout << '\n';
    }

    ~Vector() {
        delete[] data_;
    }
};

