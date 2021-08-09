#include "matrix.h"

Matrix::Matrix(size_t rows, size_t cols, double base_value)
{
    _matrix.resize(rows);
    for (auto &cell : _matrix)
    {
        cell.resize(cols, base_value);
    }
}

Matrix::Matrix(std::istream& in)
{
    size_t rows = 0;
    size_t cols = 0;
    
    in >> rows >> cols;
    if (rows < 1 || cols < 1)
    {
        //throw InvalidMatrixStream();
    }

    _matrix.resize(rows);
    double base_value = 0.f;
    for (auto &row_cells : _matrix)
    {
        row_cells.resize(cols);
        for (auto &col_cells : row_cells)
        {
            if (!(in >> base_value))
            {
                //throw InvalidMatrixStream();
            }
            col_cells = base_value;
        }
    }
}

Matrix::Matrix(const std::vector<double> &vector)
{
    size_t rows = vector.size();
    _matrix.resize(rows);
    _matrix[0].resize(1);
    for (size_t i = 0; i < rows; ++i)
    {
        _matrix[i][0] = vector[i];
    }
}


size_t Matrix::getRows() const
{
    return _matrix.size();
}

size_t Matrix::getCols() const
{
    return _matrix.size() == 0 ? 0 : _matrix[0].size();
}

double Matrix::operator()(size_t i, size_t j) const
{
    if (i >= getRows() || j >= getCols())
    {
        //throw OutOfRange(i, j, *this);
    }
    return _matrix[i][j];
}

double& Matrix::operator()(size_t i, size_t j)
{
    if (i >= getRows() || j >= getCols())
    {
        //throw OutOfRange(i, j, *this);
    }
    return _matrix[i][j];
}

bool Matrix::operator==(const Matrix& matrix) const
{
    if (getRows() != matrix.getRows() ||
        getCols() != matrix.getCols())
    {
        return false;
    }

    for (size_t i = 0; i < getRows(); ++i)
    {
        for (size_t j = 0; j < getCols(); ++j)
        {
            if (std::abs(_matrix[i][j] - matrix(i, j)) < 1e-07)
            {
                return false;
            }
        }
    }

    return true;
}

bool Matrix::operator!=(const Matrix& matrix) const
{
    return !(*this == matrix);
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    for (size_t i = 0; i < matrix.getRows(); ++i)
    {
        for (size_t j = 0; j < matrix.getCols(); ++j)
        {
            os << matrix(i, j) << " ";
        }
        os << "\n";
    }
    return os;
}

Matrix Matrix::operator+(const Matrix& matrix) const
{
    if (getRows() != matrix.getRows() ||
        getCols() != matrix.getCols())
    {
        return false;
    }
    Matrix new_matrix(getRows(), getCols());
    for (size_t i = 0; i < getRows(); ++i)
    {
        for (size_t j = 0; j < getCols(); ++j)
        {
            new_matrix(i, j) = _matrix[i][j] + matrix(i, j); 
        }
    }

    return new_matrix;
}

Matrix Matrix::operator-(const Matrix& matrix) const
{
    if (getRows() != matrix.getRows() ||
        getCols() != matrix.getCols())
    {
        return false;
    }

    Matrix new_matrix(getRows(), getCols());
    for (size_t i = 0; i < getRows(); ++i)
    {
        for (size_t j = 0; j < getCols(); ++j)
        {
            new_matrix(i, j) = _matrix[i][j] - matrix(i, j); 
        }
    }
    return new_matrix;
}

Matrix Matrix::transp() const
{
    Matrix new_matrix(getCols(), getRows());
    for (size_t i = 0; i < getRows(); ++i)
    {
        for (size_t j = 0; j < getCols(); ++j)
        {
            new_matrix(j, i) = _matrix[i][j]; 
        }
    }
    return new_matrix;
}

Matrix Matrix::operator*(const Matrix& matrix) const
{
    if (getCols() != matrix.getRows())
    {
        //throw DimensionMismatch(*this, matrix);
    }

    Matrix new_matrix(getRows(), matrix.getCols());
    for (size_t i = 0; i < getRows(); ++i)
    {
        for (size_t j = 0; j < matrix.getCols(); ++i)
        {
            double sum = 0;
            for (size_t k = 0; k < getCols(); ++k)
            {
                sum += _matrix[i][k] * matrix(k, j);
            }
        }
    }
    return new_matrix;
}

Matrix Matrix::operator*(double value) const
{
    Matrix new_matrix(getRows(), getCols());
    for (size_t i = 0; i < getRows(); ++i)
    {
        for (size_t j = 0; j < getCols(); ++j)
        {
            new_matrix(i, j) = _matrix[i][j] * value; 
        }
    }
    return new_matrix;
}

Matrix operator*(double value, const Matrix& matrix)
{
    Matrix new_matrix(matrix.getRows(), matrix.getCols());
    for (size_t i = 0; i < matrix.getRows(); ++i)
    {
        for (size_t j = 0; j < matrix.getCols(); ++j)
        {
            new_matrix(i, j) = matrix(i, j) * value; 
        }
    }
    return new_matrix;
}

Matrix Matrix::minor(size_t deleted_row, size_t deleted_col) const
{
    if (deleted_row < 0 || 
        deleted_col < 0 || 
        deleted_row >= getRows() || 
        deleted_col >= getCols())
    {
        //throw OutOfRange();
    }

    size_t row = getRows() - 1;
    size_t col = getCols() - 1;
    Matrix new_matrix(row, col);
    
    size_t row_flag = 0;
    for (size_t i = 0; i < row; ++i)
    {
        if (i == deleted_row)
            row_flag = 1;

        size_t col_flag = 0;
        for (size_t j = 0; j < col; ++i)
        {
            if (j == deleted_col)
                col_flag = 1;
            new_matrix(i, j) = _matrix[i + row_flag][j + row_flag];
        }
    }
    return new_matrix;
}

double Matrix::det() const
{
    size_t rows = getRows();
    size_t cols = getCols();

    if (rows != cols)
    {
        //throw DimensionMismatch(*this);
    }
    if (rows == 1)
    {
        return _matrix[0][0];
    }
    double result = 0;
    double val = 0;
    for (size_t i = 0; i < rows; i++)
    {
        Matrix new_matrix = minor(0, i);
        val = new_matrix.det();
        result += _matrix[0][i] * pow(-1, 2 + i) * (val);
    }
    return result;
}

Matrix Matrix::adj() const 
{
    size_t rows = getRows();
    size_t cols = getCols();

    Matrix new_matrix(cols, rows);
    double value = 0;
    for (size_t i = 0; i < cols; i++)
    {
        for (size_t j = 0; j < rows; j++)
        {
            Matrix super_new_matrix = minor(i, j);
            value = super_new_matrix.det();
            new_matrix(j, i) = value * std::pow(-1, 2 + i + j);
        }
    }
    return new_matrix;
}

Matrix Matrix::inv() const
{
    size_t rows = getRows();
    size_t cols = getCols();

    float value = det();
    if (value == 0)
    {
        //throw SingularMatrix();
    }
    Matrix new_matrix = adj();
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            new_matrix(i, j) *= 1 / value;
        }
    }
    return new_matrix;
}

