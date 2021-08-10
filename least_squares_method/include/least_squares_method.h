#pragma once

#include <vector>
#include "matrix.h"
#include "slau.h"

class LeastSquaresMethod : public Slau
{
public:
    LeastSquaresMethod(std::istream &in) : Slau(in) {} ;
    std::vector<double> getResult(size_t n);

private:
    void createOffset(size_t n);
    void createMatrix(size_t n);

private:
    Matrix _input;
};

