#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <vector>
#include<math.h>

class Matrix {
public:
    std::vector<std::vector<double>> mat;
    Matrix(size_t rows, size_t cols, double init_val = 0.0) : mat(rows, std::vector<double>(cols, init_val)) {}
    Matrix(const std::vector<std::vector<double>>& values) : mat(values) {}
    Matrix() {}

    static Matrix identity(size_t size);

    size_t rows() const {return mat.size();}
    size_t cols() const {return mat[0].size();}

    Matrix multiply(const Matrix& B) const;
    Matrix add(const Matrix& B) const;
    Matrix subtract(const Matrix& B) const;
    Matrix transpose() const;
    Matrix invert() const;
    std::vector<double>& operator[](size_t index);
    const std::vector<double>& operator[](size_t index) const;
    Matrix operator*(const Matrix &B) const;
    Matrix operator+(const Matrix &B) const;
    Matrix operator-(const Matrix &B) const;
    Matrix operator*(double val) const;
    friend Matrix operator*(double val, const Matrix &B);
    void mat_print() const;
};
#endif