#include "complex_number.h"
#include <iostream>
#include <cmath>

ComplexNumber::ComplexNumber()
{
    re = 0;
    im = 0;
}

ComplexNumber::ComplexNumber(double re = 0, double im = 0)
{
    this->re = re;
    this->im = im;
}

ComplexNumber::~ComplexNumber(){}

ComplexNumber& ComplexNumber::operator=(const ComplexNumber& number)
{
    if (this == &number) 
    {
        return *this;
    }
    re = number.re;
    im = number.im;

    return *this;
}

const ComplexNumber operator+(ComplexNumber& left, const ComplexNumber& right)
{
    return ComplexNumber(left.re + right.re, left.im + right.im);
}
    
const ComplexNumber operator-(ComplexNumber& left, const ComplexNumber& right)
{
    return ComplexNumber(left.re - right.re, left.im - right.im);
}

const ComplexNumber operator*(ComplexNumber& left, const ComplexNumber& right)
{
    return ComplexNumber(left.re * right.re - left.im * right.im, 
                         left.im * right.re + left.re * right.im);
}

const ComplexNumber operator/(ComplexNumber& left, const ComplexNumber& right)
{
    double div = right.re * right.re + right.im * right.im;
    if (std::abs(div) < 0.000001) 
    {
        std::cerr << "division 0!!!\n";
        return left;
    }
    return ComplexNumber((left.re * right.re - left.im * right.im) / div, 
                         (left.im * right.re + left.re * right.im) / div);
}


ComplexNumber& operator+=(ComplexNumber& left, const ComplexNumber& right)
{
    return left = left + right;
}

ComplexNumber& operator-=(ComplexNumber& left, const ComplexNumber& right)
{
    return left = left - right;
}

ComplexNumber& operator*=(ComplexNumber& left, const ComplexNumber& right)
{
    return left = left * right;
}

ComplexNumber& operator/=(ComplexNumber& left, const ComplexNumber& right)
{
    return left = left / right;
}
bool operator==(ComplexNumber& left, const ComplexNumber& right)
{
    return left.re == right.re && left.im == right.im;
}

double ComplexNumber::abs(ComplexNumber& number)
{
    return sqrt(number.re * number.re + number.im * number.im);
}

ComplexNumber& ComplexNumber::pow(ComplexNumber& number, int power)
{
    ComplexNumber result = number;
    for (int i = 1; i < power; ++i)
        result *= number;
    return result;
}

std::ostream& operator<<(std::ostream &os, const ComplexNumber& number) 
{    
    os << number.re;
    if (number.im >= 0)
        os << '+';
    os << number.im << "i\n";
    return os;
}
