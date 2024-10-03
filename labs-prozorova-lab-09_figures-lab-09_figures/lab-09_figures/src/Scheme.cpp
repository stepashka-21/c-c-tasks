#include "Scheme.hpp"
#include <cassert>

Scheme::Scheme(int capacity) : capacity(capacity), size(0) {
    figures_ = new Figure*[capacity];
}

Scheme::~Scheme() {
    for (int i = 0; i < size; i++) {
        delete figures_[i];
    }
    delete[] figures_;
}

void Scheme::push_back_figure(Figure* fg) {
    assert(size < capacity);
    figures_[size++] = fg;
}

int Scheme::ind(int id) {
    for (int i = 0; i < size; i++) {
        if (figures_[i]->get_id() == id) {
            return i;
        }
    }
    return -1;
}

void Scheme::remove_figure(int id) { // элементы смещаются влево
    int j = ind(id);
    delete figures_[j];
    for (int i = j; i < size - 1; i++) {
        figures_[i] = figures_[i + 1];
    }
    size--;
}

void Scheme::print_all_figures() {
    for (int i = 0; i < size; i++) {
        figures_[i]->print();
    }
}

void Scheme::zoom_figure(int id, int factor) {
    figures_[ind(id)]->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) { // если внутри нескольких фигур, то возвращается любая из них
    for (int i = 0; i < size; i++) {
        if (figures_[i]->is_inside(x, y)) {
            return figures_[i];
        }
    }
    return nullptr;
}
void Scheme::move(int id, int new_x, int new_y) {
    figures_[ind(id)]->move(new_x, new_y);
}

