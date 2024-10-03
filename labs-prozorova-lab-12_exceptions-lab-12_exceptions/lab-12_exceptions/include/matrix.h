#ifndef LAB_12_EXCEPTIONS_MATRIX_H
#define LAB_12_EXCEPTIONS_MATRIX_H

#include <cstdio>
#include <cstddef>
#include <iostream>
#include <algorithm>

class Matrix {

public:
    Matrix(std::size_t r, std::size_t c);
    Matrix(const Matrix &m);
    ~Matrix();
    Matrix();
//    std::size_t get_rows() const;
//    std::size_t get_cols() const;
//    void set(std::size_t i, std::size_t j, int val);
    int get(int i, int j) const;
    void print(FILE *f) const;
    void operations(const Matrix& m, int (*op)(int, int));

    Matrix& operator+=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);
    Matrix& operator=(Matrix m);

    static Matrix* load(const std::string &filename);
    void memory_alloc();
private:
    std::size_t _rows;
    std::size_t _cols;
    int **_data{};
};

class MatrixException : public std::invalid_argument {
public:
    explicit MatrixException(const std::string &message);
};

#endif //LAB_12_EXCEPTIONS_MATRIX_H
