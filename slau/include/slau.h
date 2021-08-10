#pragma once

#include <vector>
#include <istream>
#include "matrix.h"

class Slau : public Matrix
{
public:
    //Slau() : Matrix();
    Slau(std::istream &in) : Matrix(in) {} ;
    void addOffset(const std::vector<double> &offset);
    
    std::vector<double> findByKramer();
    //std::vector<double> findByGausse();
    std::vector<double> findByMatrix();

protected:
    std::vector<double> _offset;
};
