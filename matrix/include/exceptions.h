#pragma once

#include <exception>
#include <string>

#include "matrix.h"

class MatrixException : public std::exception {
 public:
    explicit MatrixException(const std::string& msg) : m_msg(msg) {
    }

    const char* what() const noexcept override {
        return m_msg.c_str();
    }

 private:
    std::string m_msg;
};

class InvalidMatrixStream : public MatrixException {
 public:
    InvalidMatrixStream()
        : MatrixException("Error occurred while reading from stream") {
    }
};

class OutOfRange : public MatrixException {
 public:
    OutOfRange(size_t i, size_t j, const Matrix& matrix)
        : MatrixException("Indexes (" + std::to_string(i) + ", " +
                          std::to_string(j) +
                          ") are out of range. Matrix size is [" +
                          std::to_string(matrix.rowCount()) + ", " +
                          std::to_string(matrix.colCount()) + "]") {
    }
};

class DimensionMismatch : public MatrixException {
 public:
    DimensionMismatch(const Matrix& m1, const Matrix& m2)
        : MatrixException("M1[" + std::to_string(m1.rowCount()) + ", " +
                          std::to_string(m1.colCount()) + "] and M2[" +
                          std::to_string(m2.rowCount()) + ", " +
                          std::to_string(m2.colCount()) +
                          "] are not compatible") {
    }

    explicit DimensionMismatch(const Matrix& m)
        : MatrixException("M[" + std::to_string(m.rowCount()) + ", " +
                          std::to_string(m.colCount()) +
                          "] isn't square matrix") {
    }
};

class SingularMatrix : public MatrixException {
 public:
    SingularMatrix() : MatrixException("Singular matrix") {
    }
};
