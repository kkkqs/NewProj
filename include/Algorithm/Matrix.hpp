#pragma once
#include <iostream>
#include <vector>
#include <math.h>

class Matrix {
private:
    std::vector<std::vector<double>> mat;
public:
    explicit Matrix(const size_t rows, const size_t cols, const double init_val = 0.0) : mat(rows, std::vector<double>(cols, init_val)) {}
    Matrix(const std::vector<std::vector<double>>& values) : mat(values) {}
    Matrix(const std::vector<double> values):mat({values}) {}
    Matrix(const double value):mat({{value}}) {}
    Matrix() {}

    static Matrix identity(size_t size);

    size_t rows() const {return mat.size();}
    size_t cols() const {return mat[0].size();}
    
    std::vector<double>& operator[](size_t index) {
        return mat[index];
    }

    const std::vector<double>& operator[](size_t index) const {
        return mat[index];
    }

    Matrix multiply(const Matrix& B) const;
    Matrix add(const Matrix& B) const;
    Matrix subtract(const Matrix& B) const;
    Matrix transpose() const;
    Matrix invert() const;
    Matrix operator*(const Matrix &B) const;
    Matrix operator+(const Matrix &B) const;
    Matrix operator-(const Matrix &B) const;
    Matrix operator*(const double val) const;
    friend Matrix operator*(const double val, const Matrix &B);
    void mat_print() const;
};