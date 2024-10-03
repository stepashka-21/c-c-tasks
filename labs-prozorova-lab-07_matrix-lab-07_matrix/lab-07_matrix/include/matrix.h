#ifndef LAB_07_MATRIX_H
#define LAB_07_MATRIX_H

#include <cstdio>
#include <cstddef>
#include <algorithm>

class Matrix {

public:
    Matrix(std::size_t r, std::size_t c);
    ~Matrix();
    Matrix(const Matrix& m);
    std::size_t get_rows() const;
    std::size_t get_cols() const;
    void set(std::size_t i, std::size_t j, int val);
    int get(std::size_t i, std::size_t j) const;
    void print(FILE *f) const;
    void operations(const Matrix& m, int (*op)(int, int));

    friend Matrix operator+(const Matrix& m1, const Matrix& m2);
    friend Matrix operator-(const Matrix& m1, const Matrix& m2);
    friend Matrix operator*(const Matrix& m1, const Matrix& m2);
    friend bool operator==(const Matrix& m1, const Matrix& m2);
    friend bool operator!=(const Matrix& m1, const Matrix& m2);

    Matrix& operator+=(const Matrix& m);
    Matrix& operator-=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);
    Matrix& operator=(Matrix m);

private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data;
};

#endif
