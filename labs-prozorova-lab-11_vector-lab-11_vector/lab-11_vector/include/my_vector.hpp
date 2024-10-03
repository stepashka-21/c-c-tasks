#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <ostream>

namespace containers {

    template<typename T>
    class my_vector {
    public:
        my_vector();
        explicit my_vector(std::size_t n);
        my_vector(const my_vector<T> &other);
        my_vector<T>& operator=(my_vector<T> other);
        ~my_vector();

        std::size_t size() const;
        std::size_t capacity() const;
        bool empty() const;

        void resize(std::size_t n);
        void reserve(std::size_t n);

        T& operator[](std::size_t index);
        const T& operator[](std::size_t index) const;

        void push_back(const T& value);
        void pop_back();
        void clear();

    private:
        size_t capacity_;
        size_t size_;
        T* array_;
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const my_vector<T>& vector) {
        for (std::size_t i = 0; i < vector.size(); i++) {
            os << vector[i];
            if (i + 1 < vector.size()) {
                os << ' ';
            }
        }
        return os;
    }

}

#include "my_vector_impl.hpp"

#endif  // MY_VECTOR_H_
