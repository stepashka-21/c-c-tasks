#include <iostream>
#include <cassert>
#include "my_vector.hpp"

namespace product {

class Product {
public:
    Product(const char *name, int quantity, double price) {
        size_t name_length = strlen(name);
        name_ = new char[name_length + 1];
        strcpy(name_, name);
        quantity_ = quantity;
        price_ = price;
    }

    Product(const Product &other) {
        size_t n = strlen(other.name_) + 1;
        name_ = new char[n];
        std::copy(other.name_, other.name_ + n, name_);
        quantity_ = other.quantity_;
        price_ = other.price_;
    }

    bool operator==(const Product &other) const {
        return strcmp(name_, other.name_) == 0 && quantity_ == other.quantity_ && price_ == other.price_;
    }

    ~Product() {
        delete[] name_;
    }

    friend std::ostream &operator<<(std::ostream &out, const Product &product) {
        return out << product.name_ << ' ' << product.quantity_ << ' ' << product.price_;
    }

private:
    char *name_;
    int quantity_;
    double price_;
};

}  // namespace product

template<typename T>
void test_my_vector(T first, T second) {
    containers::my_vector<T> vec;

    assert(vec.size() == 0 && vec.empty());

    vec.push_back(first);
    vec.push_back(second);

    assert(vec.size() == 2 && !vec.empty());
    assert(vec[0] == first && vec[1] == second);

    vec.pop_back();
    assert(vec.size() == 1 && vec[0] == first);

    vec.clear();
    assert(vec.empty());

    vec.reserve(10);
    assert(vec.capacity() >= 10);

    for (int i = 0; i < 15; ++i) {
        vec.push_back(first);
    }
    assert(vec.size() == 15 && vec.capacity() >= 15);

    vec.pop_back();
    assert(vec.size() == 14);

    vec.clear();
    assert(vec.capacity() >= 10);
    assert(vec.empty());
}

template<typename T>
void test_my_vector_default_constructible(size_t initial_size, T value) {
    containers::my_vector<T> vec(initial_size);
    assert(vec.size() == initial_size);

    vec.resize(initial_size + 5);
    assert(vec.size() == initial_size + 5);

    vec.resize(3);
    assert(vec.size() == 3);

    for (size_t i = 0; i < vec.size(); ++i) {
        assert(vec[i] == value);
    }
}

int main() {
    test_my_vector<int>(5, 10);
    test_my_vector_default_constructible<int>(5, 0);

    test_my_vector<product::Product>(
            product::Product("asdf", 4, 12.0),
            product::Product("qwe", -1, 7.5)
    );

    return 0;
}
