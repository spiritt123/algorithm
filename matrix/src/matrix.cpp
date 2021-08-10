#include "matrix.h"
#include "exceptions.h"

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
        throw InvalidMatrixStream();
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
                throw InvalidMatrixStream();
            }
            col_cells = base_value;
        }
    }
}

Matrix::Matrix(const std::vector<double> &vector)
{
    size_t rows = vector.size();
    _matrix.resize(rows);
    for (size_t i = 0; i < rows; ++i)
    {
        _matrix[i].resize(1);
        _matrix[i][0] = vector[i];
    }
}


size_t Matrix::rowCount() const
{
    return _matrix.size();
}

size_t Matrix::colCount() const
{
    return _matrix.size() == 0 ? 0 : _matrix[0].size();
}

std::vector<double> Matrix::getRow(size_t i)
{
    if (i < 0 || i >= rowCount())
        throw OutOfRange(i, 0, *this);

    return _matrix[i];
}

std::vector<double> Matrix::getCol(size_t j)
{
    if (j < 0 || j >= colCount())
        throw OutOfRange(0, j, *this);

    std::vector<double> answer;
    for (size_t i = 0; i < rowCount(); ++i)
        answer.push_back(_matrix[i][j]);
    return answer;
}

std::vector<std::vector<double>> Matrix::getMatrix()
{
    return _matrix;
}

void Matrix::addColum(const std::vector<double> &vector)
{
    if (vector.size() != rowCount())
        throw DimensionMismatch(*this, Matrix(vector));

    for (size_t i = 0; i < rowCount(); ++i)
    {
        _matrix[i].push_back(vector[i]);
    }
}

void Matrix::addRow(const std::vector<double> &vector)
{
    if (vector.size() != colCount())
        throw DimensionMismatch(*this, Matrix(vector));

    _matrix.push_back(vector);
}

void Matrix::changeRow(const std::vector<double> &vector, size_t row)
{
    if (row < 0 || row >= rowCount())
        throw OutOfRange(0, row, *this);

    _matrix[row] = vector;
}

void Matrix::changeColum(const std::vector<double> &vector, size_t colum)
{
    if (colum < 0 || colum >= colCount())
        throw OutOfRange(colum, 0, *this);
    
    for (size_t j = 0; j < colCount(); ++j)
    {
        _matrix[j][colum] = vector[j];
    }
}

    
double Matrix::operator()(size_t i, size_t j) const
{
    if (i >= rowCount() || j >= colCount())
        throw OutOfRange(i, j, *this);

    return _matrix[i][j];
}

double& Matrix::operator()(size_t i, size_t j)
{
    if (i >= rowCount() || j >= colCount())
        throw OutOfRange(i, j, *this);
    
    return _matrix[i][j];
}

bool Matrix::operator==(const Matrix& matrix) const
{
    if (rowCount() != matrix.rowCount() ||
        colCount() != matrix.colCount())
    {
        return false;
    }

    for (size_t i = 0; i < rowCount(); ++i)
    {
        for (size_t j = 0; j < colCount(); ++j)
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

void Matrix::operator=(const Matrix& matrix)
{
    _matrix.resize(matrix.rowCount());
    for (size_t i = 0; i < matrix.rowCount(); ++i)
    {
        _matrix[i].resize(colCount());
        for (size_t j = 0; j < matrix.colCount(); ++j)
        {
            _matrix[i][j] = matrix(i, j);
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    for (size_t i = 0; i < matrix.rowCount(); ++i)
    {
        for (size_t j = 0; j < matrix.colCount(); ++j)
        {
            os << matrix(i, j) << " ";
        }
        os << "\n";
    }
    return os;
}

Matrix Matrix::operator+(const Matrix& matrix) const
{
    if (rowCount() != matrix.rowCount() ||
        colCount() != matrix.colCount())
    {
        return false;
    }
    Matrix new_matrix(rowCount(), colCount());
    for (size_t i = 0; i < rowCount(); ++i)
    {
        for (size_t j = 0; j < colCount(); ++j)
        {
            new_matrix(i, j) = _matrix[i][j] + matrix(i, j); 
        }
    }

    return new_matrix;
}

Matrix Matrix::operator-(const Matrix& matrix) const
{
    if (rowCount() != matrix.rowCount() ||
        colCount() != matrix.colCount())
    {
        return false;
    }

    Matrix new_matrix(rowCount(), colCount());
    for (size_t i = 0; i < rowCount(); ++i)
    {
        for (size_t j = 0; j < colCount(); ++j)
        {
            new_matrix(i, j) = _matrix[i][j] - matrix(i, j); 
        }
    }
    return new_matrix;
}

Matrix Matrix::transp() const
{
    Matrix new_matrix(colCount(), rowCount());
    for (size_t i = 0; i < rowCount(); ++i)
    {
        for (size_t j = 0; j < colCount(); ++j)
        {
            new_matrix(j, i) = _matrix[i][j]; 
        }
    }
    return new_matrix;
}

Matrix Matrix::operator*(const Matrix& matrix) const
{
    if (colCount() != matrix.rowCount())
    {
        throw DimensionMismatch(*this, matrix);
    }

    Matrix new_matrix(rowCount(), matrix.colCount());
    for (size_t i = 0; i < rowCount(); ++i)
    {
        for (size_t j = 0; j < matrix.colCount(); ++j)
        {
            for (size_t k = 0; k < colCount(); ++k)
            {
                new_matrix(i,j) += _matrix[i][k] * matrix(k, j);
            }
        }
    }
    return new_matrix;
}

Matrix Matrix::operator*(double value) const
{
    Matrix new_matrix(rowCount(), colCount());
    for (size_t i = 0; i < rowCount(); ++i)
    {
        for (size_t j = 0; j < colCount(); ++j)
        {
            new_matrix(i, j) = _matrix[i][j] * value; 
        }
    }
    return new_matrix;
}

Matrix operator*(double value, const Matrix& matrix)
{
    Matrix new_matrix(matrix.rowCount(), matrix.colCount());
    for (size_t i = 0; i < matrix.rowCount(); ++i)
    {
        for (size_t j = 0; j < matrix.colCount(); ++j)
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
        deleted_row >= rowCount() || 
        deleted_col >= colCount())
    {
        throw OutOfRange(deleted_row, deleted_col, *this);
    }

    size_t row = rowCount() - 1;
    size_t col = colCount() - 1;
    Matrix new_matrix(row, col);
    size_t row_flag = 0;
    for (size_t i = 0; i < row; ++i)
    {
        if (i == deleted_row)
            row_flag = 1;

        size_t col_flag = 0;
        for (size_t j = 0; j < col; ++j)
        {
            if (j == deleted_col)
                col_flag = 1;
            new_matrix(i, j) = _matrix[i + row_flag][j + col_flag];
        }
    }
    return new_matrix;
}

double Matrix::det() const
{
    size_t rows = rowCount();
    size_t cols = colCount();

    if (rows != cols)
    {
        throw DimensionMismatch(*this);
    }
    if (rows == 1)
    {
        return _matrix[0][0];
    }
    double result = 0;
    for (size_t i = 0; i < rows; i++)
    {
        Matrix new_matrix = minor(0, i);
        result += _matrix[0][i] * pow(-1, 2 + i) * new_matrix.det();
    }
    return result;
}

Matrix Matrix::adj() const 
{
    size_t rows = rowCount();
    size_t cols = colCount();

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
    size_t rows = rowCount();
    size_t cols = colCount();

    float value = det();
    if (value == 0)
    {
        throw SingularMatrix();
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

