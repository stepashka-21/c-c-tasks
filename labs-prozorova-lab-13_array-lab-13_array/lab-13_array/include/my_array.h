#ifndef MY_ARRAY_H_
#define MY_ARRAY_H_

#include <cstddef>
#include <stdexcept>

namespace lab_13 {

template<typename T, std::size_t N>
class my_array {
private:
    T data[N];
public:
    T& at(std::size_t index) {
        if (index >= N)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    const T& at(std::size_t index) const {
        if (index >= N)
            throw std::out_of_range("Index out of range");
        return data[index];
    }

    T& operator[](std::size_t index) {
        return data[index];
    }

    const T& operator[](std::size_t index) const {
        return data[index];
    }

    bool empty() const {
        return N == 0;
    }

    std::size_t size() const {
        return N;
    }

    void fill(const T &val) {
        for (std::size_t i = 0; i < N; ++i) {
            data[i] = val;
        }
    }
};

template<std::size_t N>
class my_array<bool, N> {
private:
    static const std::size_t _size = 8;
    uint8_t data[(N + _size - 1) / _size];

    class bool_proxy {
    private:
        uint8_t& data;
        uint8_t bit;

    public:
        bool_proxy(uint8_t& data, uint8_t bit) : data(data), bit(bit) {}

        bool_proxy& operator=(bool val) {
            if (val) {
                data |= (1 << bit);
            } else {
                data &= ~(1 << bit);
            }
            return *this;
        }

        bool_proxy& operator=(const bool_proxy& other) {
            return operator=(bool(other));
        }

        operator bool() const {
            return data & (1 << bit);
        }
    };

public:
    bool_proxy operator[](std::size_t index) {
        return bool_proxy(data[index / _size], index % _size);
    }

    bool operator[](std::size_t index) const {
        return data[index / _size] & (1 << (index % _size));
    }

    bool_proxy at(std::size_t index) {
        if (index >= N)
            throw std::out_of_range("Index out of range");
        return (*this)[index];
    }

    bool at(std::size_t index) const {
        if (index >= N)
            throw std::out_of_range("Index out of range");
        return (*this)[index];
    }

    bool empty() const {
        return N == 0;
    }

    std::size_t size() const {
        return N;
    }

    void fill(bool val) {
        for (std::size_t i = 0; i < N; i++) {
            at(i) = val;
        }
    }
};
}  // namespace lab_13

#endif  // MY_ARRAY_H_
