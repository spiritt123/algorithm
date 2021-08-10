#include "least_squares_method.h"
#include "slau.h"
#include "exceptions.h"
#include <stdexcept>

std::vector<double> LeastSquaresMethod::getResult(size_t n)
{
    ++n;
    createOffset(n);
    createMatrix(n);

    std::vector<double> answer = findByMatrix();

    return answer;
}

void LeastSquaresMethod::createOffset(size_t n)
{
    _offset.resize(n);
    for (int i = n - 1; i >= 0; --i)
    {
        double sum = 0;
        for (size_t j = 0; j < _matrix[0].size(); ++j)
        {
            sum += _matrix[1][j] * std::pow(_matrix[0][j], i);
        }
        _offset[n - i - 1] = sum;
    }
}

void LeastSquaresMethod::createMatrix(size_t n)
{
    std::vector<double> powers;
    for (int i = 2 * (n - 1); i >= 0; --i)
    {
        double sum = 0;
        for (auto number : _matrix[0])
        {
            sum += std::pow(number, i);
        }
        powers.push_back(sum);
    }

    Matrix matrix(n, n);
    for (size_t i = 0; i < n; ++i)
    {
        for (size_t j = 0; j < n; ++j)
        {
            matrix(i, j) = powers[i + j];
        }
    }
    _matrix = matrix.getMatrix();
}


