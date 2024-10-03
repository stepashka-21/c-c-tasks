#ifndef MY_VECTOR_IMPL_HPP
#define MY_VECTOR_IMPL_HPP

#include <cstddef>
#include <cstring>

namespace containers {
    template<typename T>
    my_vector<T>::my_vector() : capacity_(1), size_(0), array_(reinterpret_cast<T *>(new char[sizeof(T)])) {}
    
    // template<typename T>
    // my_vector<T>::my_vector(std::size_t n) : size_(n), capacity_(n) {
    //     size_t k = 1;
    //     while (k < n) { 
    //         k *= 2; 
    //     }
    //     capacity_ = k;
    //     array_ = reinterpret_cast<T*>(new char [capacity_ * sizeof(T)]);
    //     for (size_t i = 0; i < n; ++i) {
    //         new (array_ + i) T();
    //     }
    // }
    
    template<typename T>
    my_vector<T>::my_vector(std::size_t n) : size_(0), capacity_(n) {
        size_t k = 1;
        while (k < n) { 
            k *= 2; 
        }
        capacity_ = k;
        array_ = reinterpret_cast<T*>(new char [capacity_ * sizeof(T)]);
        resize(n);
    }

    // template<typename T>
    // my_vector<T>::my_vector(const my_vector<T>& other)
    //         : size_(other.size_), capacity_(other.capacity_), array_(nullptr) {
    //     if (capacity_ > 0) {
    //         array_ = reinterpret_cast<T*>(new char[sizeof(T) * capacity_]);
    //         for (std::size_t i = 0; i < size_; ++i) {
    //             new (array_ + i) T(other.array_[i]);
    //         }
    //     }
    // }

    template<typename T>
    my_vector<T>::my_vector(const my_vector<T>& other)
            : size_(0), capacity_(1), array_(nullptr) {
        reserve(other.size_);
        for (std::size_t i = 0; i < other.size_; ++i) {
            new (array_ + i) T(other.array_[i]);
        }
        size_ = other.size_;
    }

    template<typename T>
    my_vector<T>& my_vector<T>::operator=(my_vector<T> other) {
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
        std::swap(array_, other.array_);
        return *this;
    }

    template<typename T>
    my_vector<T>::~my_vector() {
        clear();
        delete[] reinterpret_cast<char *>(array_);
    }

    template<typename T>
    std::size_t my_vector<T>::size() const {
        return size_;
    }

    template<typename T>
    std::size_t my_vector<T>::capacity() const {
        return capacity_;
    }

    template<typename T>
    bool my_vector<T>::empty() const {
        return size_ == 0;
    }

    template<typename T>
    void my_vector<T>::resize(std::size_t n) {
        while (size_ > n)
            array_[--size_].~T();
        reserve(n);
        while (size_ < n)
            new(array_ + (size_++)) T();
    }

    template<typename T>
    void my_vector<T>::reserve(std::size_t n) {
        if (n <= capacity_)
            return;
        size_t new_capacity = capacity_;
        while (new_capacity < n)
            new_capacity <<= 1;
        T *new_array = reinterpret_cast<T *>(new char[sizeof(T) * new_capacity]);
        for (size_t i = 0; i < size_; i++) {
            new(new_array + i) T(array_[i]);
            array_[i].~T();
        }
        delete[] reinterpret_cast<char *>(array_);
        array_ = reinterpret_cast<T *>(new_array);
        capacity_ = new_capacity;
    }

    template<typename T>
    T& my_vector<T>::operator[](std::size_t index) {
        return array_[index];
    }

    template<typename T>
    const T& my_vector<T>::operator[](std::size_t index) const {
        return array_[index];
    }

    template<typename T>
    void my_vector<T>::push_back(const T& value) {
        reserve(size_ + 1);
        new(array_ + size_) T(value);
        size_++;
    }

    template<typename T>
    void my_vector<T>::pop_back() {
        if (size_ > 0) {
            size_--;
            array_[size_].~T();
        }
    }

    template<typename T>
    void my_vector<T>::clear() {
        for (size_t i = 0; i < size_; i++)
            array_[i].~T();
        size_ = 0;
    }

}

#endif  // MY_VECTOR_IMPL_HPP
