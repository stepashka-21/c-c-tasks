#include "matrix.hpp"

Matrix::Matrix(std::size_t r, std::size_t c) : _rows(r), _cols(c) {
    _data = new int*[_rows];
    for (std::size_t i = 0; i < _rows; ++i) {
        _data[i] = new int[_cols];
        std::fill(_data[i], _data[i] + _cols, 0);
    }
}

Matrix::~Matrix() {
    for (std::size_t i = 0; i < _rows; ++i) {
        delete[] _data[i];
    }
    delete[] _data;
}

Matrix::Matrix(const Matrix& m) : _rows(m._rows), _cols(m._cols) {
    _data = new int*[_rows];
    for (std::size_t i = 0; i < _rows; ++i) {
        _data[i] = new int[_cols];
        for (std::size_t j = 0; j < _cols; ++j) {
            _data[i][j] = m._data[i][j];
        }
    }
}

Matrix& Matrix::operator=(Matrix m) {
    using std::swap;
    swap(_rows, m._rows);
    swap(_cols, m._cols);
    swap(_data, m._data);
    return *this;
}

std::size_t Matrix::get_rows() const {
    return _rows;
}

std::size_t Matrix::get_cols() const {
    return _cols;
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
    _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
    return _data[i][j];
}

bool Matrix::operator==(const Matrix& that) const {
    if (_rows != that._rows || _cols != that._cols) {
        return false;
    }
    for (std::size_t i = 0; i < _rows; ++i) {
        for (std::size_t j = 0; j < _cols; ++j) {
            if (_data[i][j] != that._data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& that) const {
    return !(*this == that);
}
