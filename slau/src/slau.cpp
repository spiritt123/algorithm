
#include "slau.h"
#include "exceptions.h"
#include <stdexcept>

std::vector<double> Slau::findByKramer()
{
    if (getRows() != getCols())
        throw DimensionMismatch(*this);

    if (_offset.size() != getCols())
        throw DimensionMismatch(*this);

    std::vector<double> answer;
    double det = this->det();
    if (std::abs(det) < 0.0001)
        throw std::invalid_argument("Divide by zero error in fraction!");
    //данный алгоритм описывает учебные дейстиви. Возможная оптимизация: транспонировать, поменять строку, транспонировать.
    for (size_t i = 0; i < getRows(); ++i)
    {
        //Matrix new_matrixi(_matrix);
        Slau new_matrix = *this;
        new_matrix.changeColum(_offset, i);
        answer.push_back(new_matrix.det() / det);
    }
    return answer;
}

void Slau::addOffset(const std::vector<double> &offset)
{
    _offset = offset;
}

/*
std::vector<double> Slau::findByGausse()
{
    size_t rows = getRows();
    if (rows != getCols())
        throw DimensionMismatch(*this);

    if (_offset.size() != getCols())
        throw DimensionMismatch(*this);

    for (size_t i = 0; i < rows; ++i)
    {
        if (std::abs(_matrix[i][i]) < 0.0001)
            throw std::invalid_argument("The main diagonal contains zeros!");
    }
    
    addColum(_offset);

    for (size_t k = 1; k < rows; ++k)
    {
        for (size_t j = k; j < rows; ++j)
        {
            double alpha = _matrix[j][k - 1] / _matrix[k][k];
            for (size_t i = 0; i < getCols() + 1; ++i)
            {
                _matrix[j][i] -= alpha * _matrix[k - 1][i];
            }
        }
    }

    std::vector<double> answer;

    for (int i = rows - 1; i >= 0; --i)
    {
        answer.push_back(_matrix[i][rows] / _matrix[i][i]);
        for (size_t j = rows - 1; j > i ; --j)
        {
            answer[i] -= _matrix[i][j] * answer[j] / _matrix[i][i];
        }
    }

    return answer;
}*/

std::vector<double> Slau::findByMatrix()
{
    if (getRows() != getCols())
        throw DimensionMismatch(*this);

    if (_offset.size() != getCols())
        throw DimensionMismatch(*this);

    Matrix matrix = inv() * Matrix(_offset);
    std::vector<double> answer = matrix.getCol(0); 
    
    return answer;
}
