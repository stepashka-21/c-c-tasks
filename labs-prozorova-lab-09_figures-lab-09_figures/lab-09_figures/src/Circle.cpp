#include "Circle.hpp"
#include <stdio.h>
#include <math.h>
#include <cstring>

Circle::Circle(int id, int x, int y, int radius, const char* label) : Figure(id, x, y), radius(radius) {
    char* tmp = new char[std::strlen(label) + 1];
    std::strcpy(tmp, label);
    this->label = tmp;
}

Circle::~Circle() {
    delete[] label;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id, x, y, radius, label);
}

bool Circle::is_inside(int x, int y) const {
    return pow((x - this->x), 2) + pow((y - this->y), 2) <= pow(radius, 2);
}

void Circle::zoom(int factor) {
    radius *= factor;
}
