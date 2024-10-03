#include "matrix.h"

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

//Matrix::Matrix(const Matrix &m) : Matrix(m._rows, m._cols) {
// то есть лучше так? :
Matrix::Matrix(const Matrix &m) : _rows(m._rows), _cols(m._cols) {
    _data = new int*[_rows];
    for (std::size_t i = 0; i < _rows; ++i) {
        _data[i] = new int[_cols];
        for (std::size_t j = 0; j < _cols; ++j) {
            _data[i][j] = m._data[i][j];
        }
    }
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

void Matrix::print(FILE *f) const {
    for (std::size_t i = 0; i < _rows; ++i) {
        for (std::size_t j = 0; j < _cols; ++j) {
            fprintf(f, "%d", _data[i][j]);
            if (j + 1 != _cols) {
                fprintf(f, " ");
            }
        }
        fprintf(f, "\n");
    }
}

void Matrix::operations(const Matrix& m, int (*op)(int, int)) {
    for (std::size_t r = 0; r < _rows; ++r) {
        for (std::size_t c = 0; c < _cols; ++c) {
            _data[r][c] = op(_data[r][c], m._data[r][c]);
        }
    }
}

Matrix &Matrix::operator+=(const Matrix &m) {
    operations(m, [](int a, int b) { return a + b; });
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &m) {
    operations(m, [](int a, int b) { return a - b; });
    return *this;
}

Matrix operator+(const Matrix &m1, const Matrix &m2) {
    Matrix result = m1;
    result += m2;
    return result;
}

Matrix operator-(const Matrix &m1, const Matrix &m2) {
    Matrix result = m1;
    result -= m2;
    return result;
}

Matrix operator*(const Matrix &m1, const Matrix &m2) {
    Matrix result(m1._rows, m2._cols);
    for (size_t i = 0; i < m1._rows; ++i) {
        for (size_t j = 0; j < m2._cols; ++j) {
            for (size_t k = 0; k < m1._cols; ++k) {
                result._data[i][j] += m1._data[i][k] * m2._data[k][j];
            }
        }
    }
    return result;
}

Matrix& Matrix::operator=(Matrix m) {
    using std::swap;
    swap(_rows, m._rows);
    swap(_cols, m._cols);
    swap(_data, m._data);
    return *this;
}


Matrix& Matrix::operator*=(const Matrix& m) {
    *this = *this * m;
    return *this;
}

bool operator==(const Matrix& m1, const Matrix& m2) {
    if (m1._rows != m2._rows || m1._cols != m2._cols) {
        return false;
    }
    for (std::size_t i = 0; i < m1._rows; ++i) {
        for (std::size_t j = 0; j < m1._cols; ++j) {
            if (m1._data[i][j] != m2._data[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix& m1, const Matrix& m2) {
    return !(m1 == m2);
}
