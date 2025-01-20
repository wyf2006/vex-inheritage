#include "../include/Matrix.h"
#include<cassert>
#include<cmath>
using namespace std;

Matrix Matrix::identity(size_t size) {
    Matrix I(size, size);
    for (size_t i = 0; i < size; ++i) {
        I.mat[i][i] = 1.0;
    }
    return I;
}

/// @brief 右乘
Matrix Matrix::multiply(const Matrix& B) const {
    assert(cols() == B.rows());
    Matrix result(rows(), B.cols());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < B.cols(); ++j) {
            for (size_t k = 0; k < cols(); ++k) {
                result.mat[i][j] += mat[i][k] * B.mat[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::add(const Matrix& B) const {
    assert(rows() == B.rows() && cols() == B.cols());
    Matrix result(rows(), cols());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < cols(); ++j) {
            result.mat[i][j] = mat[i][j] + B.mat[i][j];
        }
    }
    return result;
}

Matrix Matrix::subtract(const Matrix& B) const {
    assert(rows() == B.rows() && cols() == B.cols());
    Matrix result(rows(), cols());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < cols(); ++j) {
            result.mat[i][j] = mat[i][j] - B.mat[i][j];
        }
    }
    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(cols(), rows());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < cols(); ++j) {
            result.mat[j][i] = mat[i][j];
        }
    }
    return result;
}

/// @brief 求逆矩阵
Matrix Matrix::invert() const {
    assert(rows() == cols());
    size_t n = rows();
    Matrix A = *this;  //深拷贝
    Matrix I = identity(n);

    // 高斯消元
    for (size_t i = 0; i < n; ++i) {
        double maxEl = abs(A.mat[i][i]);
        size_t maxRow = i;
        for (size_t k = i + 1; k < n; ++k) {
            if (abs(A.mat[k][i]) > maxEl) {
                maxEl = abs(A.mat[k][i]);
                maxRow = k;
            }
        }

        for (size_t k = i; k < n; ++k) {
            swap(A.mat[maxRow][k], A.mat[i][k]);
            swap(I.mat[maxRow][k], I.mat[i][k]);
        }

        double pivot = A.mat[i][i];
        for (size_t k = 0; k < n; ++k) {
            A.mat[i][k] /= pivot;
            I.mat[i][k] /= pivot;
        }

        for (size_t k = 0; k < n; ++k) {
            if (k != i) {
                double factor = A.mat[k][i];
                for (size_t j = 0; j < n; ++j) {
                    A.mat[k][j] -= factor * A.mat[i][j];
                    I.mat[k][j] -= factor * I.mat[i][j];
                }
            }
        }
    }

    return I;
}

std::vector<double>& Matrix::operator[](size_t index) {
    return mat[index];
}

const std::vector<double>& Matrix::operator[](size_t index) const {
    return mat[index];
}

Matrix Matrix::operator*(const Matrix& B) const{
    assert(cols() == B.rows());
    Matrix result(rows(), B.cols());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < B.cols(); ++j) {
            for (size_t k = 0; k < cols(); ++k) {
                result.mat[i][j] += mat[i][k] * B.mat[k][j];
            }
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& B) const {
    assert(rows() == B.rows() && cols() == B.cols());
    Matrix result(rows(), cols());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < cols(); ++j) {
            result.mat[i][j] = mat[i][j] + B.mat[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& B)const {
    assert(rows() == B.rows() && cols() == B.cols());
    Matrix result(rows(), cols());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < cols(); ++j) {
            result.mat[i][j] = mat[i][j] - B.mat[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar)const {
    Matrix result(rows(), cols());
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < cols(); ++j) {
            result[i][j] = scalar * mat[i][j];
        }
    }
    return result;
}

void Matrix::mat_print() const {
    for (size_t i = 0; i < rows(); ++i) {
        for (size_t j = 0; j < cols(); ++j) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}
Matrix operator*(double val, const Matrix& A) {
    return A * val;
}