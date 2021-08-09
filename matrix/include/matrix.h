#pragma once

#include <iostream>
#include <vector>
#include <cmath>
//#include "exceptions.h"

class Matrix
{
public:
    Matrix(size_t rows = 0, size_t cols = 0, double base_value = 0);
    Matrix(std::istream& in);
    Matrix(const std::vector<double> &vector);
    size_t getRows() const;
    size_t getCols() const;

    double operator()(size_t i, size_t j) const;
    double& operator()(size_t i, size_t j);
    bool operator==(const Matrix& matrix) const;
    bool operator!=(const Matrix& matrix) const;
    Matrix operator+(const Matrix& matrix) const;
    Matrix operator-(const Matrix& matrix) const;
    Matrix operator*(const Matrix& matrix) const;
    Matrix operator*(double value) const;

    Matrix transp() const;
    Matrix minor(std::size_t deleted_row, std::size_t deleted_col) const;
    double det() const;
    Matrix adj() const;
    Matrix inv() const;
private:
    std::vector<std::vector<double>> _matrix;
};

std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
Matrix operator*(double value, const Matrix& matrix);
